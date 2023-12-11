#include "LuaMaths.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Utils/Math.h"
#include <sol/sol.hpp>

namespace FanshaweGameEngine
{
    using namespace Components;

	
		void BindLuaMaths(sol::state& state)
		{

            auto mult_overloads = sol::overload
            (

                [](const Vector3& v1, const Vector3& v2) -> Vector3 { return v1 * v2; },

                [](const Vector3& v1, float f) -> Vector3 { return v1 * f; },

                [](float f, const Vector3& v1) -> Vector3 { return f * v1; }
            );


            // ================== VECTOR 2 ==========================
			state.new_usertype<Vector2>
            (
				"Vector2", 
                sol::constructors<Vector2(float,float)>(),
				"x", &Vector2::x,
				"y", &Vector2::y,

                sol::meta_function::addition, [](const Vector2& a, const Vector2& b) { return a + b; },

                sol::meta_function::multiplication, [](const Vector2& a, const Vector2& b) { return a * b; },

                sol::meta_function::subtraction, [](const Vector2& a, const Vector2& b) { return a - b; },

                sol::meta_function::division, [](const Vector2& a, const Vector2& b) { return a / b; },

                sol::meta_function::equal_to, [](const Vector2& a, const Vector2& b) { return a == b; },

                "Length", [](const Vector2& v) { return Length(v); },
               
                "Distance", [](const Vector2& a, const Vector2& b) { return Distance(a, b); },
                
                "DistanceSquared", [](const Vector2& a, const Vector2& b) { return DistanceSquared(a, b); }
            );

         
			
            // ================================= VECTOR 3 ==========================================

            state.new_usertype<Vector3>
            (
               "Vector3",
               sol::constructors<sol::types<>, sol::types<float, float, float>>(),
               "x", &Vector3::x,
               "y", &Vector3::y,
               "z", &Vector3::z,

               sol::meta_function::addition, [](const Vector3& a, const Vector3& b) { return a + b; },
                
               sol::meta_function::multiplication, mult_overloads,

               sol::meta_function::subtraction, [](const Vector3& a, const Vector3& b) { return a - b; },
                
               sol::meta_function::unary_minus, [](Vector3& v) -> Vector3 { return -v; },
               
               sol::meta_function::division, [](const Vector3& a, const Vector3& b) { return a / b; },
                
               sol::meta_function::equal_to, [](const Vector3& a, const Vector3& b) { return a == b; },
                
               "Normalise", [](Vector3& v) { return Normalize(v); },
               
               "Length", [](const Vector3& v) { return Length(v); },
                
               "Distance", [](const Vector3& a, const Vector3& b) { return Distance(a, b); },
                
               "DistanceSquared", [](const Vector3& a, const Vector3& b) { return DistanceSquared(a, b); }
            );


            // ====================== VECTOR 4 ==============================

            state.new_usertype<Vector4>
            (
               "Vector4",
                sol::constructors<Vector4(), Vector4(float, float, float, float)>(),

                "x", &Vector4::x, 
                "y", &Vector4::y, 
                "z", &Vector4::z, 
                "w", &Vector4::w,

                sol::meta_function::addition, [](const Vector4& a, const Vector4& b) { return a + b; },
               
                sol::meta_function::multiplication, [](const Vector4& a, const Vector4& b)  { return a * b; },
               
                sol::meta_function::multiplication, sol::overload
                (
                    [](const Vector4& v1, const Vector4& v2) -> Vector4 { return v1 * v2; },
                    [](const Vector4& v1, float f) -> Vector4 { return v1 * f; },
                    [](float f, const Vector4& v1) -> Vector4 { return f * v1; }
                ),

                sol::meta_function::multiplication, [](float a, const Vector4& b) { return a * b; },
                
                sol::meta_function::subtraction, [](const Vector4& a, const Vector4& b) { return a - b; },
                
                sol::meta_function::division, [](const Vector4& a, const Vector4& b) { return a / b; },
              
                sol::meta_function::equal_to, [](const Vector4& a, const Vector4& b) { return a == b; },
                
                "Normalise", [](Vector4& v) { return Normalize(v); },
                
                "Length", [](const Vector4& v)  { return Length(v); },
                
                "Distance", [](const Vector4& a, const Vector4& b) { return Distance(a, b); },
                
                "DistanceSquared", [](const Vector4& a, const Vector4& b)  { return DistanceSquared(a, b); }
            
            );



            // =============== QUARTERNION ========================

            state.new_usertype<Quaternion>
            (
                "Quaternion",
                sol::constructors<Quaternion(float, float, float, float), Quaternion(Vector3)>(),
                "x", &Quaternion::x,
                "y", &Quaternion::y,
                "z", &Quaternion::z,
                "w", &Quaternion::w,

                sol::meta_function::addition, [](const Quaternion& a, const Quaternion& b) { return a + b; },

                sol::meta_function::multiplication, [](const Quaternion& a, const Quaternion& b) { return a * b; },
               
                sol::meta_function::subtraction, [](const Quaternion& a, const Quaternion& b) { return a - b; },
               
                sol::meta_function::equal_to, [](const Quaternion& a, const Quaternion& b)  { return a == b; },
                
                "Normalise", [](Quaternion& q) { return Normalize(q); }
            );

            // ====================== MATRIX 3x3 ===============

            state.new_usertype<Matrix3> 
            (
                "Matrix3",

                sol::constructors<Matrix3(float, float, float, float, float, float, float, float, float), Matrix3()>(), 

                sol::meta_function::multiplication, [](const Matrix3& a, const Matrix3& b) { return a * b; } 
            );

            // ================= MAtrix 4x4 ====================

            state.new_usertype<Matrix4> 
            (
                "Matrix4",
                sol::constructors<Matrix4(float), Matrix4()>(), 
               
                sol::meta_function::multiplication, [](const Matrix4& a, const Matrix4& b) { return a * b; },
               
                sol::meta_function::addition, [](const Matrix4& a, const Matrix4& b)  { return a + b; },
                
                sol::meta_function::subtraction, [](const Matrix4& a, const Matrix4& b) { return a - b; }
            );


            state.new_usertype<Transform>
            (
                 "Transform",
                 sol::constructors<Transform()>(),

                "Scale", & Components::Transform::GetScale,
                "Rotation", & Components::Transform::GetRotation,
                "EularRotation", & Components::Transform::GetEulerRotation,
                "Position", & Components::Transform::GetPosition,
                "SetPosition", & Components::Transform::SetPosition,
                "SetScale", & Components::Transform::SetScale,
                "SetRotation", & Components::Transform::SetRotation,
                "SetEularRotation", & Components::Transform::SetEularRotation,
                "GetForwardDirection", & Components::Transform::GetForwardVector,
                "GetRightDirection", & Components::Transform::GetRightVector


            );



           
		}

	
}