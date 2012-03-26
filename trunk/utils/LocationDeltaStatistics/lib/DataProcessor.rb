
require 'Coordinate.rb' 
require 'CentralDatabaseEntry'

class DataProcessor

    @@CENTRAL_STATISTIC_FLAG = "CENTRAL"
    @@DISTRUBUTED_STATISTIC_FLAG = "TABLE"

    def initialize(fileName)
        @fileName = fileName
        @centralizedData = Hash.new
        processCentralizedDatabaseData()
    end

    def to_s()
        return @centralizedData.to_s()
    end

    def getActualCoordinateFor(time, destinationIPAddress)
        return @centralizedData["#{time}:#{destinationIPAddress}"]
    end

    def processDistrubutedData()
        file = File.new(@fileName, "r")
        outFileName = @fileName.gsub(/\.csv$/, ".processed.csv")
        puts "Processing distributed data for #{@fileName}"
        puts "Storing results in #{outFileName}"
        @outFile = File.new(outFileName, "w")
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
        puts "Processing centralized data for #{@fileName}"
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
        @centralizedData["#{time}:#{thisIPAddress}"] = CentralDatabaseEntry.new(thisIPAddress, time, destinationCoordinates)
    end

    def storeStatistics(time, thisNodeName, destinationIPAddress, destinationCoordinates)
        datum = getActualCoordinateFor(time, destinationIPAddress)

        if datum != nil
            #puts "Store statistics for #{thisNodeName} for entry of #{destinationIPAddress} with #{destinationCoordinates} at #{time}"
            #puts "\t#{datum}"
            distance = destinationCoordinates.distance(datum.coordinates)
            @outFile.write("#{time}, #{thisNodeName}, #{destinationIPAddress}, #{distance}\n")
        end
    end
end
