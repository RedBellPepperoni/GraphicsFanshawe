#pragma once
#include "Engine/Core/Application/Application.h"
#include "Engine/Utils/UniqueId/UniqueId.h"
#include <map>
#include <sol/forward.hpp>


namespace FanshaweGameEngine
{
	class Scene;
	class Entity;
    namespace Components {
        class Transform;
    }

    using Components::Transform;

		class LuaScriptComponent
		{
        public:
			LuaScriptComponent();
			LuaScriptComponent(const std::string& filename, Scene* scene);
			~LuaScriptComponent();

			void Init();
			void OnInit();



			void OnUpdate(float dt);
			void Reload();

			void Load(const std::string& filename);
			Entity GetCurrentEntity();

            Transform* GetTransform();
            Vector3 GetPosition();
            void SetPosition(const Vector3& position);

            // For accessing this component in lua
            void SetThisComponent();

            void LoadScript(const std::string& fileName);

       

            const sol::environment& GetSolEnvironment() const
            {
                return *m_env;
            }
            const std::string& GetFilePath() const
            {
                return m_fileName;
            }

            void SetFilePath(const std::string& path)
            {
                m_fileName = path;
            }

            const std::map<int, std::string>& GetErrors() const
            {
                return m_errors;
            }

            bool Loaded()
            {
                return m_env != nullptr;
            }

		private:

            Scene* m_scene = nullptr;
            std::string m_fileName;
            std::map<int, std::string> m_errors;

            sol::environment* m_env;
            sol::protected_function* m_OnInitFunc;
            sol::protected_function* m_UpdateFunc;
            sol::protected_function* m_onReleaseFunc;

      
		};
	
}

