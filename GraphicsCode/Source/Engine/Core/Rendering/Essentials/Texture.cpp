#include "Texture.h"
#include "Engine/Utils/GLUtils.h"
namespace FanshaweGameEngine
{
	namespace Rendering
	{
		GLenum GetGLFormat(TextureFormat format)
		{
			switch (format)
			{
			case FanshaweGameEngine::Rendering::TextureFormat::R:   return GL_R8;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::R16: return GL_R16;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RG: return GL_RG8;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RG16: return GL_RG16;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::R16F: return GL_R16F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::R32F: return GL_R32F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RG16F: return GL_RG16F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RG32F: return GL_RG32F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB: return GL_RGB;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA: return GL_RGBA;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB16: return GL_RGB16;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB16F: return GL_RGB16F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA16: return GL_RGBA16;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA16F:return GL_RGBA16F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB32F:return GL_RGB32F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA32F:return GL_RGBA32F;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::DEPTH:return GL_DEPTH_COMPONENT;
				break;
			case FanshaweGameEngine::Rendering::TextureFormat::DEPTH32F:return GL_DEPTH_COMPONENT32F;
				break;
			default:  return GL_RGB;
				break;
			}
		}


		GLint WrapTable[] =
		{
			 GL_CLAMP_TO_EDGE,
			GL_CLAMP_TO_BORDER,
			GL_MIRRORED_REPEAT,
			GL_REPEAT
		};


		void Texture::DeleteTexture()
		{
			if (m_textureId != 0)
			{
				GLDEBUG(glDeleteTextures(1, &m_textureId));
			}

			m_textureId = 0;
			m_activeId = 0;
		}


		Texture::Texture()
		{
			GLDEBUG(glGenTextures(1,&m_textureId));
		}


		Texture::~Texture()
		{
			DeleteTexture();
		}

		void Texture::Bind() const
		{
			GLDEBUG(glActiveTexture(GL_TEXTURE0 + m_activeId));
			GLDEBUG(glBindTexture(m_textureType, m_textureId));
			
		}

		void Texture::Bind(int id) const
		{
			m_activeId = id;
			Bind();
		}

		void Texture::UnBind() const
		{
			GLDEBUG(glActiveTexture(GL_TEXTURE0 + m_activeId));
			GLDEBUG(glBindTexture(m_textureType, 0));
		}

		int Texture::GetBoundId() const
		{
			return m_activeId;
		}
		uint32_t Texture::GetHandle() const
		{
			return m_textureId;
		}


		void Texture::Load(uint8_t* data, int width, int height, int channels, bool isFloating, TextureFormat format)
		{
			//m_filePath
		}


		void Texture::LoadDepth(int width, int height, TextureFormat format)
		{

		}

		void Texture::GenerateMipMaps()
		{
		}
		bool Texture::IsMuliSampled() const
		{
			return false;
		}
		bool Texture::IsFloatingPoint() const
		{
			switch (m_format)
			{
			case FanshaweGameEngine::Rendering::TextureFormat::R:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::R16:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::RG:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::RG16:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::R16F:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::R32F:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::RG16F:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::RG32F:
			    return true;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB16:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB16F:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA16:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA16F:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB32F:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA32F:
				return true;
			case FanshaweGameEngine::Rendering::TextureFormat::DEPTH:
				return false;
			case FanshaweGameEngine::Rendering::TextureFormat::DEPTH32F:
				return true;
			default:
				return false;
			}

		}
		bool Texture::IsDepthOnly() const
		{
			return m_format == TextureFormat::DEPTH || m_format == TextureFormat::DEPTH32F;
		}
		size_t Texture::GetWidth() const
		{
			return m_width;
		}
		size_t Texture::GetHeight() const
		{
			return m_height;
		}
		size_t Texture::GetChannelCount() const
		{
			switch (m_format)
			{
			case TextureFormat::R:
				return 1;
			case TextureFormat::R16:
				return 1;
			case TextureFormat::RG:
				return 2;
			case TextureFormat::RG16:
				return 2;
			case TextureFormat::R16F:
				return 1;
			case TextureFormat::R32F:
				return 1;
			case TextureFormat::RG16F:
				return 2;
			case TextureFormat::RG32F:
				return 2;
			case TextureFormat::RGB:
				return 3;
			case TextureFormat::RGBA:
				return 4;
			case TextureFormat::RGB16:
				return 3;
			case TextureFormat::RGB16F:
				return 3;
			case TextureFormat::RGBA16:
				return 4;
			case TextureFormat::RGBA16F:
				return 4;
			case TextureFormat::RGB32F:
				return 3;
			case TextureFormat::RGBA32F:
				return 4;
			case TextureFormat::DEPTH:
				return 1;
			case TextureFormat::DEPTH32F:
				return 1;
			default:
				return 0;
			}
		}
		size_t Texture::GetSampleCount() const
		{
			return m_samples;
		}
		size_t Texture::GetPixelSize() const
		{
			switch (m_format)
			{
			case FanshaweGameEngine::Rendering::TextureFormat::R:
				return 1;
			case FanshaweGameEngine::Rendering::TextureFormat::R16:
				return 2;
			case FanshaweGameEngine::Rendering::TextureFormat::RG:
				return 2;
			case FanshaweGameEngine::Rendering::TextureFormat::RG16:
				return 4;
			case FanshaweGameEngine::Rendering::TextureFormat::R16F:
				return 2;
			case FanshaweGameEngine::Rendering::TextureFormat::R32F:
				return 4;
			case FanshaweGameEngine::Rendering::TextureFormat::RG16F:
				return 4;
			case FanshaweGameEngine::Rendering::TextureFormat::RG32F:
				return 8;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB:
				return 3;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA:
				return 4;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB16:
				return 6;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB16F:
				return 6;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA16:
				return 8;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA16F:
				return 8;
			case FanshaweGameEngine::Rendering::TextureFormat::RGB32F:
				return 12;
			case FanshaweGameEngine::Rendering::TextureFormat::RGBA32F:
				return 16;
			case FanshaweGameEngine::Rendering::TextureFormat::DEPTH:
				return 1;
			case FanshaweGameEngine::Rendering::TextureFormat::DEPTH32F:
				return 4;
			default:
				return 1;
			}
		}
		TextureFormat Texture::GetFormat() const
		{
			return m_format;
		}

		TextureWraping Texture::GetWraping() const
		{


			GLint result = 0;
			Bind(0);

			GLDEBUG(glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &result));

			if (result == GL_REPEAT)
			{
				return TextureWraping::REPEAT;
			}
			else if (result == GL_CLAMP_TO_BORDER)
			{
				return TextureWraping::CLAMP_TO_BORDER;
			}
			else if (result == GL_MIRRORED_REPEAT)
			{
				return TextureWraping::MIRRORED_REPEAT;
			}
			
			return TextureWraping::CLAMP_TO_EDGE;
		}

		void Texture::SetWarping(TextureWraping wraping)
		{
			Bind(0);
			GLDEBUG(glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &WrapTable[(int)wraping]));
			GLDEBUG(glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &WrapTable[(int)wraping]));
		}

		uint32_t Texture::GetTextureType() const
		{
			return m_textureType;
		}
	}
}

