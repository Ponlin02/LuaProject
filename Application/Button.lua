local button = {}
print("Hello i am a button")
button.time = 5
--button.door = 1


function button:OnCreate()
	print("button created!")
end

function button:OnUpdate(delta)
	print("update button!")
	print(self.time)
	if self.time >= 0 then
		self.time = self.time - 1
	end
	print("button not activated")
end

--function button:OnActivate()
	--print("activated button!")
	--self.time = 30
--end

return button