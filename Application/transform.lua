-- Create a local table to fill with values and return.
-- This makes it possible to some scripts to require ( same
-- as include in C / C ++) , this module without creating a
-- table in the global environment.
local transform = {}

-- require will search for the requested module and run it.
-- dofile (" vector.lua ") would do the same thing but would ,
-- not search in other directories listed in package.path.
-- require will automatically add ’ .lua ’ at the end of the
-- requested module.
-- A required module will return a table , it ’s not more
-- complicated than that. :)
local vector = require("vector")

-- p : position, a vector
-- r : rotation, a vector
-- s : scale, a vector
function transform.new(p, r, s)
    local t = {
        postion = p or vector.new(),    -- set default vector if p is nil
        rotation = r or vector.new (),  -- set default vector if r is nil
        scale = s or vector.new()       -- set default vector if s is nil
    }
    return t
end

-- We will add more functionality in module M3 ,
-- when we work with Lua classes. :)

return transform