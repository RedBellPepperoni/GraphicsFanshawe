#pragma once
#include "Engine/Core/System/Input/FlyCameraController.h"
#include "Engine/Core/System/Input/OrbitalCameraController.h"
#include "Engine/Core/System/Input/CameraController.h"
#include "Engine/Core/Memory/Memory.h"

namespace FanshaweGameEngine
{
	class DefaultCameraController
	{

	public:

		enum class CameraType : uint8_t
		{
			FirstPerson = 0,
			ThirdPerson = 1,
			FlyCam = 2,
			Orbital = 3
		};

		DefaultCameraController()
			: m_type(CameraType::FlyCam)
		{
		}

		DefaultCameraController(CameraType type)
		{
			SetCameraType(type);
		}

		void SetCameraType(CameraType type)
		{
			m_type = type;

			switch (m_type)
			{
			case CameraType::FirstPerson:

				//m_cameraController = MakeShared<>

				break;
			case CameraType::ThirdPerson:
				break;
			case CameraType::FlyCam:

				m_cameraController = MakeShared<FlyCameraController>();
				break;


			case CameraType::Orbital:

				m_cameraController = MakeShared <OrbitalCameraController>();
				break;

			default:
				break;
			}
		}

		CameraType getType()
		{
			return m_type;
		}

		 SharedPtr<CameraController> GetController() 
		 {
			return m_cameraController;
		 }



	private:


		CameraType m_type = CameraType::FlyCam;
		SharedPtr<CameraController> m_cameraController;

	};

}