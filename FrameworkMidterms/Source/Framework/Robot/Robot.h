#pragma once
#include "Framework/Game/IDetector.h"
#include <Engine/Utils/Math.h>

using namespace FanshaweGameEngine;

namespace Framework 
{
	


	class Robot : public IDetector
	{
		enum class CardGame
		{
			ExplodingKitten,
			Enchure

		};


	public:

		explicit Robot(const int id, const Vector2Int& startposition);
		virtual ~Robot();

		void OnDetect(int otherId) override;
		void OnAction(int otherId, ActionType action) override;

		void UpdatePositon(const Vector2Int& newPos);

		const Vector2Int& GetGridPostion() const;


		const int GetId() const;
		

		const int GetFriendId() const;
		void SetFriendId(const int& Id);


		const bool ShouldMove() const;
		void SetShouldMove(const bool move);

		float currentCooldown = 1.0f;

		bool m_Greeted = false;

		CardGame currentCardGame;





	private:



		void ChangeColor(ActionType action);

		bool m_shouldMove = false;

		bool m_greetedfriend = false;

		Vector2Int m_gridPos;

		// The Id of the current Robot
		int m_robotID = -1;


		// The ID of the this robot's friend
		int m_friendlyRobotID = -1;

		// Ranges from 0 to 10
		int m_currentfriendShipValue = -1;



	};
}

