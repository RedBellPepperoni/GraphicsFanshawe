#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <string>

namespace FanshaweGameEngine
{
	class Model;

	namespace Components
	{

		class ModelComponent
		{

		public:
			
			explicit ModelComponent(const std::string filePath);


			



		private:

			ModelComponent();

			SharedPtr<Model> m_modelRef;


		};
	}

}