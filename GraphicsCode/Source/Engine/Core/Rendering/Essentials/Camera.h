#pragma once
#include "Engine/Utils/Math.h"

#include <string>


namespace FanshaweGameEngine
{
    
	namespace Rendering
	{

		class Camera 
		{


        public:

            Camera();
            Camera(float FOV, float Near, float Far, float Aspect);
            Camera(float Aspect, float Near, float Far);
            ~Camera() = default;

            // Temporary defining the Transforms here until I switch to ECS
            //Transform m_transform;
            std::string m_name;

        public:

            const Matrix4& GetProjectionMatrix();
   

            const float GetZoom() const;
            void SetZoom(float zoom);

            void SetAspectRatio(float w, float h);
            void SetAspectRatio(float m_aspectRatio);
            const float GetAspectRatio() const;

            void SetOrthoSize(float size);
            const float GetOrthoSize() const;

            const float GetZFar() const;
            void SetZFar(float zFar);

            const float GetZNear() const;
            void SetZNear(float zNear);

            void SetOrthographic(bool ortho);
            const bool IsOrthographic() const;

            void SetDirection(const Vector3 vector);
            const Vector3& GetDirection() const;


            const Vector3& GetUpVector() const;
            const Vector3& GetRightVector() const;
            const Vector3& GetForwardVector() const;


        private:

            Vector3 m_upVector = Vector3(0.0f, 1.0f, 0.0f);
            Vector3 m_rightVector = Vector3(-1.0f, 0.0f, 0.0f);
            Vector3 m_forwardVector = Vector3(0.0f, 0.0f, 1.0f);
            Vector3 m_direction = Vector3(0.0f, 0.0f, 1.0f);


            void UpdateProjectionMatrix();
    
            bool m_shouldUpdateProjection = false;


            // Default aspect is 16:9
            float m_aspectRatio = 16.0f / 9.0f;
            float m_zoom = 1.0f;

            float m_orthosize = 1.0f;

          
            Matrix4 m_projection{ 1.0f };

 
            float m_fov = 60.0f;
            float m_near = 0.001f;
            float m_far = 1000.0f;

            float m_mouseSensitivity = 0.1f;
            float m_sensitivity = 250.0f;

            bool m_orthographic = false;

		
		};
	}
}
