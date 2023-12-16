local CommandSequencer = require("commandsequencer")
local CommandManager = require("commandmanager")
local CommandGroup = require("commandgroup")
local Command = require("command")

local  sequencer = CommandSequencer.new()

local start = false

function OnInit()
    -- Initialize the command sequence if needed
    if not sequencer then
        sequencer = CommandSequencer.new()
    end



    if sequencer  then
        print("Found")
    else

        print("Error:  sequencer not initialized.")
    end


    
end


function OnUpdate(deltaTime)

   if Input.GetKeyPressed(Key.G) then
    Log.Warn("Pressed")
    start = true

   end

    if start then
        sequencer.onUpdate(deltaTime)
    end
end

