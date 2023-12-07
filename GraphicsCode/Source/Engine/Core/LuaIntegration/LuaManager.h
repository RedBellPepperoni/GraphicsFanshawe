#pragma once
#include "Engine/Utils/Singleton.h"
#include <vector>

namespace sol
{
	class state;
}


namespace FanshaweGameEngine
{
	class Scene;

	class LuaManager : public Singleton<LuaManager>
		{

		public:


			LuaManager();
			~LuaManager();

			void OnInit();
			void OnInit(Scene* scene);
			void OnUpdate(Scene* scene);

			void BindLuaECS(sol::state& state);
			void BindLuaLog(sol::state& state);
			void BindLuaInput(sol::state& state);
			void BindLuaScene(sol::state& state);
			void BindLuaApplication(sol::state& state);

			static std::vector<std::string>& GetIdentifiers() 
			{
				return m_identifiers;
			}

			sol::state& GetState()
			{
				return *m_state;
			}

			static std::vector<std::string> m_identifiers;

		private:

			sol::state* m_state;
		};
	
}

