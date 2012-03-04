#!/usr/bin/env ruby 

require 'Coordinate.rb' 

#
# This program will output the results from the simulation
# into all of the error scores.
# 
# Author: Remo Cocco
#

CENTRAL_STATISTIC_FLAG = "CENTRAL"
DISTRUBUTED_STATISTIC_FLAG = "TABLE"

def process(fileName)
    file = File.new(fileName, 'r')

    file.each_line("\n") do |row|
        row = row.gsub(/\s/,  '')
        columns = row.split(",")
        entryType = columns[0]

        # thse are uncoditinal 
        time = columns[1]
        #puts "Time = " + time


        if entryType == CENTRAL_STATISTIC_FLAG
            thisIPAddress = columns[2]
            #puts "This node address = #{thisNodeAddress}"
            destinationCoordinates = Coordinate.new(columns[3], columns[4])
            storeCentralizedDatabaseData(time, thisIPAddress, destinationCoordinates)
        elsif entryType == DISTRUBUTED_STATISTIC_FLAG
            thisNodeName = columns[2]
            destinationIPAddress =  columns[3]
            destinationCoordinates = Coordinate.new(columns[4], columns[5])
            storeStatistics(time, thisNodeName, destinationIPAddress, destinationCoordinates)

            puts row
        else
            thisNodeName = columns[2]
            destinationIPAddress = columns[3]
            $stderr.puts "Incorrect input at line " + file.loneno
        end

        #break if file.lineno > 10
    end
end

def storeCentralizedDatabaseData(time, thisIPAddress, destinationCoordinates) 
    #puts "Storing coordinates for #{destinationCoordinates} for #{thisIPAddress} at #{time}"
end

def getActualCoordinateFor(time, destinationIPAddress)
end

def storeStatistics(time, thisNodeName, destinationIPAddress, destinationCoordinates)
    #puts "getActualCoordinateFor(#{time}, #{destinationIPAddress})"
    puts "Store statistics for #{thisNodeName} for entry of #{destinationIPAddress} with #{destinationCoordinates} at #{time}"
end

ARGV.each do|a|
    #puts "Argument: #{a}"
    process(a)
end

