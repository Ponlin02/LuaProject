-- Require this file when you want to make entities in the scene

-- Functions requires that a 'scene' exists
function createPlayer(x, z)
	local player = scene.CreateEntity()
	scene.SetComponent(player, "player", x, 2, z)
end

function createFloor(x, z)
	local floor = scene.CreateEntity()
	scene.SetComponent(floor, "floor", x, z)
end

function createWall(x, z)
	local wall = scene.CreateEntity()
	scene.SetComponent(wall, "floor", x, z)
	scene.SetComponent(wall, "wall", x, z)
end
