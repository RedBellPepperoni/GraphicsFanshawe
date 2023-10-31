#pragma once
#include "GameEngine.h"
#include "Explosion.h"

using namespace Physics;

class Asteroid
{

public:

	Asteroid(const std::string& newName, SharedPtr<Model> model ,const Vector3& position, bool towardsShip = true)
	{
		m_name = newName;
        Entity Object = Application::GetCurrent().GetCurrentScene()->CreateEntity(m_name);

        startPosi = position;

        Object.AddComponent<Transform>();

        m_transform = &Object.GetComponent<Transform>();
        m_transform->SetPosition(position);


        // So that the sphere kinda emcompasses teh asteroid
        m_transform->SetScale(Vector3(0.015f));
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


        goToShip = towardsShip;

        ResetSpawn();


        


	}


 

    void OnHit()
    {
        if (!isHit)
        {
            m_Explosion->Explode(m_transform->GetPosition());
            //nucleonTransform->SetPosition(m_transform->GetPosition());
            ResetSpawn();

        }


	}

    RigidBody3D* getBody() 
    {
        return m_body;
    }


    void Update(float deltaTime)
    {
      
        m_Explosion->Update(deltaTime);

        Move(deltaTime);


    }



    void ApplyShieldForce()
    {   
        shieldDeflect = true;  
    }


private:

    void ResetSpawn()
    {
        m_body->SetForce(Vector3(0.0f));
        m_body->SetVelocity(Vector3(0.0f));
        
        Vector3 randomRotation = Vector3(rand() % 350, rand() % 360, rand() % 360);
       
        m_transform->SetPosition(startPosi);
        m_transform->SetRotation(randomRotation);
        m_body->SetPosition(startPosi);
        shieldDeflect = false;
    }
   


    void Move(float deltaTime)
    {
        if (m_body && m_transform)
        {
            if (Distance(Vector3(0.0f), m_body->m_position) > 500.0f)
            {
                ResetSpawn();
                return;
            }

            if (shieldDeflect)
            {
                Vector3 forceDir = Normalize(m_transform->GetPosition());
                m_body->SetForce(forceDir * 80000.0f);
                return;
                
            }


            if (goToShip)
            { // Direction towards Ship

                Vector3 newDir = Normalize(-m_transform->GetPosition());
                Vector3 force = Normalize(direction + (newDir * 0.6f));
                m_body->SetForce(force * forceMultiplier);
            }

            else
            {
                m_body->SetForce(Normalize(direction) * forceMultiplier);
               
            }


            Vector3 rotation = m_transform->GetEulerRotation();

         

           
        }
    }

    std::string m_name;
    Transform* m_transform;
    RigidBody3D* m_body;
    bool isHit = false;
    float forceMultiplier = 10000.0f;
    SharedPtr<Explosion> m_Explosion;
    

    Transform* nucleonTransform = nullptr;
   
    Vector3 direction = Vector3(0.0f,0.0f,-1.0f);

    
    
    bool goToShip = false;
    Vector3 startPosi;
    bool shieldDeflect = false;



};

