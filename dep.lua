---
--- Created by djbartolini.
--- DateTime: 5/18/24 5:30 PM
---

local function execute_command(command)
    local handle = io.popen(command .. " 2>&1")  -- Redirect stderr to stdout
    local output = handle:read("*a")
    local _, _, exit_code = handle:close()
    return output, exit_code
end

-- List of commands to execute
local commands = {
    "sudo cp -r /opt/homebrew/opt/sdl2 ./lib",
    "sudo cp -r /opt/homebrew/opt/sdl2_image ./lib",
    "sudo cp -r /opt/homebrew/opt/sdl2_mixer ./lib"
}

-- Iterate through each command and execute it
for _, command in ipairs(commands) do
    print("Executing command: " .. command)
    local output, exit_code = execute_command(command)
    print("Command output:\n" .. output)
    print("Exit code: " .. tostring(exit_code))

    -- Check if the command was successful
    if exit_code == 0 then
        print("Command executed successfully.")
    else
        print("Command failed with exit code:", exit_code)
        break  -- Stop execution if any command fails
    end
end



--
--local commands =
--{
--    "ls /opt/homebrew/opt/sdl2",
--    "cp -r /opt/homebrew/opt/sdl2 ./lib",
--    "cp -r /opt/homebrew/opt/sdl2_image ./lib",
--    "cp -r /opt/homebrew/opt/sdl2_mixer ./lib"
--}
--
--for _, command in ipairs(commands) do
--	print("Copying dependencies . . .")
--	print("Dependency path: ", command)
--
--	local exit_code = os.execute(command)
--
--	if exit_code ~= 0 then
--		print("Command failed. Exit code: ", exit_code)
--		break
--	else
--	    print("Dependencies added to `./lib`.")
--	end
--end
