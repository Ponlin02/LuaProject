
--local f = io.open("test1.txt")

--local lines = {}
--for line in io.lines("test1.txt") do 
	--lines[#lines + 1] = line
--end

--for k,v in pairs(lines) do
  --print('line[' .. k .. ']', v)
--end

print("nu kör vi!")

for line in io.lines("test.txt") do
	
	local entityID, component, posX, posZ = line:match("entity:%s*(%d+)%s*'(.-)'%s*posX:%s*(%d+)%s*posZ:%s(%d+)")

    posX = tonumber(posX) 
    posZ = tonumber(posZ) 
    
    print(posX)
    print(posZ)
    print(component)

    if component == "floor" then
        createFloor(posX, posZ)
    elseif component == "wall" then
        createWall(posX, posZ)
    elseif component == "door" then
        createDoor1(posX, posZ)
    elseif component == "button" then
        createButton1(posX, posZ)
    elseif component == "goal" then
        createGoal(posX, posZ)
    elseif component == "player" then
        createPlayer(posX * 5, posZ * 5)
        createFloor(posX, posZ) -- Ofta har spelaren golv under sig
    else
        print("Okänd komponent:", component)
    end
end


createPlayer(12,12)