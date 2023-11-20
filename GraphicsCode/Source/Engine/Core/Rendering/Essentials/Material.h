#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"
#include "Texture.h"
#include <string>

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
            SharedPtr<Texture> albedoMap;
            SharedPtr<Texture> normalMap;
            SharedPtr<Texture> aoroughMetalMap;
            SharedPtr<Texture> emissiveMap;
        };


		class Material
		{

        public:

            Material() = default;
            ~Material() = default;

            std::string name = "DefaultMaterial";

            Vector2 uvMultiplier{ 1.0f };

            Vector4 albedoColour{ 0.0f,0.0f,0.0f,1.0f };
            float roughness = 0.8f;
            float metallic = 0.1f;
            float emissive = 0.0f;

            float normalMapMultiplier = 1.0f;
            float emissiveMapMultiplier = 1.0f;

            MaterialType type = MaterialType::Opaque;

            MaterialTextures textureMaps;

            constexpr static size_t TextureCount = 4;

		};
	}
}

