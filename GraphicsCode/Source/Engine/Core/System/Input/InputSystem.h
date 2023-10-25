#pragma once
#include "Engine/Core/System/Events/Event.h"
#include "Engine/Core/System/Events/KeyEvent.h"
#include "Engine/Utils/Singleton.h"


namespace FanshaweGameEngine
{
	namespace Input
	{

#define MAX_KEYBOARD_KEYS 350

		class InputSystem : public Singleton<InputSystem>
		{
		public:
			 InputSystem();

			 // Virtual since it inherits from singleton
		     virtual ~InputSystem() = default;

			 void ProcessEvent(EventBase& event);

			 bool GetKeyDown(Key key) const { return keyboardKeysPressed[(int)key]; }
			 bool GetKeyHeld(Key key) const { return keyboardKeysHeld[(int)key]; }

			 void SetKeyDown(Key key, bool pressed) { keyboardKeysPressed[(int)key] = pressed; }
			 void SetKeyHeld(Key key, bool pressed) { keyboardKeysHeld[(int)key] = pressed; }


			 void ResetKeyPressed();
			 void ResetAll();

		protected:

			 bool OnKeyDown(KeyDownEvent& event);
			 bool OnKeyUp(KeyUpEvent& event);


		protected:

			 bool keyboardKeysPressed[MAX_KEYBOARD_KEYS];
			 bool keyboardKeysHeld[MAX_KEYBOARD_KEYS];


		};
	}
}

