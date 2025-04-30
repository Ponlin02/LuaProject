local transform = {}

local vector = require("vector")

function transform.istransform(t)
	return getmetatable(t) == transform
end

function transform.v1new(p, r, s)
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