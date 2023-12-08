#pragma once
#include "Engine/Core/Application/Application.h"
#include "Engine/Utils/UniqueId/UniqueId.h"
#include <map>
#include <sol/forward.hpp>

//namespace FanshaweGameEngine
//{
//	class Scene;
//	class Entity;
//
//	namespace Components
//	{
//		class LuaScriptComponent
//		{
//        public:
//			LuaScriptComponent();
//			LuaScriptComponent(const std::string& filename, Scene* scene);
//			~LuaScriptComponent();
//
//			void Init();
//			void OnInit();
//
//			void OnUpdate(float deltaTime);
//			void Reload();
//
//			void Load(const std::string& filename);
//			Entity GetCurrentEntity();
//
//            // For accessing this component in lua
//            void SetThisComponent();
//
//            void LoadScript(const std::string& fileName);
//
//            void OnCollisionBegin();
//            void OnCollisionEnd();
//
//            const sol::environment& GetSolEnvironment() const
//            {
//                return *m_env;
//            }
//            const std::string& GetFilePath() const
//            {
//                return m_fileName;
//            }
//
//            void SetFilePath(const std::string& path)
//            {
//                m_fileName = path;
//            }
//
//            const std::map<int, std::string>& GetErrors() const
//            {
//                return m_errors;
//            }
//
//            bool Loaded()
//            {
//                return m_env.get() != nullptr;
//            }
//
//		private:
//
//            Scene* m_scene = nullptr;
//            std::string m_fileName;
//            std::map<int, std::string> m_errors;
//
//            SharedPtr<sol::environment> m_env;
//            SharedPtr<sol::protected_function> m_onInitFunc;
//            SharedPtr<sol::protected_function> m_updateFunc;
//            SharedPtr<sol::protected_function> m_onReleaseFunc;
//
//            SharedPtr<sol::protected_function> m_physBeginFunc;
//            SharedPtr<sol::protected_function> m_physEndFunc;
//      
//		};
//	}
//}

