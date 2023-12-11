#include "XwingDirector.h"
#include "XWing.h"
#include "SphereTest.h"


namespace FanshaweGameEngine
{



	int XwingDirector::xwingcount = 0;

	static Vector3 GetRandomVector(const int minLength, const int maxLength)
	{
		int xDir = Random32::Range(-10, 10);
		int yDir = Random32::Range(-10, 10);
		int zDir = Random32::Range(-10, 10);

		Vector3 point = Normalize(Vector3(xDir, yDir, zDir)) * (float)Random32::Range(minLength, maxLength);

		return point;
	}

	static Vector3 GetSmartDirectionalVector(const int minLength, const int maxLength,const Vector3 origin)
	{
		int xDir = Random32::Range(-10, 10);
		int yDir = Random32::Range(-10, 10);
		int zDir = Random32::Range(-10, 10);

		// Pushes the point in the direction if it is inside the sphere
		Vector3 point = Normalize(Vector3(xDir, yDir, zDir)) * (float)Random32::Range(minLength, maxLength);

		Vector3 Dir = Normalize(point - origin);


		point = point + (Dir * 1000.0f);
		
		return point;
	}

	void XwingDirector::SpawnXWing()
	{
		Application& application = Application::GetCurrent();


		std::string name = "XWing_" + std::to_string(xwingcount);
		xwingcount++;

		Entity xwingEntity = application.GetCurrentScene()->CreateEntity(name);

		SharedPtr<Mesh> mesh = application.GetModelLibrary()->GetResource("XWing")->GetMeshes()[0];


		xwingEntity.AddComponent<MeshComponent>(mesh);
		SharedPtr<Material> material = xwingEntity.AddComponent<MeshRenderer>().GetMaterial();

		material->textureMaps.albedoMap = application.GetTextureLibrary()->GetResource("XWingAlbedo");
		material->metallic = 0.8f;


		/*SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create();
		collider->SetHalfDimensions(Vector3(3.6f, 1.0f, 40.0f));

		Matrix4 colliderTransform = Translate(Matrix4(1.0), Vector3(0.0f, 0.0f, -36.0f)) * Scale(Matrix4(1.0), collider->GetHalfDimensions());
			

		collider->SetTransform(colliderTransform);*/

		SharedPtr<SphereCollider> collider = Factory<SphereCollider>::Create();
		collider->SetRadius(3.6f);

		Matrix4 colliderTransform = Translate(Matrix4(1.0), Vector3(0.0f, 0.0f, -40.0f)) * Scale(Matrix4(1.0), Vector3(3.6f));


		collider->SetTransform(colliderTransform);


		PhysicsProperties properties;

		properties.collider = collider;
		properties.isStatic = false;
		properties.stationary = false;
		properties.mass = 5.0f;
		properties.position = Vector3(1000.0);
		properties.rotation = Quaternion(Radians(Vector3(0.0f, 0.0f, 0.0f)));
		properties.elasticity = 0.6f;
		properties.friction = 0.5f;
		properties.velocity = Vector3(0.0f);
		properties.tag = CollisionTag::Xwing;

		RigidBody3D* body = application.GetPhysicsEngine()->CreateRigidBody(xwingEntity, properties);

		

		XWing* xwingPtr =  &xwingEntity.AddComponent<XWing>();
		xwingPtr->SetRigidBody(body);
		xwingPtr->SetOnCollisionCallback(body);


		GetInstance().m_XwingList.push_back(xwingPtr);

	}

	void XwingDirector::SpawnTestSpherePair()
	{

		Application& application = Application::GetCurrent();


		std::string name = "TestSphere_01" ;

		Entity sphereEntity = application.GetCurrentScene()->CreateEntity(name);

		/*SharedPtr<Mesh> mesh = application.GetModelLibrary()->GetResource("Sphere")->GetMeshes()[0];


		sphereEntity.AddComponent<MeshComponent>(mesh);
		SharedPtr<Material> material = sphereEntity.AddComponent<MeshRenderer>().GetMaterial();*/



		SharedPtr<SphereCollider> spcollider = Factory<SphereCollider>::Create();
		//spcollider->SetHalfDimensions(Vector3(40.0f, 40.0f,40.0f));
		spcollider->SetRadius(80.0f);


		PhysicsProperties properties;

		properties.collider = spcollider;
		properties.isStatic = false;
		properties.stationary = false;
		properties.mass = 5.0f;
		properties.position = Vector3(0.0f,250.0f,0.0f);
		properties.rotation = Quaternion(Radians(Vector3(0.0f, 0.0f, 0.0f)));
		properties.elasticity = 0.6f;
		properties.friction = 0.5f;
		properties.velocity = Vector3(0.0f);
		properties.tag = CollisionTag::TestSphere;

		RigidBody3D* body = application.GetPhysicsEngine()->CreateRigidBody(sphereEntity, properties);
		//body->m_OnCollisionCallback = std::bind(&XwingDirector::OnSphereOneCollision, this, std::placeholders::_1, std::placeholders::_2);

		SphereTestOne = &sphereEntity.AddComponent<SphereTest>();
		SphereTestOne->SetRigidBody(body);
		
		name = "TestSphere_02";
		sphereEntity = application.GetCurrentScene()->CreateEntity(name);
		SharedPtr<SphereCollider>collider = Factory<SphereCollider>::Create();
		collider->SetRadius(6.0f);
		body = application.GetPhysicsEngine()->CreateRigidBody(sphereEntity, properties);
		body->m_OnCollisionCallback = std::bind(&XwingDirector::OnSphereTwoCollision, this, std::placeholders::_1, std::placeholders::_2);

		SphereTestTwo = &sphereEntity.AddComponent<SphereTest>();
		SphereTestTwo->SetRigidBody(body);


	}

	void XwingDirector::TempStartAll()
	{

		for (XWing* xwing : m_XwingList)
		{
			CalculateXWingPath(xwing);
		}
		
	}

	void XwingDirector::Update(float deltaTime)
	{

		for (XWing* xwing : m_XwingList)
		{
			xwing->Update(deltaTime);
		}


	}

	void XwingDirector::CalculateXWingPath( XWing* xwing)
	{
		// Calculate teh Startign pos
		CalculateOriginPoint();

		Vector3 startPos = SphereTestOne->GetRigidBody().GetPosition();
		

		CalculateTargetPoint(false);

		Vector3 targetPos = SphereTestTwo->GetRigidBody().GetPosition();

		Quaternion rot = LookAtRotation(Normalize(targetPos - startPos), Vector3(0.0f, 1.0f, 0.0f));


		// Set intial poition
		xwing->GetRigidBody().SetPosition(startPos);
		xwing->GetRigidBody().SetRotation(rot);
		

		xwing->SetOriginAndTatget(startPos,targetPos);
		xwing->FlyMission();

	}

	 void XwingDirector::CalculateOriginPoint()
	 {
		
		Vector3 point = GetRandomVector(850,1400);

		SphereTestOne->GetRigidBody().SetPosition(point);
	
		Quaternion rot = Quaternion();
		SphereTestOne->GetRigidBody().SetRotation(rot);
		
	 }



	void XwingDirector::CalculateTargetPoint(bool directedtowardsShieldGenerators)
	{
		Vector3 point = GetRandomVector(40, 300);

		SphereTestTwo->GetRigidBody().SetPosition(point);

		 point = GetSmartDirectionalVector(30,120, SphereTestOne->GetRigidBody().GetPosition());

		if (directedtowardsShieldGenerators)
		{ // Do stuff here
			//point = GetRandomVector(5,20);

		}

		SphereTestTwo->GetRigidBody().SetPosition(point);

		Quaternion rot = Quaternion();
		SphereTestTwo->GetRigidBody().SetRotation(rot);


	}




	void XwingDirector::SpawnWaypointTrails(const Vector2& firstPoint, const Vector2& secondPoint)
	{

	}
	void XwingDirector::LaunchXWing(const Vector2& targetPoint)
	{
	}

	bool XwingDirector::OnSphereOneCollision(RigidBody3D* body, Vector3 contactpoint)
	{
		LOG_WARN("SphereOne :  spawned INSIDE the destroyer.......Recalculating");

		return true;
	}

	bool XwingDirector::OnSphereTwoCollision(RigidBody3D* body, Vector3 contactpoint)
	{
		LOG_WARN("SphereTwo :  spawned INSIDE the destroyer.......Recalculating");

		return true;
	}

}