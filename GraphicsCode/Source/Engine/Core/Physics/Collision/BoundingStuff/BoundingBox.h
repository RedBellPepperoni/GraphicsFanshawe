#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	enum IntersectionResult : uint8_t
	{
		OUTSIDE			= 0,
		INSIDE			= 1,
		INTERSECTING	= 2
		
	};



	// Forward Declaration
	class BoundingSphere;

	class BoundingBox
	{

	public:

		BoundingBox();
		BoundingBox(const Vector3& min, const Vector3& max);
		BoundingBox(const BoundingBox& otherBox);

		~BoundingBox();

		// Resets the min and Mix for bounding box
		void Reset();


		BoundingBox& operator=(const BoundingBox& other);
		BoundingBox& operator=(BoundingBox&& other);

		void Set(const Vector3& min, const Vector3& max);

		void Translate(const Vector3& translation);

		void Scale(const Vector3& scale);

		void Rotate(const Matrix3& rotation);

		void Transform(const Matrix4& transform);

		BoundingBox GetTransformedBox(const Matrix4& transform);

		IntersectionResult CheckInterscetion(const BoundingBox& otherBox) const;

		IntersectionResult CheckInterscetion(const BoundingSphere& otherSphere) const;
		 
		void Merge(const Vector3& point);
		


		Vector3 Size() const;
		Vector3 Center() const;
		Vector3 Min() const;
		Vector3 Max() const;
		Vector3 GetExtents() const;




	private:

		Vector3 m_min;
		Vector3 m_max;


	};


}

