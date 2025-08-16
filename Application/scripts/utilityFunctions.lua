--Utility functions

function setWall( entity, posX, posZ )
	scene.RemoveComponent(entity, "floor")
	scene.SetComponent(entity, "wall", posX, posZ)
end

function setDoorNorth( entity, posX, posZ) 
    scene.RemoveComponent(entity, "floor")
	scene.SetComponent(entity, "door1", posX, posZ, true)
    scene.SetComponent(entity, "door1state", 0.5, false)
end

function setDoorWest( entity, posX, posZ ) 
    scene.RemoveComponent(entity, "floor")
	scene.SetComponent(entity, "door1", posX, posZ, false)
    scene.SetComponent(entity, "door1state", 0.5, false)
end

function setButton1( entity, posX, posZ )
	scene.RemoveComponent(entity, "floor")	
	scene.SetComponent(entity, "button1", posX, posZ)
	scene.SetComponent(entity, "button1click")
end

function setGoal( entity, posX, posZ )
	scene.RemoveComponent(entity, "floor")
	scene.SetComponent(entity, "goal", posX, posZ)
end

function setPlayer( entity, posX, posZ )
	scene.RemoveComponent(entity, "floor")
	scene.SetComponent(entity, "player", posX, 2, posZ)
    scene.SetComponent(6, "floor", 1, 1)
end

function createAddCollumnCoroutine(x, z)
    local posX = x + 1
    local posZ = z + 1
	local entity = scene.CreateEntity()

    local co = coroutine.create(function()
        for y = 1, posZ do
            e = scene.CreateEntity()
            scene.SetComponent(e, "floor", posX, y - 1)
			
            coroutine.yield()  -- yield så vi kan fortsätta nästa frame
        end
    end)

	return co, entity
end

function createAddRowCoroutine(x, z)
    local posX = x + 1
    local posZ = z + 1
	local entity = scene.CreateEntity()

    local co = coroutine.create(function()
		for y = 1, posX do
			entity = scene.CreateEntity()
			scene.SetComponent(entity, "floor", y - 1, posZ)
		
            coroutine.yield()  -- yield så vi kan fortsätta nästa frame
        end
    end)

	return co, entity
end

function openDoorCoroutine(entity)
    local co = coroutine.create(function()
        local steps = 600  -- antal frames tills dörren är helt stängd
        door = scene.GetComponent(entity, "door1state")
        scene.RemoveComponent(entity, "door1state")
        scene.SetComponent(entity, "door1state", 0.0 , true)
       
        for i = 1, steps do

            local openAmount = i / steps
            scene.RemoveComponent(entity, "door1state")
            scene.SetComponent(entity, "door1state", openAmount, true)
           
            coroutine.yield()
        end

        -- Stäng klart dörren
        scene.RemoveComponent(entity, "door1state")
        scene.SetComponent(entity, "door1state", 1.0, false)

        end)
    return co, entity
end
