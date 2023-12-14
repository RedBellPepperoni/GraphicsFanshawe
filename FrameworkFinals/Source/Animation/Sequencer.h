#pragma once
//#include "AnimationCurve.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include <string>
#include <vector>
#include "Engine/Utils/Logging/Log.h"

namespace FanshaweGameEngine
{
	using namespace Components;


	namespace Animation
	{


		struct Waypoint
		{

			Vector3 position;
			//Quaternion rotation;
			Vector3 rotation;

		};

		struct Sequence
		{
			std::string name;

			std::vector<Waypoint> waypointList;
			Transform* objectTransform;
			
			bool curve = false;

			bool objectVisible = true;
			bool play = false;
			bool playComplete = false;

			//float startTime = 0.0f;
			float duration = 1.0f;
			float seekTime = 0.0f;
			float startTime = 0.0f;

			template <typename T>
			inline T Bezier(float t, T p0, T p1, T p2, T p3)
			{
				return Cube(1 - t) * p0 + 3 * Square(1 - t) * t * p1 + 3 * (1 - t) * Square(t) * p2 + Cube(t) * p3;
			}



			void Update(const float animTime,const float deltaTime)
			{

				if (playComplete)
				{
					return;
				}

				if (animTime >= startTime)
				{
					play = true;
				}

				//Dont update
				if (!play)
				{
					return;
				}

				
				

				// will always be between 0 and 1
				float lerp = seekTime / duration;

				Vector3 nextPosition = Vector3(0.0f);
				Vector3 nextRotation = Vector3(0.0f);

				if (!curve)
				{
					nextPosition = Lerp(waypointList[0].position, waypointList[1].position, lerp);
					nextRotation = Lerp(waypointList[0].rotation, waypointList[1].rotation, lerp);
				}
				else
				{
					nextPosition = Bezier(lerp, waypointList[0].position, waypointList[1].position, waypointList[2].position, waypointList[3].position);
					nextRotation = Bezier(lerp, waypointList[0].rotation, waypointList[1].rotation, waypointList[2].rotation, waypointList[3].rotation);

				}
				
				objectTransform->SetPosition(nextPosition);
				objectTransform->SetEularRotation((nextRotation));

				seekTime = seekTime + deltaTime;

				

				if (seekTime >= duration)
				{
					play = false;
					playComplete = true;
					seekTime = 0.0f;
				}

				
				
			}

			

		};



		class Sequencer
		{

		public:

			void AddSequence(Sequence data);


			void Update(float deltaTime);

			void SetTotalDuration(float duration);

		private:

			std::vector<Sequence> m_SequenceList;

			float totalDuration = 0.0f;

			float currentSeek = 0.0f;

		};
	}
}

