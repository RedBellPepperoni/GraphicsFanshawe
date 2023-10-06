#include "Camera.h"

namespace FanshaweGameEngine
{
    namespace Rendering
    {
        Camera::Camera()
            : m_aspectRatio(1.0f)
            , m_near(0.1f)
            , m_far(100.0f)
            , m_fov(60.0f)
            , m_orthographic(false)
        {
        }
        Camera::Camera(float FOV, float Near, float Far, float aspect)
            : m_aspectRatio(aspect)
            , m_fov(FOV)
            , m_near(Near)
            , m_far(Far)
            , m_orthographic(false)
        {
        }
        
        Camera::Camera(float aspectRatio, float, float)
            : m_aspectRatio(aspectRatio)
            , m_fov(60)
            , m_near(near)
            , m_far(far)
            , m_orthographic(true)
        {
        }

       
        const Matrix4& Camera::GetProjectionMatrix()
        {
            if (m_shouldUpdateProjection)
            {
                UpdateProjectionMatrix();
                m_shouldUpdateProjection = false;
            }

            return m_projection;
        }
        const Matrix4& Camera::GetViewMatrix()
        {
            return m_view;
        }
        
        const float Camera::GetZoom() const
        {
            return m_zoom;
        }
        void Camera::SetZoom(float zoom)
        {
            m_zoom = zoom;
            m_shouldUpdateProjection = true;
        }
        void Camera::SetAspectRatio(float width, float height)
        {
            SetAspectRatio(width / height);
        }
        void Camera::SetAspectRatio(float ratio)
        {
            m_aspectRatio = ratio;
            m_shouldUpdateProjection = true;
        }
        const float Camera::GetAspectRatio() const
        {
            return m_aspectRatio;
        }

        void Camera::SetOrthoSize(float size)
        {
            m_orthosize = size;
            m_shouldUpdateProjection = true;
        }

        const float Camera::GetOrthoSize() const
        {
            return m_orthosize;
        }

        const float Camera::GetZFar() const
        {
            return m_far;
        }
        void Camera::SetZFar(float zFar)
        {
            m_far = zFar;
            m_shouldUpdateProjection = true;
        }
        const float Camera::GetZNear() const
        {
            return m_near;
        }
        void Camera::SetZNear(float zNear)
        {
            m_near = zNear;
            m_shouldUpdateProjection = true;
        }

        void Camera::SetOrthographic(bool ortho)
        {
            m_orthographic = ortho;
            m_shouldUpdateProjection = true;
        }

        void Camera::UpdateProjectionMatrix()
        {
            if (m_orthographic)
            {
    
                m_projection = Math::CalculateOrthoMatrix(-m_aspectRatio * m_orthosize, m_aspectRatio * m_orthosize, -m_orthosize, m_orthosize, m_near, m_far);
            }

            else
            {
                m_projection = Math::CalculatePerspectiveMatrix(m_fov, m_aspectRatio, m_near, m_far);
            }
        }
    }
}
