#pragma once
#include "NarrowPhase.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"

#include "Engine/Core/Physics/Collision/Colliders/SphereCollider.h"
#include "Engine/Core/Physics/Collision/Colliders/MeshCollider.h"
#include "Engine/Utils/Logging/Log.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{

		


		NarrowPhase::NarrowPhase()
		{
			// making the binary value to the fill all the values with 1
			// right now max colliders is 32 (10000) so making it 63 which is (11111)

			m_MaxType = (ColliderType::MAX | (ColliderType::MAX >> 1));
		}

		NarrowPhase::~NarrowPhase()
		{
		}

		bool NarrowPhase::DetectCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, Collider* colliderOne, Collider* colliderTwo, CollisionData* outData)
		{
			// caching the types for faster computation
			ColliderType typeOne = colliderOne->GetType();
			ColliderType typeTwo = colliderTwo->GetType();

			if ((typeOne | typeTwo) > m_MaxType)
			{
				LOG_ERROR("INVALID Collider : {0} {1}", std::to_string(typeOne), std::to_string(typeTwo));
			}


			// Check Sphere Sphere First
			
			if ((typeOne & ColliderType::SPHERE) && (typeTwo & ColliderType::SPHERE))
			{
				// Reverse casting cuz its fun :(
				// This will Break a lot of stuff if teh casts are wrong
				return DetectSphereCollision(bodyOne, bodyTwo, colliderOne, colliderTwo, outData);
			}


			// If one of the object is a sphere and the other is either a box or mesh collider
			if ((typeOne & ColliderType::SPHERE && (typeTwo & ColliderType::MESH || typeTwo & ColliderType::BOX)) || (typeTwo & ColliderType::SPHERE && (typeOne & ColliderType::MESH || typeOne & ColliderType::BOX)))
			{
				

				return DetectSpherePolygonCollision(bodyOne, bodyTwo, colliderOne, colliderTwo, outData);
			}
			
			


			return false;
		}

		bool NarrowPhase::BuildCollisionManifold(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, Collider* colliderOne, Collider* colliderTwo, CollisionData& colData, Manifold* outManifold)
		{

			if (!outManifold)
			{			
				return false;
			}

			ManifoldPolygon poly1, poly2;
			colliderOne->GetManifoldPolygon(bodyOne, colData.collisionNormal, poly1);
			colliderTwo->GetManifoldPolygon(bodyTwo, -colData.collisionNormal, poly2);

			if (poly1.FaceCount == 0 || poly2.FaceCount == 0)
				return false;
			else if (poly1.FaceCount == 1)
				outManifold->AddContactPoint(poly1.Faces[0], poly1.Faces[0] - colData.collisionNormal * colData.penetration, colData.collisionNormal, colData.penetration);
			else if (poly2.FaceCount == 1)
				outManifold->AddContactPoint(poly2.Faces[0] + colData.collisionNormal * colData.penetration, poly2.Faces[0], colData.collisionNormal, colData.penetration);
			else
			{
				bool flipped;
				Vector3* incPolygon;
				int incPolygonCount;
				Plane* refAdjPlanes;
				int refAdjPlanesCount;
				Plane refPlane;

				if (Abs(Dot(colData.collisionNormal, poly1.Normal)) > Abs(Dot(colData.collisionNormal, poly2.Normal)))
				{
					float planeDist = -(Dot(poly1.Faces[0], -poly1.Normal));
					refPlane = Plane(-poly1.Normal, planeDist);

					refAdjPlanes = poly1.AdjacentPlanes;
					refAdjPlanesCount = poly1.PlaneCount;
					incPolygon = poly2.Faces;
					incPolygonCount = poly2.FaceCount;

					flipped = false;
				}
				else
				{
					float planeDist = -(Dot(poly2.Faces[0], -poly2.Normal));
					refPlane = Plane(-poly2.Normal, planeDist);

					refAdjPlanes = poly2.AdjacentPlanes;
					refAdjPlanesCount = poly2.PlaneCount;
					incPolygon = poly1.Faces;
					incPolygonCount = poly1.FaceCount;

					flipped = true;
				}

				SutherlandHodgesonClipping(incPolygon, incPolygonCount, refAdjPlanesCount, refAdjPlanes, incPolygon, incPolygonCount, false);
				SutherlandHodgesonClipping(incPolygon, incPolygonCount, 1, &refPlane, incPolygon, incPolygonCount, true);

				for (int i = 0; i < incPolygonCount; i++)
				{
					auto& endPoint = incPolygon[i];
					float contact_penetration;
					Vector3 globalOnA, globalOnB;

					if (flipped)
					{
						contact_penetration = -(Dot(endPoint, colData.collisionNormal)
							- (Dot(colData.collisionNormal, poly2.Faces[0])));

						globalOnA = endPoint + colData.collisionNormal * contact_penetration;
						globalOnB = endPoint;
					}
					else
					{
						contact_penetration = Dot(endPoint, colData.collisionNormal) - Dot(colData.collisionNormal, poly1.Faces[0]);

						globalOnA = endPoint;
						globalOnB = endPoint - colData.collisionNormal * contact_penetration;
					}

					outManifold->AddContactPoint(globalOnA, globalOnB, colData.collisionNormal, contact_penetration);
				}
			}
			return true;


			
		}

		

		bool NarrowPhase::CheckCollisionbySAT(const Vector3& axis, RigidBody3D* bodyOne, RigidBody3D* bodyTwo, Collider* colliderOne, Collider* colliderTwo, CollisionData* outData)
		{
			Vector3 minOne, maxOne;
			Vector3 minTwo, maxTwo;

			colliderOne->GetMinMaxFromAxis(bodyOne, axis, &minOne, &maxOne);
			colliderTwo->GetMinMaxFromAxis(bodyTwo, axis, &minTwo, &maxTwo);

			float minOneCorrelation = Dot(axis, minOne);
			float maxOneCorrelation = Dot(axis, maxOne);
			float minTwoCorrelation = Dot(axis, minTwo);
			float maxTwoCorrelation = Dot(axis, maxTwo);

			if (minOneCorrelation < minTwoCorrelation && maxOneCorrelation >= minTwoCorrelation)
			{
				if (outData != nullptr)
				{
					outData->collisionNormal = axis;
					outData->penetration = minTwoCorrelation - maxOneCorrelation;
					outData->pointOnPlane = maxOne + outData->collisionNormal * outData->penetration;
				}

				return true;

			}

			if (minTwoCorrelation <= minOneCorrelation && maxTwoCorrelation > minOneCorrelation)
			{
				if (outData != nullptr)
				{
					outData->collisionNormal = -axis;
					outData->penetration = minOneCorrelation - maxTwoCorrelation;
					outData->pointOnPlane = minOne + outData->collisionNormal * outData->penetration;
				}

				return true;

			}


			
			return false;
		}

		bool NarrowPhase::DetectSphereCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, Collider* colliderOne, Collider* colliderTwo, CollisionData* outData)
		{
			CollisionData data;

			Vector3 axis = bodyTwo->GetPosition() - bodyOne->GetPosition();

			if (Length(axis) > 0.1f)
			{
				axis = Normalize(axis);
			}

			if (!CheckCollisionbySAT(axis, bodyOne, bodyTwo, colliderOne, colliderTwo, &data))
			{
				return false;
			}
			   
			if (outData)
			{
				*outData = data;
			}

			return true;
		}

		bool NarrowPhase::DetectSpherePolygonCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, Collider* colliderOne, Collider* colliderTwo, CollisionData* outData)
		{
			if (!(colliderOne->GetType() & ColliderType::SPHERE || colliderTwo->GetType() & ColliderType::SPHERE))
			{

				LOG_ERROR("None of the colliders are spheres");
				return false;
			}

			Collider* complexShape;
			RigidBody3D* complexObj;
			RigidBody3D* sphereObj;

			if (bodyOne->GetCollider()->GetType() & ColliderType::SPHERE)
			{
				sphereObj = bodyOne;
				complexShape = colliderTwo;
				complexObj = bodyTwo;
			}
			else
			{
				sphereObj = bodyTwo;
				complexShape = colliderOne;
				complexObj = bodyOne;
			}

			CollisionData cur_colData;
			CollisionData best_colData;
			best_colData.penetration = -FLT_MAX;

			
			std::vector<Vector3>& shapeCollisionAxes = complexShape->GetCollisionNormals(complexObj);

			// The predefined Edgesof the triangles are checked here
			std::vector<ColliderEdge>& complex_shape_edges = complexShape->GetEdgeList(complexObj);

			Vector3 p = GetClosestPointOnEdges(sphereObj->GetPosition(), complex_shape_edges);
			Vector3 p_t = sphereObj->GetPosition() - p;
			p_t = Normalize(p_t);

			static const int MAX_COLLISION_AXES = 100;
			static Vector3 possibleCollisionAxes[MAX_COLLISION_AXES];

			uint32_t possibleCollisionAxesCount = 0;
			for (const Vector3& axis : shapeCollisionAxes)
			{
				possibleCollisionAxes[possibleCollisionAxesCount++] = axis;
			}

			AddPossibleCollisionAxis(p_t, possibleCollisionAxes, possibleCollisionAxesCount);

			for (uint32_t i = 0; i < possibleCollisionAxesCount; i++)
			{
				const Vector3& axis = possibleCollisionAxes[i];
				if (!CheckCollisionbySAT(axis, bodyOne, bodyTwo, colliderOne, colliderTwo, &cur_colData))
					return false;

				if (cur_colData.penetration > best_colData.penetration)
					best_colData = cur_colData;
			}

			if (outData)
				*outData = best_colData;


			

			return true;
		}



		Vector3 NarrowPhase::GetClosestPointOnEdges(const Vector3& target, const std::vector<ColliderEdge>& edges)
		{
			
			Vector3 closest_point, temp_closest_point;
			float closest_distsq = FLT_MAX;

			for (const ColliderEdge& edge : edges)
			{
				Vector3 a_t = target - edge.firstPosition;
				Vector3 a_b = edge.secondPosition - edge.firstPosition;

				// Magnitude of AB vector 
				float magnitudeAB = Dot(a_b, a_b);     
				
				// The DOT product of a_to_t and a_to_b
				float ABAPproduct = Dot(a_t, a_b);       

				// The Normalised "distance" from a to your closest point
				float distance = ABAPproduct / magnitudeAB; 

				// Clamp returned point to be on the line, e.g if the closest point is beyond the AB return either A or B as closest points

				if (distance < 0.0f) 
					temp_closest_point = edge.firstPosition;

				else if (distance > 1)
					temp_closest_point = edge.secondPosition;
				else
					temp_closest_point = edge.firstPosition + a_b * distance;

				Vector3 c_t = target - temp_closest_point;
				float temp_distsq = Dot(c_t, c_t);

				if (temp_distsq < closest_distsq)
				{
					closest_distsq = temp_distsq;
					closest_point = temp_closest_point;
				}
			}

			return closest_point;
		}


		void NarrowPhase::AddPossibleCollisionAxis(Vector3& axis, Vector3* possibleCollisionAxes, uint32_t& possibleCollisionAxesCount)
		{
			
			if (LengthSquared(axis) < 0.00001f)
				return;

			axis = Normalize(axis);

			float value = (1.0f - 0.00001f);

			for (uint32_t i = 0; i < possibleCollisionAxesCount; i++)
			{
				const Vector3& p_axis = possibleCollisionAxes[i];
				if (Abs(Dot(axis, p_axis)) >= value)
					return;
			}

			possibleCollisionAxes[possibleCollisionAxesCount++] = axis;
		}

		Vector3 NarrowPhase::PlaneEdgeIntersection(const Plane& plane, const Vector3& start, const Vector3& end) const
		{

			Vector3 ab = end - start;

			float ab_plane = Dot(plane.Normal(), ab);

			if (Abs(ab_plane) > 0.0001f)
			{
				Vector3 pointofContact = plane.Normal() * (-plane.Distance(Vector3(0.0f)));

				Vector3 width = start - pointofContact;
				float fac = -(Dot(plane.Normal(), width)) / ab_plane;
				ab = ab * fac;

				return start + ab;
			}

			return start;
		}


		// Clipping algo which starts as an infinite space and keeps clipping on each side

		void NarrowPhase::SutherlandHodgesonClipping(Vector3* inputPoly, int inputPolyCount, int clipPlaneCount, const Plane* clipPlanes, Vector3* outPoly, int& outPolyCount, bool removePoints) const
		{

			if (!outPoly)
				return;

			Vector3 ppPolygon1[8], ppPolygon2[8];
			int inputCount = 0, outputCount = 0;

			Vector3* input = ppPolygon1, * output = ppPolygon2;
			inputCount = inputPolyCount;
			output = inputPoly;
			outputCount = inputCount;

			for (int iterations = 0; iterations < clipPlaneCount; ++iterations)
			{
				if (outputCount == 0)
					break;

				const Plane& plane = clipPlanes[iterations];

				std::swap(input, output);
				inputCount = outputCount;

				outputCount = 0;

				Vector3 startPoint = input[inputCount - 1];
				for (int i = 0; i < inputCount; i++)
				{
					const auto& endPoint = input[i];
					bool startInPlane = plane.IsPointOnPlane(startPoint);
					bool endInPlane = plane.IsPointOnPlane(endPoint);

					if (removePoints)
					{
						if (endInPlane)
							output[outputCount++] = endPoint;
					}
					else
					{
						// if entire edge is within the clipping plane, keep it as it is
						if (startInPlane && endInPlane)
							output[outputCount++] = endPoint;

						// if edge interesects the clipping plane, cut the edge along clip plane
						else if (startInPlane && !endInPlane)
							output[outputCount++] = PlaneEdgeIntersection(plane, startPoint, endPoint);
						else if (!startInPlane && endInPlane)
						{
							output[outputCount++] = PlaneEdgeIntersection(plane, endPoint, startPoint);
							output[outputCount++] = endPoint;
						}
					}

					startPoint = endPoint;
				}
			}

			outPoly = output;
			outPolyCount = outputCount;

		}



	}
}