#include "Robot.h"
#include "Engine/Utils/Logging/Log.h"

namespace Framework
{
	Robot::Robot(const int id, const Vector2Int& startposition)
	  : m_robotID(id)
 	  , m_gridPos(startposition)
	{

	}

	Robot::~Robot()
	{

	}

	void Robot::OnDetect(int otherId)
	{
		
	}

	void Robot::OnAction(int otherId, ActionType action)
	{
		switch (action)
		{
		case Framework::IDetector::ActionType::GreetFriend:

			// Change Color Here
			//printf("ColorChanged");

			break;
		case Framework::IDetector::ActionType::PlayCard:
			break;
		case Framework::IDetector::ActionType::GiveGift:
			break;
		case Framework::IDetector::ActionType::Explode:
			break;
		default:
			break;
		}
	}

	void Robot::UpdatePositon(const Vector2Int& newPos)
	{
		m_gridPos = newPos;
	}

	const Vector2Int& Robot::GetGridPostion() const
	{
		return m_gridPos;
	}

	const int Robot::GetId() const
	{
		return m_robotID;
	}

	const int Robot::GetFriendId() const
	{
		return m_friendlyRobotID;
	}

	void Robot::SetFriendId(const int& Id)
	{
		m_friendlyRobotID = Id;

		LOG_WARN("Friend for {0} is : {1}", m_robotID, m_friendlyRobotID);
	}

	const bool Robot::ShouldMove() const
	{
		return m_shouldMove;
	}

	void Robot::SetShouldMove(const bool move)
	{
		m_shouldMove = move;
	}

	void Robot::ChangeColor(ActionType action)
	{

	}
}