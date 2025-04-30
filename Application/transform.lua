local transform = {}

local vector = require("vector")

function transform.istransform(t)
	return getmetatable(t) == transform
end

function transform.__newindex(t,k,v)
	print("transform - not possible to assign new fields")
end

function transform:__tostring()
	return "position: " .. self.position:__tostring() ..
			", rotation :" .. self.rotation:__tostring() ..
			", scale: " .. self.scale:__tostring()
end

function transform.new(p, r, s)
	--assert(p == nil or vector.isvector(p), "transform new - expected 
		--args: vector is nil")

	local t = {
		position = p or vector.new(),
		rotation = r or vector.new(),
		scale = s or vector.new()
	}
	return setmetatable(t, transform)
end

return transform