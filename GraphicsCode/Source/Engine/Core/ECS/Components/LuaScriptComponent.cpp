#include "LuaScriptComponent.h"
#include "Engine/Core/LuaIntegration/LuaManager.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Utils/Loading/File.h"
#include <sol/sol.hpp>

namespace FanshaweGameEngine
{

		LuaScriptComponent::LuaScriptComponent()
		{
			m_scene = nullptr;
			m_fileName = "";
			m_env = nullptr;
		}

		LuaScriptComponent::LuaScriptComponent(const std::string& filename, Scene* scene)
		{
			m_scene = scene;
			m_fileName = filename;
			m_env = nullptr;

			Init();
		}

		LuaScriptComponent::~LuaScriptComponent()
		{
			if (m_env)
			{
				sol::protected_function releaseFunc = (*m_env)["OnRelease"];
				if (releaseFunc)
				{
					releaseFunc.call();
				}
			}
		}

		void LuaScriptComponent::Init()
		{
			LoadScript(m_fileName);
		}

		void LuaScriptComponent::OnInit()
		{
			

			if (m_OnInitFunc)
			{

			

				sol::protected_function_result result = m_OnInitFunc->call();
				if (!result.valid())
				{
					sol::error err = result;
					LOG_ERROR("Failed to Execute Script Lua Init function");
					LOG_ERROR("Error : {0}", err.what());
				}
			}

		}
		void LuaScriptComponent::OnUpdate(float dt)
		{
			if (m_UpdateFunc)
			{
				sol::protected_function_result result = m_UpdateFunc->call(dt);

				if (!result.valid())
				{
					sol::error err = result;
					LOG_ERROR("Failed to Execute Script Lua OnUpdate");
					LOG_ERROR("Error : {0}", err.what());
				}
			}
		}

		void LuaScriptComponent::Reload()
		{
			if (m_env)
			{
				sol::protected_function releaseFunc = (*m_env)["OnRelease"];
				if (releaseFunc.valid())
					releaseFunc.call();
			}

			Init();
		}

		void LuaScriptComponent::Load(const std::string& filename)
		{
			if (m_env)
			{
				sol::protected_function releaseFunc = (*m_env)["OnRelease"];
				if (releaseFunc.valid())
					releaseFunc.call();
			}

			m_fileName = filename;
			Init();
		}

		Entity LuaScriptComponent::GetCurrentEntity()
		{
			if (!m_scene)
			{
				m_scene = Application::GetCurrent().GetCurrentScene();
			}

			auto entities = m_scene->GetEntityManager()->GetComponentsOfType<LuaScriptComponent>();

			for (auto entity : entities)
			{
				LuaScriptComponent* comp = &entity.GetComponent<LuaScriptComponent>();
				if (comp->GetFilePath() == GetFilePath())
				{
					return entity;
				}
			}

			return Entity();
		}

		Transform* LuaScriptComponent::GetTransform()
		{
			if (!m_scene)
			{
				m_scene = Application::GetCurrent().GetCurrentScene();
			}

			return &GetCurrentEntity().GetComponent<Transform>();
		}

		Vector3 LuaScriptComponent::GetPosition()
		{
			return GetTransform()->GetPosition();
		}

		void LuaScriptComponent::SetPosition(const Vector3& position)
		{
			GetTransform()->SetPosition(position);
		}

		


		void LuaScriptComponent::SetThisComponent()
		{
			if (m_env)
			{
				(*m_env)["LuaComponent"] = this;
			}
		}

		void LuaScriptComponent::LoadScript(const std::string& fileName)
		{
			m_fileName = fileName;
			std::string physicalPath = m_fileName;
			if (!File::Exists(fileName))
			{
				LOG_ERROR("Failed to Load Lua script {0}", fileName);
				m_env = nullptr;
				return;
			}


			m_env = new sol::environment(LuaManager::GetInstance().GetState(), sol::create, LuaManager::GetInstance().GetState().globals());

			auto loadFileResult = LuaManager::GetInstance().GetState().script_file(physicalPath, *m_env, sol::script_pass_on_error);
			if (!loadFileResult.valid())
			{
				sol::error err = loadFileResult;
				LOG_ERROR("Failed to Execute Lua script {0}", physicalPath);
				LOG_ERROR("Error : {0}", err.what());

				std::string filename = File::GetFileName(m_fileName);
				std::string error = std::string(err.what());

				int line = 1;
				auto linepos = error.find(".lua:");
				std::string errorLine = error.substr(linepos + 5); //+4 .lua: + 1
				auto lineposEnd = errorLine.find(":");
				errorLine = errorLine.substr(0, lineposEnd);
				line = std::stoi(errorLine);
				error = error.substr(linepos + errorLine.size() + lineposEnd + 4); //+4 .lua:

				m_errors[line] = std::string(error);
			}
			else
				m_errors = {};

			if (!m_scene)
				m_scene = Application::GetCurrent().GetCurrentScene();

			(*m_env)["CurrentScene"] = m_scene;
			(*m_env)["LuaComponent"] = this;

			m_OnInitFunc = new sol::protected_function((*m_env)["OnInit"]);

			if (!m_OnInitFunc->valid())
			{

				LOG_ERROR("Lua : Invalid On Init");
				delete m_OnInitFunc;
			}

			m_UpdateFunc = new sol::protected_function((*m_env)["OnUpdate"]);
			if (!m_UpdateFunc->valid())
			{
				delete m_UpdateFunc;
			}


			LuaManager::GetInstance().GetState().collect_garbage();

		}

	
	
}