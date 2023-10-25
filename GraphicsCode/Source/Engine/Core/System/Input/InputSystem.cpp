#include "InputSystem.h"


namespace FanshaweGameEngine
{
	

	namespace Input
	{

		bool InputSystem::OnKeyDown(KeyDownEvent& event)
		{
			
			SetKeyDown(Key(event.GetKeyCode()), event.GetRepeatCount() < 1);
			SetKeyHeld(Key(event.GetKeyCode()), true);

			return false;
		}


		bool InputSystem::OnKeyUp(KeyUpEvent& event)
		{
			SetKeyDown(Key(event.GetKeyCode()), false);
			SetKeyHeld(Key(event.GetKeyCode()), false);
			return false;
		}


		InputSystem::InputSystem()
		{
			ResetAll();
		}

		void InputSystem::ProcessEvent(EventBase& event)
		{
			EventDispatcher dispatcher(event);

			dispatcher.dispatch<KeyDownEvent>(BIND_FN(OnKeyDown));
			dispatcher.dispatch<KeyUpEvent>(BIND_FN(OnKeyUp));
			
		}

		void InputSystem::ResetKeyPressed()
		{
			memset(keyboardKeysPressed, 0, MAX_KEYBOARD_KEYS);
			memset(keyboardKeysHeld, 0, MAX_KEYBOARD_KEYS);
		}

		void InputSystem::ResetAll()
		{
			// Add mouse key reset here later
			ResetKeyPressed();
		}


		
	}
}