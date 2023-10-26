#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"

namespace FanshaweGameEngine
{
	namespace Rendering
	{

        class Shader;

        enum class MaterialType
        {
            Opaque,
            Transparent,
            Masked
        
        };


      

        struct MaterialTextures
        {
            // Create a Texture Class later ON
           // SharedPtr<Texture2D> albedo;
           // SharedPtr<Texture2D> normal;
           // SharedPtr<Texture2D> metallic;
           // SharedPtr<Texture2D> roughness;
           // SharedPtr<Texture2D> ao;
           // SharedPtr<Texture2D> emissive;
        };


		class Material
		{

        public:

            // Default Constructor
            Material();
            // Destructor
            ~Material();

            Vector4 albedoColour = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
            float roughness = 0.8f;
            float metallic = 0.1f;
            float emissive = 0.0f;

            float normalMapMultiplier = 1.0f;
            float emissiveMapMultiplier = 1.0f;

            MaterialType type = MaterialType::Opaque;



		};
	}
}

