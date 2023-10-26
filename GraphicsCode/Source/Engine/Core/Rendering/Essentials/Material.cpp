#include "Material.h"

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		Material::Material()
			: albedoColour(Vector4(0.0f, 0.0f, 0.0f, 1.0f))
			, roughness (0.8f)
			, metallic (0.1f)
			, emissive (0.0f)
		{

		}

		Material::~Material()
		{
			
		}
	}
}