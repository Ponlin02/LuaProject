-- Create a local table to fill with values and return.
-- This makes it possible to some scripts to require ( same
-- as include in C / C ++) , this module without creating a
-- table in the global environment.
local vector = {}

function vector.new (x , y , z )
    local t = {
        x = x or 0 , -- set 0 as default value if x is nil
        y = y or 0 , -- set 0 as default value if y is nil
        z = z or 0 -- set 0 as default value if z is nil
    }
    return t
end

-- We will add more functionality in module M3 ,
-- when we work with Lua classes. :)

return vector