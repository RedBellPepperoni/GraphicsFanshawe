#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/System/Window/Window.h"


namespace FanshaweGameEngine
{

	namespace Rendering
	{

		class Camera 
		{
        public:

            Camera();
            Camera(float FOV, float Near, float Far, float aspect);
            Camera(float aspectRatio, float near, float far);
            ~Camera() = default;



        public:

            const Matrix4& GetProjectionMatrix();
            const Matrix4& GetViewMatrix();


            const float GetZoom() const;
            void SetZoom(float zoom);

            void SetAspectRatio(float w, float h);
            void SetAspectRatio(float ratio);
            const float GetAspectRatio() const;

            void SetOrthoSize(float size);
            const float GetOrthoSize() const;

            const float GetZFar() const;
            void SetZFar(float zFar);

            const float GetZNear() const;
            void SetZNear(float zNear);

            void SetOrthographic(bool ortho);


        private:

            void UpdateProjectionMatrix();
    
            bool m_shouldUpdateProjection = false;


            // Default aspect is 16:9
            float m_aspectRatio = 16.0f / 9.0f;
            float m_zoom = 1.0f;

            float m_orthosize = 1.0f;

           
            Matrix4 m_view{ 1.0f };
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
