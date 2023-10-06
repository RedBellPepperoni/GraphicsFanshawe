#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <cmath>
#include <array>
#include <algorithm>



namespace FanshaweGameEngine
{

    namespace Math
    {
        // Renaming glm variables into more Usable format
        using Vector2 = glm::vec<2, float>;
        using Vector3 = glm::vec<3, float>;
        using Vector4 = glm::vec<4, float>;

        using Vector2Int = glm::vec<2, int>;
        using Vector3Int = glm::vec<3, int>;
        using Vector4Int = glm::vec<4, int>;

        using Matrix2 = glm::mat2;
        using Matrix2x3 = glm::mat2x3;
        using Matrix3 = glm::mat3;
        using Matrix2x4 = glm::mat2x4;
        using Matrix3x4 = glm::mat3x4;
        using Matrix4 = glm::mat4;


    
        using Quaternion = glm::quat;


        // =================  Specific Fucntions for Vectors ===========================
        template<typename Vector>

        // Vector Mathematics

        // Calculate the Dot product of two vectors, returns a scalar float
        inline float Dot(const Vector& v1, const Vector& v2)
        {
            return glm::dot(v1, v2);
        }

        // Calculate the Cross product of two vectors, returns a vector that is perpendicular to both given vectors
        inline Vector3 Cross(const Vector3& v1, const Vector3& v2)
        {
            return glm::cross(v1, v2);
        }


        // View Projection Matrix Stuff

        // Calculates and returns a ViewMatrix, returns a 4x4 Matrix 
        inline Matrix4 GetViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up)
        {
            return glm::lookAt(eye, center, up);
        }

        // Calculates and Returns the Perspective Matrix, returns a 4x4 Matrix 
        inline Matrix4 CalculatePerspectiveMatrix(float fov, float aspect, float znear, float zfar)
        {
            return glm::perspective(glm::radians(fov), aspect, znear, zfar);
        }

        inline Matrix4 CalculateOrthoMatrix(float left, float right, float bottom, float top, float znear, float zfar)
        {
            return glm::ortho(left, right, bottom, top, znear, zfar);
        }

        // Returns a rotation , to rotate a matix so that it faces the given direction vector
        inline Quaternion LookAtRotation(const Vector3& direction, const Vector3& up)
        {
            return glm::quatLookAt(direction, up);
        }


        // Quaternion Stuff
        // Calculates and returns a rotation vaule from a 4X4 matrix
        inline Quaternion GetQuaternion(const Matrix4& rotationMat)
        {
            return glm::toQuat(rotationMat);
        }

        // Converts a Quaternion into a readable vector3 format
        inline Vector3 GetEularAngles(const Quaternion& quat)
        {
            return glm::eulerAngles(quat);
        }
    }

    // Easily Accessible namespace to whichever class includes this .h file
    using namespace Math;

}

    
