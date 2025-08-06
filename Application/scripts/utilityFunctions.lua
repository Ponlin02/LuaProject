--Utility functions

function setWall( entity, posX, posZ )
	scene.RemoveComponent(entity, "floor")
	scene.SetComponent(entity, "wall", posX, posZ)
end

function setDoor1( entity, posX, posZ )
	scene.RemoveComponent(entity, "floor")
	scene.SetComponent(entity, "door1", posX, posZ)
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
    --return coroutine.create(function()
    local co = coroutine.create(function()
        local steps = 600  -- antal frames tills dörren är helt stängd
        --local door = scene.GetComponent(entity, "door1state")
        --door.openAmount = 0.0
    
        scene.RemoveComponent(entity, "door1state")
        scene.SetComponent(entity, "door1state", 0.0 , true)
        --coroutine.yield() -- låt dörren vara öppen minst 1 frame


        for i = 1, steps do
            --local door = scene.GetComponent(entity, "door1state")
            --door.openAmount = i / steps
            local openAmount = i / steps
            scene.RemoveComponent(entity, "door1state")
            scene.SetComponent(entity, "door1state", openAmount, true)
           
            coroutine.yield()
        end

        -- Stäng klart dörren
        --local door = scene.GetComponent(entity, "door1state")
        scene.RemoveComponent(entity, "door1state")
        scene.SetComponent(entity, "door1state", 1.0, false)

        end)
    return co, entity
end
