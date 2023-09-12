#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <cmath>
#include <array>
#include <algorithm>


    namespace Math {

        using Vector2 = glm::vec<2, float>;
        using Vector3 = glm::vec<3, float>;
        using Vector4 = glm::vec<4, float>;

        using Vector2Int = glm::vec<2, int>;
        using Vector3Int = glm::vec<3, int>;
        using Vector4Int = glm::vec<4, int>;

        using Matrix2x2 = glm::mat2x2;
        using Matrix2x3 = glm::mat2x3;
        using Matrix3x3 = glm::mat3x3;
        using Matrix2x4 = glm::mat2x4;
        using Matrix3x4 = glm::mat3x4;
        using Matrix4x4 = glm::mat4x4;

        using Quaternion = glm::quat;
   
    }
