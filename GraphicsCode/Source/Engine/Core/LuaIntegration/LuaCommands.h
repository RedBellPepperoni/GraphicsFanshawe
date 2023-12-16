#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Singleton.h"
#include <vector>

namespace sol
{
	class state;
}




namespace FanshaweGameEngine
{

	enum CommandType
	{
		MoveTo,
		MoveTowards
	};

	class LuaCommands : public Singleton<LuaCommands>
	{
	public:

		//static void AddMoveCommand();


	private:


		static void MoveTo(const Vector3& position, const float time);
		static void MoveTowards(const Vector3& position, const float speed);


		static void OrientTo(const Vector3& rotation, const float time);
		static void OrientTowards(const Vector3& rotation, const float speed);

		static void AddWaypoint(const Vector3& position);

		static void FollowCurve(std::vector<Vector3> waypoints);


		static void OrientDirLight(const Vector3 rotation);
		static void ChangeDirLightIntensity(const float intensity);



	private:

		

	};

	


	

}

