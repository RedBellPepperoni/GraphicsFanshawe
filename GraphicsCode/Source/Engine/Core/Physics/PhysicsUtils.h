#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		

		 float Major(const Vector3& v) 
		 {
			float m = v.x;
			if (v.y > m) m = v.y;
			if (v.z > m) m = v.z;
			return m;
		 }

		 float Minor(const Vector3& v) 
		 {
			float m = v.x;
			if (v.y < m) m = v.y;
			if (v.z < m) m = v.z;
			return m;
		 }


	}
}

