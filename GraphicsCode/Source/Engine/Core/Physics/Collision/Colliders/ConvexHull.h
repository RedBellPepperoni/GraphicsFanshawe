#pragma once
#include "Engine/Utils/Math.h"
#include <vector>

namespace FanshaweGameEngine
{

	namespace Rendering
	{
		class Mesh;
	}

	using Rendering::Mesh;

	namespace Physics
	{

		// ============ Work on this later to simplfy mesh triangulation convex hull
		class ConvexHull
		{
		public:

			ConvexHull();
			~ConvexHull();

			void AddVertex(const Vector3& vertex);

			

		};

	}
}

