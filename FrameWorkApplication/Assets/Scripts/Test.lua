--Default Lua Script


targetMoveToposition = {}
movetime = 0.0

function OnInit()


end



function MoveTo(position, time)

    targetMoveToposition = position
    movetime = time

end



function OnUpdate(dt)

   

    local position = LuaComponent:GetPosition()

    position.x = position.x + 10*dt 

    LuaComponent:SetPosition(position)

    Log.Info(tostring(position.x))
    Log.Warn("Warn")

end

function OnCleanUp()
end