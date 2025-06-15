-- Default scene for the game

require("scripts/entityFunctions")

-- Message
print("Attempting to load default map...")

-- Map
-- 0 = floor
-- 1 = wall
-- 9 = player

local map = {
    {1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 9, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1},
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
		elseif value == 9 then
			createFloor(posX, posZ)
			createPlayer(posX * 5, posZ * 5)
		end
	end
end

-- End message
print("Default map successfully loaded!")
