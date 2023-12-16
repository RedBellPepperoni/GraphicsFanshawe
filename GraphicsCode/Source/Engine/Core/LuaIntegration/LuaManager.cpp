#pragma once
#include "LuaManager.h"
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"

#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/System/Input/InputSystem.h"
#include "LuaMaths.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Core/ECS/Components/LuaScriptComponent.h"
#include "Engine/Utils/Math/Random.h"
#include "Engine/Core/Rendering/Lights/Light.h"
#include "Engine/Core/ECS/Components/MeshRenderer.h"
#include "Engine/Core/Rendering/Essentials/Material.h"
#include "Engine/Core/Rendering/Essentials/Mesh.h"
#include "Engine/Core/ECS/Components/MeshComponent.h"
#include "Engine/Utils/Loading/Model.h"




#include <sol/sol.hpp>




namespace FanshaweGameEngine
{

    using namespace Rendering;

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

    using namespace entt;

#define REGISTER_COMPONENT_WITH_ECS(curLuaState, Comp, assignPtr)                                              \
    {                                                                                                          \
                                                                                        \
        auto entity_type = curLuaState["Entity"].get_or_create<sol::usertype<registry>>();                     \
        entity_type.set_function("Add" #Comp, assignPtr);                                                      \
        entity_type.set_function("Remove" #Comp, &Entity::RemoveComponent<Comp>);                              \
        entity_type.set_function("Get" #Comp, &Entity::GetComponent<Comp>);                                    \
        entity_type.set_function("TryGet" #Comp, &Entity::TryGetComponent<Comp>);                              \
        entity_type.set_function("Has" #Comp, &Entity::HasComponent<Comp>);                                    \
        auto entityManager_type = curLuaState["enttRegistry"].get_or_create<sol::usertype<registry>>();        \
        entityManager_type.set_function("view_" #Comp, &_ECS_export_view<type_list<Comp>, type_list<>>::view); \
        auto V = curLuaState.new_usertype<view<entt::get_t<Comp>>>(#Comp "_view");                             \
        V.set_function("each", &view<get_t<Comp>>::each<std::function<void(Comp&)>>);                    \
        V.set_function("front", &view<get_t<Comp>>::front);                                              \
        m_identifiers.push_back(#Comp);                                                                        \
        m_identifiers.push_back("Add" #Comp);                                                                  \
        m_identifiers.push_back("Remove" #Comp);                                                               \
        m_identifiers.push_back("Get" #Comp);                                                                  \
        m_identifiers.push_back("TryGet" #Comp);                                                               \
        m_identifiers.push_back("Has" #Comp);                                                                  \
    }


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


        sol::usertype<Entity> entityType = state.new_usertype<Entity>("Entity", sol::constructors<sol::types<entt::entity, Scene*>>());
        sol::usertype<EntityManager> entityManagerType = state.new_usertype<EntityManager>("EntityManager");

        entityType.set_function("Valid", &Entity::IsValid);
        entityType.set_function("SetActive", &Entity::SetActive);
        entityType.set_function("Active", &Entity::IsActive);
        state.set_function("GetEntityByName", &GetEntityByName);

        sol::usertype<NameComponent> nameComponent_type = state.new_usertype<NameComponent>("NameComponent");
        nameComponent_type["name"] = &NameComponent::name;
        REGISTER_COMPONENT_WITH_ECS(state, NameComponent, static_cast<NameComponent& (Entity::*)()>(&Entity::AddComponent<NameComponent>));
      
        sol::usertype<LuaScriptComponent> script_type = state.new_usertype<LuaScriptComponent>("LuaScriptComponent", sol::constructors<sol::types<std::string, Scene*>>());
        REGISTER_COMPONENT_WITH_ECS(state, LuaScriptComponent, static_cast<LuaScriptComponent& (Entity::*)(std::string&&, Scene*&&)>(&Entity::AddComponent<LuaScriptComponent, std::string, Scene*>));
        script_type.set_function("GetCurrentEntity", &LuaScriptComponent::GetCurrentEntity);
        script_type.set_function("SetThisComponent", &LuaScriptComponent::SetThisComponent);
        
        using namespace Components;
        REGISTER_COMPONENT_WITH_ECS(state, Transform, static_cast<Transform & (Entity::*)()>(&Entity::AddComponent<Transform>));

       /* script_type.set_function("GetTransform", &LuaScriptComponent::GetTransform);
        script_type.set_function("Position", &LuaScriptComponent::GetPosition);
        script_type.set_function("SetPosition", &LuaScriptComponent::SetPosition);*/

        state.new_usertype<Light>(
            "Light",
            "Intensity", &Light::intensity,
            "Radius", &Light::radius,
            "Color", &Light::color,
            "Direction", &Light::direction,
            "Position", &Light::position,
            "Type", &Light::type,
            "InnerAngle", &Light::innerAngle,
            "OuterAngle", &Light::outerAngle); 

        REGISTER_COMPONENT_WITH_ECS(state, Light, static_cast<Light & (Entity::*)()>(&Entity::AddComponent<Light>));

     /*   
        state.new_usertype<Material>(
            "Material",
            "albedoColour", &Material::albedoColour); 

        state.new_usertype<MeshRenderer>(
            "MeshRenderer",
            "GetMaterial", &MeshRenderer::GetMaterial);



        REGISTER_COMPONENT_WITH_ECS(state, MeshRenderer, static_cast<MeshRenderer & (Entity::*)()>(&Entity::AddComponent<MeshRenderer>));


        state.new_usertype<Mesh>(
            "Mesh"
            );

        state.new_usertype<MeshComponent>(
            "MeshComponent",
            "MeshRed", &MeshComponent::m_handle);

        REGISTER_COMPONENT_WITH_ECS(state, MeshRenderer, static_cast<MeshRenderer & (Entity::*)()>(&Entity::AddComponent<MeshRenderer>));



        state.new_usertype<Model>(
            "Model",
            "GetMesh", &Model::GetFirstMesh

        );*/


        

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
            { "G", Input::Key::G },
            { "H", Input::Key::H },
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
        scene_type.set_function("CreateEntity", &Scene::CreateEntity);
  
        state.set_function("Rand", &LuaRand);

    }

    void LuaManager::BindLuaApplication(sol::state& state)
    {
        sol::usertype<Application> app_type = state.new_usertype<Application>("Application");
        
       
    }

}