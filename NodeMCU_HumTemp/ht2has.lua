-- Sends Humidity and Temperature Values to Home automation server
-- Format is *MyHomeProto;HumTemp;SensorId;Humidity(*10);Temp(*100);END#

function sendHumTemp2Has(host, sensorId, humidity, temperature)
  srv = net.createConnection(net.TCP,0)
  srv:on("receive", function( sck, c) print(c) end)
  srv:connect(12000, host)
  srv:on("connection", function(sck,c)
    sck:send("*MyHomeProto;HumTemp;"..sensorId..";"..(humidity*10)..";"..(temperature*100)..";END#", function() sck:close() end)
  end)
end
