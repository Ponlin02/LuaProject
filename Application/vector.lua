local vector = {}



--[[if getmetatable(t) == mt then
	print("We have defined our type!")
end
]]--	


print("nu körs denna fil")

vector.__index = vector

function vector:length()
	return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
end

function vector.normalized(v)
	local length = v:length()
	return vector.new(v.x / length, v.y / length, v.z / length)
end

function vector.new(x, y, z)
	local t = {
		x = x or 0,
		y = y or 0,
		z = z or 0
	}

	--t.length = length

	return setmetatable(t, vector)
end

function vector.isvector(t)
	return getmetatable(t) == vector
end

function vector.__newindex(t,k,v)
	print("vector - not possible to assign new fields")
end

function vector.__tostring(t)
	local string = "(" .. t.x .. ", " .. t.y .. ", " .. t.z .. " )"
	return string
end

function vector.__unm(t)
	return vector.new(-t.x, -t.y, -t.z)
end

function vector.__add(a, b)
	if vector.isvector(a) == true and vector.isvector(b) == true then
		return vector.new(a.x + b.x, a.y + b.y, a.z + b.z)
	end
end

function vector.__sub(a, b)
	if vector.isvector(a) == true and vector.isvector(b) == true then
		return vector.new(a.x - b.x, a.y - b.y, a.z - b.z)
	end
end

function vector.__mul(a, b)
	if vector.isvector(a) == true and vector.isvector(b) == true then
		return vector.new(a.x * b.x, a.y * b.y, a.z * b.z)
	end	
	if vector.isvector(a) == true and vector.isvector(b) == false then
		return vector.new(a.x * b, a.y * b, a.z * b)
	end
	if vector.isvector(a) == false and vector.isvector(b) == true then
		return vector.new(a * b.x, a * b.y, a * b.z)
	end
end

function vector.__div(a, b)
	if vector.isvector(a) == true and vector.isvector(b) == true then
		return vector.new(a.x / b.x, a.y / b.y, a.z / b.z)
	end	
	if vector.isvector(a) == true and vector.isvector(b) == false then
		return vector.new(a.x / b, a.y / b, a.z / b)
	end
end

function vector.__eq(a, b)
	if vector.isvector(a) == false or vector.isvector(b) == false then
		return false
	end
	if a.x == b.x and a.y == b.y and a.z == b.z then
		return true
	else 
		return false
	end
end

return setmetatable(vector, {
	__call = function(_,...)
		return vector.new(...)
	end
})