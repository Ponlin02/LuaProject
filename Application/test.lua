entity = scene.CreateEntity()
print("hello from test")
scene.SetComponent(entity, "floor", 0, 0)
scene.SetComponent(entity, "behaviour", "Button.lua")