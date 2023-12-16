
local CommandGroup = {}
CommandGroup.__index = CommandGroup

function CommandGroup.new()
    local self = setmetatable({}, CommandGroup)
    self.serialCommands = {}
    self.parallelCommands = {}
    return self
end

function CommandGroup.pushSerial(self, command)
    table.insert(self.serialCommands, command)
end

function CommandGroup.pushParallel(self, command)
    table.insert(self.parallelCommands, command)
end

function CommandGroup.executeSerial(self, deltaTime)
    for _, command in ipairs(self.serialCommands) do
        if not command.isDone then
            command:execute(deltaTime) 
            if command.isDone then
                print("Command", command.name, "is finished.")
            else
                break  
            end
        end
    end
end

function CommandGroup.executeParallel(self, deltaTime)
    for _, command in ipairs(self.parallelCommands) do
        command:execute(deltaTime)  
    end
end

return CommandGroup
