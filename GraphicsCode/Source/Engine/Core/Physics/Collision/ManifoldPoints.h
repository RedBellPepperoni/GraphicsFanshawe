#include "Engine/Core/Physics/PhysicsUtils.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{

		struct ManifoldPoints 
		{
			Vector3 A;
			Vector3 B;
			Vector3 Normal;
			float Depth;
			bool HasCollision;

			ManifoldPoints()
				: A(0.0f)
				, B(0.0f)
				, Normal(0.0f)
				, Depth(0.0f)
				, HasCollision(false)
			{}

			ManifoldPoints(
				Vector2 a,
				Vector2 b
			)
				: A(a, 0.f)
				, B(b, 0.f)
				, HasCollision(true)
			{
				Vector2 ba = a - b;
				Depth = glm::length(ba);
				if (Depth > 0.00001f)
				{
					Normal = Vector3(ba / Depth, 0.f);
				}
				else {
					Normal = Vector3(0, 1, 0);
					Depth = 1;
				}
			}

			ManifoldPoints(
				Vector3 a,
				Vector3 b
			)
				: A(a)
				, B(b)
				, HasCollision(true)
			{
				Vector3 ba = a - b;
				Depth = glm::length(ba);
				if (Depth > 0.00001f)
				{
					Normal = ba / Depth;
				}
				else {
					Normal = Vector3(0, 1, 0);
					Depth = 1;
				}
			}

			ManifoldPoints(
				Vector3 a,
				Vector3 b,
				Vector3 n,
				float     d
			)
				: A(a)
				, B(b)
				, Normal(n)
				, Depth(d)
				, HasCollision(true)
			{}

			ManifoldPoints(
				Vector2 a,
				Vector2 b,
				Vector2 n,
				float     d
			)
				: A(a, 0)
				, B(b, 0)
				, Normal(n, 0.0f)
				, Depth(d)
				, HasCollision(true)
			{}

			void SwapPoints()
			{
				Vector3 t = A;
				A = B;
				B = t;
				Normal = -Normal;
			}
		};
	}
}
