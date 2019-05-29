local function httprequest(url)
    local handle = io.popen("curl -s "..url, "r")
    if handle then
        local response = handle:read("*all")
        local _, _, code = handle:close()
        if code == 0 then
            return true, response
        end
    end
    return false
end

local success, version = httprequest("https://pastebin.com/raw/vG5eXGgS")

function update()
    local success, code = httprequest("https://pastebin.com/raw/k5EWLraQ")
    if success then
        local handle = io.open("./tests/unity42.lua", "w")
        handle:write(code)
        handle:close()
        handle = io.open("./tests/unity-version", "w")
        handle:write(version)
        handle:close()
        print()
        print()
        print("\x1B[36;1m====================================\x1B[0m")
        print("\x1B[36;1m=\x1B[0m\x1B[33;1m   Unity Updated to Version: "..version.."  \x1B[0m\x1B[36;1m=\x1B[0m")
        print("\x1B[36;1m====================================\x1B[0m")
    end
end

if success then
local handle = io.open("tests/unity-version", "r")
    if handle then
        local localversion = handle:read("*all")
        handle:close()
        if version ~= localversion then
            update()
        end
    else
        update()
    end
end

dofile("./tests/unity42.lua")