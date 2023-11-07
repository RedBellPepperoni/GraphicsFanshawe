#pragma once
#include "Engine/Core/ECS/EntityManager.h"


namespace FanshaweGameEngine
{


	class Heirarchy
	{
	public:

		// This class can be added as a component later on which will have parent child relations
		Heirarchy(Entity parent);
		Heirarchy();


	};

	class SceneGraph
	{

	};


}