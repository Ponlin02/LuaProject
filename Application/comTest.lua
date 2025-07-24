--Utility functions

function setWall( entity, posX, posZ )
	scene.SetComponent(entity, "wall", posX, posZ)
end

function setDoor1( entity, posX, posZ )
	scene.SetComponent(entity, "door1", posX, posZ)
end

function setButton1( entity, posX, posZ )
	scene.SetComponent(entity, "button1", posX, posZ)
	scene.SetComponent(entity, "button1click")
end

function setGoal( entity, posX, posZ )
	scene.SetComponent(entity, "goal", posX, posZ)
end

function addRow(x, z)
	local posX = x + 1
	local posZ = z + 1
	print(x)
	for y = 1, posX do
		entity = scene.CreateEntity()
		scene.SetComponent(entity, "floor", y - 1, posZ)
	end	
end

function addCollumn(x, z)
	local posX = x + 1
	local posZ = z + 1
	print(x)
	for y = 1, posZ do
		entity = scene.CreateEntity()
		scene.SetComponent(entity, "floor", posX, y  - 1)
	end
end