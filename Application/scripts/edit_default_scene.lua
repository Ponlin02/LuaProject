-- Default scene for edit map
-- Creatíng 25 squares in a 5 x 5 square

print("attempt 1 for writing ...")

require("scripts/entityFunctions")

print("attempt 2 for writing...")

for z = 1, 5 do
	for x = 1, 5 do
		local posZ = z - 1
		local posX = x - 1
		createFloor(posX, posZ)
	end
end

createPlayer(12,12)

print ("Succesfully created editmap")