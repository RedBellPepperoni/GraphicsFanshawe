#include "DisplayItem.h"
#include "Robotron/Units/UnitManager.h"

namespace Robotron
{
	DisplayItem::DisplayItem()
	{		

	}

	void DisplayItem::Setup(MeshComponent* mesh, Transform* trasnform)
	{
		displayMesh = mesh;
		transform = trasnform;
	}

	void DisplayItem::Update(float DeltaTime)
	{
		
		

		if(!shouldUpdate)
		{
			return;
		}

		

		countdown += DeltaTime;

		if (countdown >= disappeartime)
		{
			Hide();
			
		}



	}

	void DisplayItem::Display(Vector2 position)
	{
		transform->SetPosition(Vector3(position.x, 0.0f, position.y));
		displayMesh->isVisible = true;
		shouldUpdate = true;
		countdown = 0.0f;
	}

	

	void DisplayItem::Hide()
	{
		//transform->SetPosition(Vector3(100.0f, 0.0f, 100.0f));
		displayMesh->isVisible = false;
		shouldUpdate = false;
		
	}
}