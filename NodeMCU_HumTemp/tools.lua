-- Some useful shortcuts

function ls()
	local l=file.list();
	local i=0
	for k,v in pairs(l) do
		print("  "..k.." "..v.." Bytes\n")
		i=i+1
	end
	print(" Number of files: "..i)
end

