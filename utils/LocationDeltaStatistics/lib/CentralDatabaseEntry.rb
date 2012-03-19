class CentralDatabaseEntry
    attr_accessor :ipAddress, :time, :coordinates

    def initialize(ipAddress, time, coordinates)
        @ipAddress = ipAddress
        @time = time.to_f
        @coordinates = coordinates
    end

    def isEntryFor(time, destinationIPAddress)
        return @time == time.to_f && @ipAddress == destinationIPAddress
    end

    def to_s()
        return "#{@ipAddress} at time #{@time} was at #{@coordinates}"
    end
end
