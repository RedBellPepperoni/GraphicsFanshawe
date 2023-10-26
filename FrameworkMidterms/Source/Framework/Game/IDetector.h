#pragma once

namespace Framework
{
	class IDetector
	{

	public:

		enum class ActionType : unsigned char
		{
			GreetFriend,
			PlayCard,
			GiveGift,

			Explode // Random stuff cuz my brain is fried at this point
		};


		IDetector() {};
		virtual ~IDetector() {};

		virtual void OnDetect(int otherId) = 0;
		virtual void OnAction(int otherId, ActionType action) = 0;
	};
}
