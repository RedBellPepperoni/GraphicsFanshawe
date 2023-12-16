-- command.lua

local Command = {}
Command.__index = Command

-- Command Type Enum
Command.CommandType = {
    MOVE_TOWARDS = "MoveTowards",
   
}

function Command.new(name, commandType, params)
    local self = setmetatable({}, Command)
    self.name = name
    self.commandType = commandType
    self.params = params

    -- Assigning the action based on commandType
    if commandType == Command.CommandType.MOVE_TOWARDS then
        self.action = Command.moveTowardsAction
    end
    

    return self
end

function Command.execute(self, deltaTime)
    --print("Executing command:", self.name)
    self.action(self.params)(deltaTime)  -- Pass deltaTime to the action function
end

-- Specific actions for each command type
function Command.moveTowardsAction(params)
  
    return function(deltaTime)

    local transform = params.transform
    local targetPosition = params.targetPosition
    local timeToMove = params.timeToMove

    local initialPosition = transform.GetPosition()
    local startTime = 0 -- To keep track of the start time

    print("Object position:")

        if startTime == 0 then
            startTime = deltaTime
        end

        local currentTime = deltaTime - startTime

        if currentTime < timeToMove then
            local t = currentTime / timeToMove

            local lerpedPosition = {
                x = initialPosition.x * (1 - t) + targetPosition.x * t,
                y = initialPosition.y * (1 - t) + targetPosition.y * t,
                z = initialPosition.z * (1 - t) + targetPosition.z * t
            }

            -- Update the transform's position
            --transform.position = lerpedPosition

            transform.SetPosition(Vector3.new(lerpedPosition.x,lerpedPosition.y,lerpedPosition.z))

            print("Object position:", transform.position)
        else
            -- Ensure the final position is set to the target position
            transform.position = targetPosition

            print("Object reached target position:", targetPosition)

            -- Reset start time for potential reuse
            startTime = 0
        end
    end
end

function Command.executeMoveTowards(transform, targetPosition, timeToMove)
    local params = {
        transform = transform,
        targetPosition = targetPosition,
        timeToMove = timeToMove
    }
    return Command.new("MoveTowards", Command.CommandType.MOVE_TOWARDS, params)
end

return Command