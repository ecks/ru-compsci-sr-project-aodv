
require 'Coordinate.rb' 

class DataProcessor

    @@CENTRAL_STATISTIC_FLAG = "CENTRAL"
    @@DISTRUBUTED_STATISTIC_FLAG = "TABLE"

    def initialize(fileName)
        @file = File.new(fileName, "r")
        processCentralizedDatabaseData()
    end

    def processCentralizedDatabaseData()
        @file.each_line("\n") do | row |
            row = row.gsub(/\s/,  '')
            columns = row.split(",")
            entryType = columns[0]

            time = columns[1]
            #puts "Time = " + time

            if entryType == CENTRAL_STATISTIC_FLAG
                thisIPAddress = columns[2]
                destinationCoordinates = Coordinate.new(columns[3], columns[4])
                storeCentralizedDatabaseData(time, thisIPAddress, destinationCoordinates)
            end
        end

    end

    def storeCentralizedDatabaseData(time, thisIPAddress, destinationCoordinates) 
        puts "Storing coordinates for #{destinationCoordinates} for #{thisIPAddress} at #{time}"
    end

    def getActualCoordinateFor(time, destinationIPAddress)
    end

    def storeStatistics(time, thisNodeName, destinationIPAddress, destinationCoordinates)
        #puts "getActualCoordinateFor(#{time}, #{destinationIPAddress})"
        #puts "Store statistics for #{thisNodeName} for entry of #{destinationIPAddress} with #{destinationCoordinates} at #{time}"
    end

    def to_s()
        "#{@file}"
    end
end
