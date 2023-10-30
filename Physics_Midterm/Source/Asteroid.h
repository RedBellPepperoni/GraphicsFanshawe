#pragma once
#include "GameEngine.h"
#include "Explosion.h"

using namespace Physics;

class Asteroid
{

public:

	Asteroid(const std::string& newName, SharedPtr<Model> model ,const Vector3& position)
	{
		m_name = newName;
        Entity Object = Application::GetCurrent().GetCurrentScene()->CreateEntity(m_name);

        startPosi = position;

        Object.AddComponent<Transform>();

        m_transform = &Object.GetComponent<Transform>();
        m_transform->SetPosition(position);


        // So that the sphere kinda emcompasses teh asteroid
        m_transform->SetScale(Vector3(0.015));
        Object.AddComponent<MeshComponent>(model->GetMeshes()[0]);
        Object.AddComponent<MeshRenderer>();


        PhysicsProperties properties;

        properties.position = position;
        properties.stationary = false;
        properties.isStatic = false;
        properties.mass = 500.0f;


      

        m_body = &Object.AddComponent<RigidBody3D>(properties);
        SphereCollider* collider = &Object.AddComponent<SphereCollider>();
        collider->SetRadius(8.0f);
        m_body->SetCollider(*collider);

        // binding the Event callback for collision event
        m_body->m_OnCollisionCallback = std::bind(&Asteroid::OnHit, this);

        // Creating a new Explosion
        m_Explosion = MakeShared<Explosion>();




	}


 

    void OnHit()
    {
        if (!isHit)
        {

            m_Explosion->Explode(m_transform->GetPosition());

            m_body->SetForce(Vector3(0.0f));
            m_body->SetVelocity(Vector3(0.0f));

            m_transform->SetPosition(startPosi);
            m_body->SetPosition(startPosi);

            //isHit = true;


        }


	}

    RigidBody3D* getBody() 
    {
        return m_body;
    }


    void Update(float deltaTime)
    {
      
        m_Explosion->Update(deltaTime);
        MoveTowardsShip();
    }




private:


    void SpawnRandomDirection()
    {
        int xDir = rand() % (300 - 180 + 1) + 180;
        int yDir = rand() % (300 - 180 + 1) + 180;
        int zDir = rand() % (300 - 180 + 1) + 180;




    }

    void MoveTowardsShip()
    {
        if (m_body && m_transform)
        {
            // Direction towards Ship
            Vector3 force = Normalize( - m_transform->GetPosition());
            m_body->SetForce(force * forceMultiplier);
        }
    }

    std::string m_name;
    Transform* m_transform;
    RigidBody3D* m_body;
    bool isHit = false;
    float forceMultiplier = 10000.0f;
    SharedPtr<Explosion> m_Explosion;
   

    Vector3 startPosi;

};

