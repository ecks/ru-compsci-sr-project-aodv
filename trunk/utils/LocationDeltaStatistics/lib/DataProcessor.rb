
require 'Coordinate.rb' 
require 'CentralDatabaseEntry'

class DataProcessor

    @@CENTRAL_STATISTIC_FLAG = "CENTRAL"
    @@DISTRUBUTED_STATISTIC_FLAG = "TABLE"

    def initialize(fileName)
        @fileName = fileName
        @centralizedData = Array.new()
        processCentralizedDatabaseData()
    end

    def to_s()
        return @centralizedData.to_s()
    end

    def getActualCoordinateFor(time, destinationIPAddress)
        #puts "Searching for #{destinationIPAddress} at #{time}"
        @centralizedData.each do | datum |
            if datum.isEntryFor(time, destinationIPAddress)
                return datum
            end
        end

        return nil
    end

    def processDistrubutedData()
        file = File.new(@fileName, "r")
        @outFile = File.new(@fileName.gsub(/\.csv$/, ".out.csv"), "w")
        file.each_line("\n") do | row |
            row = row.gsub(/\s/,  '')
            columns = row.split(",")
            entryType = columns[0]

            time = columns[1]

            if entryType == @@DISTRUBUTED_STATISTIC_FLAG
                thisNodeName = columns[2]
                destinationIPAddress = columns[3]
                destinationCoordinates = Coordinate.new(columns[4], columns[5])
                storeStatistics(time, thisNodeName, destinationIPAddress, destinationCoordinates)
            end
        end

        @outFile.close()
    end

    private

    def processCentralizedDatabaseData()
        file = File.new(@fileName, "r")
        file.each_line("\n") do | row |
            row = row.gsub(/\s/,  '')
            columns = row.split(",")
            entryType = columns[0]

            time = columns[1]
            #puts "Time = " + time

            if entryType == @@CENTRAL_STATISTIC_FLAG
                thisIPAddress = columns[2]
                destinationCoordinates = Coordinate.new(columns[3], columns[4])
                storeCentralizedDatabaseData(time, thisIPAddress, destinationCoordinates)
            end
        end

    end

    def storeCentralizedDatabaseData(time, thisIPAddress, destinationCoordinates) 
        datum = CentralDatabaseEntry.new(thisIPAddress, time, destinationCoordinates)
        @centralizedData << datum
    end

    def storeStatistics(time, thisNodeName, destinationIPAddress, destinationCoordinates)
        datum = getActualCoordinateFor(time, destinationIPAddress)

        if datum != nil
            puts "Store statistics for #{thisNodeName} for entry of #{destinationIPAddress} with #{destinationCoordinates} at #{time}"
            puts "\t#{datum}"
            distance = destinationCoordinates.distance(datum.coordinates)
            @outFile.write("#{time}, #{thisNodeName}, #{destinationIPAddress}, #{distance}\n")
        end
    end
end
