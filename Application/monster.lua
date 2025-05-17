local monster = {}
print("hello from monster file")
monster.lifespan = 3

function monster:OnCreate()
	print("Monster created!")
end

function monster:OnUpdate(delta)
	print("Monster updated!")

	self.lifespan = self.lifespan - 1

	if self.lifespan <= 0 then
		scene.RemoveEntity(self.ID)
		print("I dieded")
	end
end

return monster