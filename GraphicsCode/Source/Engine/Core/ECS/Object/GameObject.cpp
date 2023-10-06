#include "GameObject.h"
#include "Engine/Core/Rendering/Essentials/Mesh.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Macros/Macro.h"
#include <iostream>


namespace FanshaweGameEngine
{
    GameObjectRegistry::GameObjectRegistry()
    {
    }
    GameObjectRegistry::~GameObjectRegistry()
    {
    }

    GameObjectRegistry::ObjectRegistry GameObjectRegistry::Get()
    {
        return m_objectRegistry;
    }

    SharedPtr<GameObject> GameObjectRegistry::CreateObject(const SharedPtr<Mesh>& mesh, const std::string& friendlyObjectName)
    {
     
       CHECKNULL(mesh);

       SharedPtr<GameObject> newObject = Factory<GameObject>::Create();

       newObject->m_rendermesh = mesh;
       //newObject->m_rendermesh->GetVBO()->Bind();
       //newObject->m_rendermesh->GetIBO()->Bind();

       m_objectRegistry.emplace(friendlyObjectName, newObject);

       return newObject;
    }
    
  
    GameObject::GameObject(const SharedPtr<Mesh>& mesh)
    {
        m_rendermesh = mesh;
        
    } 

    GameObject::GameObject(const Transform& transform, const SharedPtr<Mesh>& mesh)
    {
        m_rendermesh = mesh;
        m_transform = transform;
    }
    GameObject::~GameObject()
    {
    }
    void GameObject::AttachShader(const uint32_t& shaderID)
    {
        //Application::GetCurrent().
    }
}