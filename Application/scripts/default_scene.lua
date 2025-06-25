-- Default scene for the game

require("scripts/entityFunctions")

-- Message
print("Attempting to load default map...")

-- Map
-- 0 = floor
-- 1 = wall
-- 2 = button
-- 3 = door
-- 4 = goal
-- 9 = player

local map = {
    {1, 1, 1, 2, 1, 1, 1},
    {1, 0, 3, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1},
    {1, 2, 1, 9, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 4, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 1}
}

-- Loading the map in the scene
for z = 1, #map do
	for x = 1, #map[z] do
		local value = map[z][x]
		local posX = x - 1
		local posZ = z - 1

		if value == 0 then
			createFloor(posX, posZ)
		elseif value == 1 then
			createWall(posX, posZ)
        elseif value == 2 then
			createButton1(posX, posZ)
        elseif value == 3 then
			createDoor1(posX, posZ)
            createFloor(posX, posZ)
        elseif value == 4 then
			createGoal(posX, posZ)
		elseif value == 9 then
			createFloor(posX, posZ)
			createPlayer(posX * 5, posZ * 5)
		end
	end
end

-- End message
print("Default map successfully loaded!")
