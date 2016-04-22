print('Configuring WiFi Connection')
-- In this file the variables _SSID and _WLANKEY must be set
dofile("secrets.lua")
wifi.setmode(wifi.STATION)
print('set mode=STATION (mode='..wifi.getmode()..')')
print('MAC: ',wifi.sta.getmac())
print('chip: ',node.chipid())
print('heap: ',node.heap())
wifi.sta.sethostname("nodemcu1")
-- wifi config start
wifi.sta.config(_SSID, _WLANKEY)
-- wifi config end

print("Starting Telnet Server...")
dofile("telnet_srv.lua")
setupTelnetServer()

-- Indicate connection status with blue led
gpio.mode(0,gpio.OUTPUT)
-- Turn it ON
gpio.write(0, gpio.LOW)

ledStatus=1

tmr.alarm(0, 1000, 1, function()
   if wifi.sta.status() == wifi.STA_CONNECTING then
      if ledStatus==1 then
	gpio.write(0, gpio.HIGH)
	ledStatus=0
      else
	gpio.write(0, gpio.LOW)
        ledStatus=1
      end
   elseif wifi.sta.status() == wifi.STA_GOTIP then
      -- Turn led OFF
      gpio.write(0, gpio.HIGH)
   end
end)

-- Start main function with 5s delay
print("\n--- Starting Main in 5s ---\n")
tmr.alarm(6, 5000,tmr.ALARM_SINGLE, function() dofile("main.lua") end)


