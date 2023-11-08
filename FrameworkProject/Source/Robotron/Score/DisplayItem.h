#pragma once
#include "GameEngine.h"

namespace Robotron
{


	class DisplayItem
	{
	public:

		 DisplayItem();
		 

		~DisplayItem() {};

		void Setup(MeshComponent* mesh, Transform* trasnform);

		void Update(float DeltaTime);

		void Display(Vector2 postion);

		void Hide();


	private:

		

		float disappeartime = 2.0f;
		float countdown = 0.0f;

		bool shouldUpdate = false;

		MeshComponent* displayMesh;
		Transform* transform;


	};
}

