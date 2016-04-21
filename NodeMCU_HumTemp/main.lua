tmr.alarm(0, 2000, 1, function()
	status, temp, humi, temp_dec, humi_dec = dht.read(1)
	if status == dht.OK then
		print("DHT Temperature: "..temp.." ;".." Humidity: "..humi.."\n")
	elseif status == dht.ERROR_CHECKSUM then
    		print( "DHT Checksum error." )
	elseif status == dht.ERROR_TIMEOUT then
    		print( "DHT timed out." )
	end
end)
