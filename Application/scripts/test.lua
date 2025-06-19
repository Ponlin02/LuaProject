local entity = scene.CreateEntity()
local posx = 0
local posz = 0
scene.SetComponent(entity, "floor", posx, posz)
require("scripts/entityFunctions")

-- dofile("createfloor.lua")
local testentity = scene.CreateEntity()
scene.SetComponent(testentity, "floor", -1, -4)
scene.SetComponent(testentity, "wall", -1, -4)

-- local colliderEntity = scene.CreateEntity()
-- scene.SetComponent(colliderEntity, "collider", 0, 1, -20, 1, 2, 1)

local player = scene.CreateEntity()
scene.SetComponent(player, "player", 5, 2, 0)

local width = 4
local height = 4

for i = 0, width do
	for j = 0, height do
		local entity = scene.CreateEntity()
		scene.SetComponent(entity, "floor", i, j)
		if i == 2 and j == 2 then
			-- scene.SetComponent(entity, "wall", i, j)
			local entity = scene.CreateEntity()
			scene.SetComponent(entity, "button1", i, j)
		end
	end
end
