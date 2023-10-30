#pragma once
#include "GameEngine.h"

class Explosion
{

public:

	Explosion()
	{
		GenerateSphere();
	}

	~Explosion()
	{

	}



	void Update(float deltaTime)
	{
		if(!m_shouldExplode)
		{
			return;
		}


		if (!m_hasFinishedExploding)
		{
			m_scale += deltaTime * 60.0f;

			if (m_sphereTrasnform)
			{
				m_sphereTrasnform->SetScale(Vector3(m_scale));
			}


				if (m_scale > m_maxScale)
				{
					m_scale = 0.001f;

					m_hasFinishedExploding = true;

					if (m_sphereTrasnform)
					{
						m_sphereTrasnform->SetScale(Vector3(m_scale));
						m_sphereTrasnform->SetPosition(Vector3(1000.0f));
						m_shouldExplode = false;
						return;
					}

				}


				


		}

	}

	

	void Explode(const Vector3& position)
	{
		if(m_sphereTrasnform)
		{
			m_scale = 0.001f;

			m_sphereTrasnform->SetPosition(position);
			m_sphereTrasnform->SetScale(Vector3(m_scale));

			m_shouldExplode = true;
			m_hasFinishedExploding = false;
		}

		
	}

	static int counter;

private:

	void GenerateSphere()
	{
		std::string name = "ExplosionSphere_" + std::to_string(counter);

		Entity Object = Application::GetCurrent().GetCurrentScene()->CreateEntity(name);
		// Add a Trasnform. later make sure every spawnd entity has an auto attached transform
		SharedPtr<Model> sphereModel = Application::GetCurrent().GetModelLibrary()->GetResource("Sphere");


		Object.AddComponent<Transform>();

		m_sphereTrasnform = &Object.GetComponent<Transform>();
		m_sphereTrasnform->SetPosition(Vector3(1000.0f));
		m_sphereTrasnform->SetScale(Vector3(0.1f));
		Object.AddComponent<MeshComponent>(sphereModel->GetMeshes()[0]);
		Object.AddComponent<MeshRenderer>();
		Object.GetComponent<MeshRenderer>().GetMaterial()->albedoColour = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		counter += 1;

	}


	float m_scale = 1.0f;
	float m_maxScale = 50.0f;
	Transform* m_sphereTrasnform = nullptr;

	bool m_shouldExplode = false;
	bool m_hasFinishedExploding = false;

	
};


