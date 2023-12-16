local CommandSequencer = require("commandsequencer")
local CommandSequencer = require("commandsequencer")
local CommandGroup = require("commandgroup")

local function AddCommandToSequencer(groupIndex, command)
    local sequencer = CommandSequencer.getInstance()
    local found = false
    for _, group in ipairs(sequencer.commandGroups) do
        if group == sequencer.commandGroups[groupIndex] then
            found = true
            break
        end
    end
    if not found then
        sequencer.commandGroups[groupIndex] = CommandGroup.new()  -- Create a new group if it doesn't exist
    end

   if sequencer and sequencer.commandGroups[groupIndex] then
        sequencer.commandGroups[groupIndex]:pushSerial(command)

    else

        print("Error: Invalid group index or sequencer not initialized.")
    end
end

return {
    AddCommandToSequencer = AddCommandToSequencer
}
