--Default Lua Script
local CommandManager = require("commandmanager")
local Command = require("command")

local entity = {}
local transform = {}
local scene = {}
local otherEntity = {}

function OnInit()
   
    entity = LuaComponent:GetCurrentEntity()
    transform = LuaComponent:GetCurrentEntity():GetTransform()


    CommandManager = require("commandmanager")




    local targetPosition = { x = 20, y = 10, z = 0 }
    local timeToMove = 4
    local moveCommand = Command.executeMoveTowards(transform, targetPosition, timeToMove)
    moveCommand.isDone = false  


   CommandManager.AddCommandToSequencer(1, moveCommand)
   


 

end




function OnUpdate(dt)


    local position = transform:GetPosition()


    local nextposition =  position.x + 10 * dt

 -- transform:SetPosition(Vector3.new(nextposition,0,0))


end

function OnCleanUp()
end