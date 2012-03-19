#!/usr/bin/env ruby
$LOAD_PATH << './lib'

require 'DataProcessor.rb'

ARGV.each do | fileName | 
    dataProcessor = DataProcessor.new(fileName)
    dataProcessor.processDistrubutedData()
end

