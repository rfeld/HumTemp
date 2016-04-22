-- Send Temperature and Humidity to HAS every 10s
dofile("ht2has.lua")
tmr.alarm(0, 10000, 1, function()
	status, temp, humi, temp_dec, humi_dec = dht.read(1)
	if status == dht.OK then
		print("DHT Temperature: "..temp.." ;".." Humidity: "..humi.."\n")
    sendHumTemp2Has("raspberrypi2", "nodemcu1", humi, temp)
	elseif status == dht.ERROR_CHECKSUM then
    		print( "DHT Checksum error." )
	elseif status == dht.ERROR_TIMEOUT then
    		print( "DHT timed out." )
	end
end)
