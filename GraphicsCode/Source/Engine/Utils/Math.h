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
        // Randon Stuff




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




        template<typename T>
        inline auto Length(const T& value)
        {
            return glm::length(value);
        }

        template<typename T>
        inline auto LengthSquared(const T& value)
        {
            return glm::length2(value);
        }

        template<typename T>
        inline auto Distance(const T& v1, const T& v2)
        {
            return glm::distance(v1, v2);
        }

        template<typename T>
        inline auto DistanceSquared(const T& v1, const T& v2)
        {
            return glm::distance2(v1, v2);
        }


        inline float Square(float value)
        {
            return value * value;
        }

        template<typename T>
        inline constexpr T Clamp(const T& value, const T& low, const T& high)
        {
            return glm::clamp(value, low, high);
        }

        inline float Abs(float value)
        {
            return glm::abs(value);
        }

        inline Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float a)
        {
            return glm::lerp(q1, q2, a);
        }

        inline Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float a)
        {
            return glm::slerp(q1, q2, a);
        }

        template<typename T>
        inline constexpr T Radians(const T& degrees)
        {
            return glm::radians(degrees);
        }

        template<typename T>
        inline constexpr T Degrees(const T& radians)
        {
            return glm::degrees(radians);
        }

        template<typename T>
        inline constexpr T Pi()
        {
            return glm::pi<T>();
        }

        template<typename T>
        inline constexpr T Epsilon()
        {
            return glm::epsilon<T>();
        }

        // Gets an angle in radians between 2 vectors
        template<typename Vector>
        inline float Angle(const Vector& v1, const Vector& v2)
        {
            return std::acos(Dot(v1, v2) / (Length(v1) * Length(v2)));
        }


        // View Projection Matrix Stuff

        // Calculates and returns a Matrix , returns a 4x4 Matrix 
        inline Matrix4 GetLookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
        {
            return glm::lookAt(eye, center, up);
        }   

        // Calculates and Returns the Perspective Matrix, returns a 4x4 Matrix 
        inline Matrix4 CalculatePerspectiveMatrix(float fov, float aspect, float znear, float zfar)
        {
            return glm::perspective(glm::radians(fov), aspect, znear, zfar);
        }

        inline Matrix4 CalculateReversePerspective(float fov, float aspect, float znear, float zfar)
        {
            if (fov > 120.0f) { fov = 120.0f; }
            else if (fov < 0.10f) { fov = 0.10f; }

            float const tanHalfFov = std::tan(fov / 2.0f);
            float d = 1 / tanHalfFov;

            Matrix4 reversePerspective(
                d/aspect, 0.0f, 0.0f, 0.0f,
                0.0f, d, 0.0f, 0.0f,
                0.0f, 0.0f, -1.0f, 0.0f,
                0.0f, znear, 0.0f, 0.0f);

            return reversePerspective;
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


        // Matrix Processing functions // Just simplified wrappers

        // Returns a transpose of the give nMatrix
        template<typename Matrix>
        inline Matrix Transpose(const Matrix& mat)
        {
            return glm::transpose(mat);
        }

        // Returns a inverse of the give nMitrix
        template<typename Matrix>
        inline Matrix Inverse(const Matrix& mat)
        {
            return glm::inverse(mat);
        }



        // ===== Tranform Stuff ====
        inline Matrix4 Translate(const Matrix4& matrix, const Vector3& vector)
        {
            return glm::translate(matrix, vector);
        }

        inline Matrix4 Scale(const Matrix4& matrix, const Vector3& vector)
        {
            return glm::scale(matrix, vector);
        }

        inline Matrix4 Scale(const Matrix4& matrix, float value)
        {
            return glm::scale(matrix, Vector3(value));
        }

        inline Matrix4 Rotate(const Matrix4& matrix, float angle, const Vector3& axis)
        {
            return glm::rotate(matrix, angle, axis);
        }

        inline Quaternion Rotate(const Quaternion& quat, float angle, const Vector3& axis)
        {
            return glm::rotate(quat, angle, axis);
        }

        inline Matrix4 QuatToMatrix(const Quaternion& quat)
        {
            return glm::toMat4(quat);
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




        template<typename T>

        inline T Normalize(const T& value)
        {
            return glm::normalize(value);
        }



        template<typename T, typename U>
        inline constexpr decltype(std::declval<T>() + std::declval<U>()) Max(const T& v1, const U& v2)
        {
            return (v1 > v2 ? v1 : v2);
        }

        template<typename T, typename U, typename R>
        inline constexpr decltype(std::declval<T>() + std::declval<U>() + std::declval<R>()) Max(const T& v1, const U& v2, const R& v3)
        {
            return Max(Max(v1, v2), v3);
        }

        template<typename T, typename U>
        inline constexpr decltype(std::declval<T>() + std::declval<U>()) Min(const T& v1, const U& v2)
        {
            return (v1 < v2 ? v1 : v2);
        }

        template<typename T, typename U, typename R>
        inline constexpr decltype(std::declval<T>() + std::declval<U>() + std::declval<R>()) Min(const T& v1, const U& v2, const R& v3)
        {
            return Min(Min(v1, v2), v3);
        }


        template<typename T>
        inline T VectorMax(const T& v1, const T& v2)
        {
            T result(0.0f);
            for (typename T::length_type i = 0; i < result.length(); i++)
            {
                result[i] = std::max(v1[i], v2[i]);
            }
            return result;
        }

        template<typename T>
        inline T VectorMin(const T& v1, const T& v2)
        {
            T result(0.0f);
            for (typename T::length_type i = 0; i < result.length(); i++)
            {
                result[i] = std::min(v1[i], v2[i]);
            }
            return result;
        }





        // Computes pair of vectors with min and max coordinates in side a vertex array

        inline std::pair<Vector3, Vector3>MinMaxComponents(Vector3* verteces, size_t size)
        {
            Vector3 maxCoords(-1.0f * std::numeric_limits<float>::max());
            Vector3 minCoords(std::numeric_limits<float>::max());
            for (size_t i = 0; i < size; i++)
            {
                minCoords = VectorMin(minCoords, verteces[i]);
                maxCoords = VectorMax(maxCoords, verteces[i]);
            }
            return { minCoords, maxCoords };
        }

        
    }

    // Easily Accessible namespace to whichever class includes this .h file
    using namespace Math;

}

    
