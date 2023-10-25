#pragma once
#include "Engine/Utils/Math.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{
		// Stolen from Mr Feeney's Code
		struct Triangle
		{
			static const unsigned int NUMBER_OF_TRIANGLE_VERTICES = 3;

			Triangle()
			{
				vertices[0] = Vector3(0.0f);
				vertices[1] = Vector3(0.0f);
				vertices[2] = Vector3(0.0f);
			}

			Triangle(Vector3 v0, Vector3 v1, Vector3 v2)
			{
				vertices[0] = v0;
				vertices[1] = v1;
				vertices[2] = v2;
				ProcessNormal();
			}

			Triangle(Vector3 vertices[NUMBER_OF_TRIANGLE_VERTICES])
			{
				vertices[0] = vertices[0];
				vertices[1] = vertices[1];
				vertices[2] = vertices[2];
				ProcessNormal();
			}
			
			void ProcessNormal(void)
			{
				Vector3 v0_1 = vertices[1] - vertices[0];
				Vector3 v0_2 = vertices[2] - vertices[1];
				normal = Normalize(Cross(v0_1, v0_2));
				return;
			}
			
			Vector3 getCentre(void)
			{
				return ((vertices[0] + vertices[1] + vertices[2]) / (float)NUMBER_OF_TRIANGLE_VERTICES);
			}

			// ================= Variables ========

			Vector3 vertices[NUMBER_OF_TRIANGLE_VERTICES];
			Vector3 normal = Vector3(0.0f);

		};




		class MeshCollider
		{

			MeshCollider();
			virtual ~MeshCollider();





		};


	}
}


