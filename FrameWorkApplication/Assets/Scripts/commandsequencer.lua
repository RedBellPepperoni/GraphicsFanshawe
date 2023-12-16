-- commandsequencer.lua




local CommandSequencer = {}
CommandSequencer.__index = CommandSequencer

local instance = nil

function CommandSequencer.new()
    local self = setmetatable({}, CommandSequencer)
    self.commandGroups = {}
    return self
end

function CommandSequencer.getInstance()
    if not instance then
        instance = CommandSequencer.new()
    end
    return instance
end

function CommandSequencer.addCommandGroup(commandGroup)
    table.insert(instance.commandGroups, commandGroup)
end

function CommandSequencer.onUpdate(deltaTime)
    for _, group in ipairs(instance.commandGroups) do
        group:executeSerial(deltaTime)
        group:executeParallel(deltaTime)
    end
end

return CommandSequencer