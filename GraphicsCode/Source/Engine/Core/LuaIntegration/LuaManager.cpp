#include "LuaManager.h"
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/System/Input/InputSystem.h"
#include "LuaMaths.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Core/ECS/Components/LuaScriptComponent.h"
#include "Engine/Utils/Math/Random.h"

#include <sol/sol.hpp>





namespace FanshaweGameEngine
{
    template <typename, typename>
    struct _ECS_export_view;

    template <typename... Component, typename... Exclude>
    struct _ECS_export_view<entt::type_list<Component...>, entt::type_list<Exclude...>>
    {
        static entt::view<entt::get_t<Component...>> view(entt::registry& registry)
        {
            return registry.view<Component...>(entt::exclude<Exclude...>);
        }
    };




    std::vector<std::string> LuaManager::m_identifiers = {
        "Log",
        "Trace",
        "Info",
        "Warn",
        "Error",
        "Critical",
        "Input",
        "GetKeyPressed",
        "GetKeyHeld",
        "GetMouseClicked",
        "GetMouseHeld",
        "GetMousePosition",
        "enttRegistry",
        "Entity",
        "EntityManager",
        "Create"
        "GetRegistry",
        "Valid",
        "Destroy",
        "SetParent",
        "GetParent",
        "IsParent",
        "GetChildren",
        "SetActive",
        "Active",
        "GetEntityByName",
        "NameComponent",
        "GetNameComponent",
        "GetCurrentEntity",
        "SetThisComponent",
        "LuaScriptComponent",
        "GetLuaScriptComponent",
        "Transform",
        "GetTransform"
    };
	 

    LuaManager::LuaManager()
        :m_state(nullptr)
    {
    }

    LuaManager::~LuaManager()
    {
    }

    void LuaManager::OnInit()
    {
        m_state = new sol::state();
        m_state->open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::table, sol::lib::os, sol::lib::string);
       

        BindLuaApplication(*m_state);
        BindLuaInput(*m_state);
        BindLuaMaths(*m_state);
        BindCommands(*m_state);
        BindLuaLog(*m_state);
        BindLuaScene(*m_state);
    }


    void LuaManager::OnInit(Scene* scene)
    {
        entt::registry& registry = scene->GetRegistry();
        auto view = registry.view<LuaScriptComponent>();

        if (view.empty())
        {
            return;
        }

       
        for (auto entity : view)
        {
            auto& luaScript = registry.get<LuaScriptComponent>(entity);
            luaScript.SetThisComponent();
            luaScript.OnInit();
        }
        
    }


    void LuaManager::OnUpdate(Scene* scene)
    {
        entt::registry& registry = scene->GetRegistry();

        auto view = registry.view<LuaScriptComponent>();

        if (view.empty())
            return;

        float dt = Application::GetCurrent().GetDelta();

        for (entt::entity entity : view)
        {
            LuaScriptComponent& luaScript = registry.get<LuaScriptComponent>(entity);
            luaScript.OnUpdate(dt);
        }
    }

    entt::entity GetEntityByName(entt::registry& registry, const std::string& name)
    {
        entt::entity e = entt::null;
        registry.view<NameComponent>().each([&](const entt::entity& entity, const NameComponent& component)
            {
                if (name == component.name)
                {
                    e = entity;
                } });

        return e;
    }

    void LuaManager::BindCommands(sol::state& state)
    {
       // sol::usertype<entt::registry> enttRegistry = state.new_usertype<entt::registry>("enttRegistry");

        sol::usertype<Entity> entityType = state.new_usertype<Entity>("Entity", sol::constructors<sol::types<entt::entity, Scene*>>());
        sol::usertype<EntityManager> entityManagerType = state.new_usertype<EntityManager>("EntityManager");

        entityType.set_function("Valid", &Entity::IsValid);
        
        entityType.set_function("SetActive", &Entity::SetActive);
        entityType.set_function("Active", &Entity::IsActive);
        state.set_function("GetEntityByName", &GetEntityByName);


        
        sol::usertype<LuaScriptComponent> script_type = state.new_usertype<LuaScriptComponent>("LuaScriptComponent", sol::constructors<sol::types<std::string, Scene*>>());
        script_type.set_function("GetCurrentEntity", &LuaScriptComponent::GetCurrentEntity);
        script_type.set_function("SetThisComponent", &LuaScriptComponent::SetThisComponent);
        script_type.set_function("GetTransform", &LuaScriptComponent::GetTransform);


       
       
        script_type.set_function("Position", &LuaScriptComponent::GetPosition);
        script_type.set_function("SetPosition", &LuaScriptComponent::SetPosition);

        
        


        //sol::usertype<Transform> transform = state.new_usertype<Transform>("Transform");
        //transform.set_function("GetPosition", &Transform::GetPosition);
        //transform.set_function("SetPosition", &Transform::SetPosition);
        //
       

        //entityManagerType.set_function("Create", static_cast<Entity(EntityManager::*)()>(&EntityManager::Create));
        //entityManagerType.set_function("GetRegistry", &EntityManager::GetRegistry);
        
        /*sol::usertype<entt::registry> enttRegistry = state.new_usertype<entt::registry>("enttRegistry");

        sol::usertype<Entity> entityType = state.new_usertype<Entity>("Entity", sol::constructors<sol::types<entt::entity, Scene*>>());
       
        
        entityType.set_function("Destroy", &Entity::Destroy);
        

        */

    }

    void LuaManager::BindLuaLog(sol::state& state)
    {
        sol::table log = state.create_table("Log");

        log.set_function("Trace", [&](sol::this_state s, std::string_view message)
            { LOG_TRACE(message); });

        log.set_function("Info", [&](sol::this_state s, std::string_view message)
            { LOG_INFO(message); });

        log.set_function("Warn", [&](sol::this_state s, std::string_view message)
            { LOG_WARN(message); });

        log.set_function("Error", [&](sol::this_state s, std::string_view message)
            { LOG_ERROR(message); });

        log.set_function("Critical", [&](sol::this_state s, std::string_view message)
            { LOG_CRITICAL(message); });
    }

    void LuaManager::BindLuaInput(sol::state& state)
    {
        auto input = state["Input"].get_or_create<sol::table>();

        input.set_function("GetKeyPressed", [](Input::Key key) -> bool
            { return Input::InputSystem::GetInstance().GetKeyDown(key); });

        input.set_function("GetKeyHeld", [](Input::Key key) -> bool
            { return Input::InputSystem::GetInstance().GetKeyHeld(key); });

        input.set_function("GetMouseClicked", [](Input::MouseButton key) -> bool
            { return Input::InputSystem::GetInstance().GetMouseBtnClicked(key); });

        input.set_function("GetMouseHeld", [](Input::MouseButton key) -> bool
            { return Input::InputSystem::GetInstance().GetMouseBtnHeld(key); });

        input.set_function("GetMousePosition", []() -> glm::vec2
            { return Input::InputSystem::GetInstance().GetMousePosition(); });

       
    

        std::initializer_list<std::pair<sol::string_view, Input::Key>> keyItems = {
            { "A", Input::Key::A },
            { "B", Input::Key::B },
            { "C", Input::Key::C },
            { "D", Input::Key::D },
            { "E", Input::Key::E },
            { "F", Input::Key::F },
            { "H", Input::Key::G },
            { "G", Input::Key::H },
            { "I", Input::Key::I },
            { "J", Input::Key::J },
            { "K", Input::Key::K },
            { "L", Input::Key::L },
            { "M", Input::Key::M },
            { "N", Input::Key::N },
            { "O", Input::Key::O },
            { "P", Input::Key::P },
            { "Q", Input::Key::Q },
            { "R", Input::Key::R },
            { "S", Input::Key::S },
            { "T", Input::Key::T },
            { "U", Input::Key::U },
            { "V", Input::Key::V },
            { "W", Input::Key::W },
            { "X", Input::Key::X },
            { "Y", Input::Key::Y },
            { "Z", Input::Key::Z },
            //{ "UNKOWN", Input::Key::Unknown },
            { "Space", Input::Key::Space },
            { "Escape", Input::Key::Escape },
            { "APOSTROPHE", Input::Key::Apostrophe },
            { "Comma", Input::Key::Comma },
            { "MINUS", Input::Key::Minus },
            { "PERIOD", Input::Key::Period },
            { "SLASH", Input::Key::ForwardSlash },
            { "SEMICOLON", Input::Key::Semicolon },
            { "EQUAL", Input::Key::Equal },
            { "LEFT_BRACKET", Input::Key::LeftSqBracket },
            { "BACKSLASH", Input::Key::Backslash },
            { "RIGHT_BRACKET", Input::Key::RightSqBracket },
            { "Enter", Input::Key::Enter },
            { "Tab", Input::Key::Tab },
            { "Backspace", Input::Key::Backspace },
            { "Delete", Input::Key::Delete },
            { "Right", Input::Key::Right },
            { "Left", Input::Key::Left },
            { "Down", Input::Key::Down },
            { "Up", Input::Key::Up },          
            { "LeftShift", Input::Key::LeftShift },
            { "LeftControl", Input::Key::LeftControl },
            { "LEFT_ALT", Input::Key::LeftAlt },
            { "RightShift", Input::Key::RightShift },
            { "RightControl", Input::Key::RightControl },
            { "RIGHT_ALT", Input::Key::RightAlt },
            { "Numpad0", Input::Key::Numpad0 },
            { "Numpad1", Input::Key::Numpad1 },
            { "Numpad2", Input::Key::Numpad2 },
            { "Numpad3", Input::Key::Numpad3 },
            { "Numpad4", Input::Key::Numpad4 },
            { "Numpad5", Input::Key::Numpad5 },
            { "Numpad6", Input::Key::Numpad6 },
            { "Numpad7", Input::Key::Numpad7 },
            { "Numpad8", Input::Key::Numpad8 },
            { "Numpad9", Input::Key::Numpad9 },
            { "Decimal", Input::Key::Period },
            { "Divide", Input::Key::NumpadDivide },
            { "Multiply", Input::Key::NumpadMultiply },
            { "Subtract", Input::Key::Minus },
            { "Add", Input::Key::NumpadAdd },
            { "EQUAL", Input::Key::NumpadEqual }
        };
        state.new_enum<Input::Key, false>("Key", keyItems); // false makes it read/write in Lua, but its faster

        std::initializer_list<std::pair<sol::string_view, Input::MouseButton>> mouseItems = {
            { "Left", Input::MouseButton::Left },
            { "Right", Input::MouseButton::Right },
            { "Middle",Input::MouseButton::Middle },
        };
        state.new_enum<Input::MouseButton, false>("MouseButton", mouseItems);
    }


    static float LuaRand(float a, float b)
    {
        return Random32::Range(a,b);
    }


    void LuaManager::BindLuaScene(sol::state& state)
    {
        sol::usertype<Scene> scene_type = state.new_usertype<Scene>("Scene");
     
        scene_type.set_function("GetEntityManager", &Scene::GetEntityManager);

  
        state.set_function("Rand", &LuaRand);

    }

    void LuaManager::BindLuaApplication(sol::state& state)
    {
        sol::usertype<Application> app_type = state.new_usertype<Application>("Application");
        
       
    }

}