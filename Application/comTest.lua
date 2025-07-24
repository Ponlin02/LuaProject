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
