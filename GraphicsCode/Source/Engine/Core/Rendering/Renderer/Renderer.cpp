#include "Renderer.h"
#include "Engine/Core/System/Window/Window.h"
#include "Engine/Utils/Logging/Log.h"
//#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/Application/Application.h"

// Forward Declaration Headers
#include "Engine/Core/Rendering/Essentials/Material.h"
#include "Engine/Core/Rendering/Essentials/Texture.h"
#include "Engine/Core/Rendering/Essentials/Mesh.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/Rendering/Buffers/VertexArray.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Rendering/Essentials/Camera.h"
#include "Engine/Core/Rendering/Shader/Shader.h"

#include "Engine/Core/Rendering/Lights/Light.h"
#include "Engine/Core/Rendering/Buffers/VertexAttribute.h"
#include "Engine/Core/Rendering/Essentials/Cubemap.h"

#include "Engine/Core/Rendering/Renderer/DebugRenderer.h"
#include "Engine/Core/Rendering/Definitions.h"



namespace FanshaweGameEngine
{





    namespace Rendering
    {

        static const uint32_t MaxPoints = 10000;
        static const uint32_t MaxPointVertices = MaxPoints * 4;
        static const uint32_t MaxPointIndices = MaxPoints * 6;
        static const uint32_t MAX_BATCH_DRAW_CALLS = 100;
        static const uint32_t RENDERER_POINT_SIZE = sizeof(PointVertexElement) * 4;
        static const uint32_t RENDERER_POINT_BUFFER_SIZE = RENDERER_POINT_SIZE * MaxPointVertices;

        static const uint32_t MaxLines = 10000;
        static const uint32_t MaxLineVertices = MaxLines * 2;
        static const uint32_t MaxLineIndices = MaxLines * 6;
        static const uint32_t MAX_LINE_BATCH_DRAW_CALLS = 100;
        static const uint32_t RENDERER_LINE_SIZE = sizeof(LineVertexElement) * 4;
        static const uint32_t RENDERER_LINE_BUFFER_SIZE = RENDERER_LINE_SIZE * MaxLineVertices;

        static const uint32_t MAX_QUADS = 10000;

        enum class DrawType
        {
            POINTS = GL_POINTS,
            LINES = GL_LINES,
            TRIANGLES = GL_TRIANGLES
        };
      

        void Renderer::DrawVertices(const DrawType drawType, const uint32_t vertexOffset,const size_t vertexCount)
        {
            // Drawing all the vertices in tthe Vertex buffer
            // Hacky way to convert long long int to GLsizei which is somw how a vanilla int
            GLDEBUG(glDrawArrays((GLenum)drawType, (GLint)vertexOffset, (GLsizei)vertexCount));
            //glDrawArrays(GL_TRIANGLES, (GLint)vertexOffset, (GLsizei)vertexCount);

        }

        void Renderer::DrawIndices(const DrawType drawType, const uint32_t indexCount, const uint32_t indexOffset)
        {
            // Increase Drawcalls here
            // Drawing the Indices
            GLDEBUG(glDrawElements((GLenum)drawType, indexCount, GL_UNSIGNED_INT, nullptr));

        }


       
        void Renderer::Init()
        {
            // Initialize the Debug Renderer
            DebugRenderer::Init();

            // Creating a new Vertex Array Object foe the Pipeline
            m_pipeline.VAO = Factory<VertexArray>::Create();    
            m_debugDrawData.VAO = Factory<VertexArray>::Create();

            m_debugDrawData.VBO = Factory<VertexBuffer>::Create(UsageType::DYNAMIC_DRAW);

          
            

            // Hard coding for now
            // Realistically this should be set up for each shader when the shader gets compiled , probably?
            m_pipeline.vertexLayout =
            {
                VertexAttribute::Attribute<Vector3>(), // position
                VertexAttribute::Attribute<Vector2>(), // texture uv
                VertexAttribute::Attribute<Vector3>(), // normal
                VertexAttribute::Attribute<Vector3>(), // tangent
                VertexAttribute::Attribute<Vector3>(), // bitangent
            };


            m_debugDrawData.vertexLayout =
            {
                VertexAttribute::Attribute<Vector3>(), // Position
                VertexAttribute::Attribute<Vector4>(), // Color
            };


            m_debugDrawData.VBO->Bind();
            m_debugDrawData.VAO->Bind();
            m_debugDrawData.VAO->AddVertexAttribLayout(m_debugDrawData.vertexLayout);
           


           // SharedPtr<TextureLibrary> lib = Application::GetCurrent().GetTextureLibrary();

           // ============== LOADING TEXTURES =======================
           // Loading default Albedo texture
           Application::GetCurrent().GetTextureLibrary()->LoadTexture("DefaultAlbedoTexture", "Engine\\Textures\\DefaultTexture.png", TextureFormat::RGB);
           Application::GetCurrent().GetCubeMapLibrary()->LoadCubeMap("FieldSkybox", "Engine\\Textures\\fieldRight.png", "Engine\\Textures\\fieldLeft.png", "Engine\\Textures\\fieldTop.png", "Engine\\Textures\\fieldBottom.png", "Engine\\Textures\\fieldFront.png", "Engine\\Textures\\fieldBack.png");


           m_pipeline.defaultTextureMap = Application::GetCurrent().GetTextureLibrary()->GetResource("DefaultAlbedoTexture");
            
           m_pipeline.SkyboxCubeObject.Init();
   


           m_pipeline.skybox.cubeMap = Application::GetCurrent().GetCubeMapLibrary()->GetResource("FieldSkybox");
           m_pipeline.skybox.SetIntensity(1.20f);

        }


       

        void Renderer::SetupDebugShaders(SharedPtr<Shader>& line, SharedPtr<Shader>& point)
        {
            m_lineShader = line;
            m_pointShader = point;
        }

        
       



      


        void Renderer::SetSkyboxCubeMap(SharedPtr<CubeMap> cubemap)
        {
            if (cubemap == nullptr)
            {
                return;
            }

            m_pipeline.skybox.cubeMap = cubemap;
        }

        void Renderer::ProcessRenderElement(const SharedPtr<Mesh>& mesh, const SharedPtr<Material>& material,Transform& transform)
        {
            if (material->albedoColour.a <= 0.0f)
            {
                // The Element is Invisible ... shouldn't be drawn
                return;
            }

            // Storing the new Element's index
            size_t elementIndex = m_pipeline.renderElementList.size();

            // Creatig a temporarty Element
            RenderElement newElement;

            if (mesh != nullptr)
            {
                newElement.meshIndex = m_pipeline.MeshList.size();
                m_pipeline.MeshList.push_back(mesh);
            }

            if (material != nullptr)
            {
                newElement.materialIndex = m_pipeline.MaterialList.size();

                // For now just checking for albedo
                if (material->textureMaps.albedoMap == nullptr)
                {
                    material->textureMaps.albedoMap = m_pipeline.defaultTextureMap;
                }

                m_pipeline.MaterialList.push_back(material);
            }


            newElement.ModelMatrix = transform.GetLocalMatrix();

            // New!! - For lighting
            newElement.NormalMatrix = transform.GetNormalMatrix();
            

            // Getting the index of the element we are going to create
            size_t currentElementIndex = m_pipeline.renderElementList.size();

            // Storing the render Element in the container
            m_pipeline.renderElementList.push_back(newElement);



            switch (material->type)
            {
            case MaterialType::Opaque: 
                                
                // Storing the Render Element in the Opage container
                m_pipeline.opaqueElementList.push_back(elementIndex);

                break;

            case MaterialType::Transparent:
                break;

            case MaterialType::Masked:

                break;

            default:
                break;
            }




        }

      

      

        void Renderer::ClearRenderCache()
        {
            m_pipeline.cameraList.clear();
            m_pipeline.MaterialList.clear();
            m_pipeline.MeshList.clear();
            m_pipeline.opaqueElementList.clear();
            m_pipeline.renderElementList.clear();
            m_pipeline.lightElementList.clear();
            m_pipeline.textureBindIndex = 0;

        }

       

       

        void Renderer::ForwardPass(SharedPtr<Shader> shader,const CameraElement& camera , const MaterialType type)
        {
          
            if (shader == nullptr)
            {
                LOG_CRITICAL("FORWARD PASS : Material type :[{0}] : Shader not loaded", (int)type );
            }

           
            // ============Set Shader Unifroms here ==================
            shader->Bind();

   
            // Setting teh View Projection Matrix from the camera
            shader->SetUniform("viewProj", camera.viewProjMatrix);
            
      
            SetLightUniform(shader);


            std::vector<size_t> elementList;

            switch (type)
            {
            case MaterialType::Opaque: elementList = m_pipeline.opaqueElementList;

                break;
            default:
                break;
            }


            if(elementList.empty())
            {
                LOG_ERROR("No Eleemnts to Draw");
                return;
            }

            for (int index = 0; index < elementList.size(); index++)
            {
                // get the Elements by index from the Render Element List
                RenderElement elementToDraw = m_pipeline.renderElementList[elementList[index]];

                // Send the Data to Draw that element
                DrawElement(camera, shader, elementToDraw);
            }

            
           
        }

        void Renderer::SkyBoxPass(SharedPtr<Shader> shader, const CameraElement& camera)
        {

            if (shader == nullptr)
            {
                LOG_CRITICAL("SKYBOX PASS : Shader not loaded");
                return;
            }

            //Setting depth test to false (so that the skybox object will always be rendered last)
            GLDEBUG(glDepthMask(GL_FALSE));

            SkyboxObject& SkyObject = m_pipeline.SkyboxCubeObject;

            Vector3 radianRotaion = m_pipeline.skybox.GetRotation();
            radianRotaion.x = Radians(radianRotaion.x);
            radianRotaion.y = Radians(radianRotaion.y);
            radianRotaion.z = Radians(radianRotaion.z);

            Matrix3 inverseRotation = Transpose(MakeRotationMatrix(radianRotaion));

            // get the intensity from the pipeline
            float skyluminance = m_pipeline.skybox.GetIntensity();

            skyluminance = skyluminance < 0.0f ? Skybox::Defaultintensity : skyluminance;

            // Bind and set Shader Unifroms
            shader->Bind();
            shader->SetUniform("StaticViewProjection", camera.staticViewProjectMatrix);
            shader->SetUniform("Rotation", Matrix3(1.0f));
            shader->SetUniform("gamma", 2.2f);
            shader->SetUniform("luminance", skyluminance);

            // Bind the skybox texture
            m_pipeline.skybox.cubeMap->Bind();

            // Bind the Skybox Object VAO
            SkyObject.GetVAO().Bind();

            // Finally draw the Object
            DrawIndices(DrawType::TRIANGLES,SkyObject.IndexCount,0);


            //Setting depth test to back to true
            GLDEBUG(glDepthMask(GL_TRUE));



        }

        void Renderer::DebugPassInternal(const CameraElement& camera, bool depthtest)
        {
            const std::vector<DebugLineData>& lines = DebugRenderer::Get()->GetLines(depthtest);
            const std::vector<DebugPointData>& points = DebugRenderer::Get()->GetPoints(depthtest);
        
            // Skipping triangles for now

            Matrix4 projView = camera.viewProjMatrix;

            // ====== DEBUG LINE DRAW CALL ============
            if (!lines.empty())
            {
                m_lineShader->Bind();
                m_lineShader->SetUniform("projectionView", projView);


                for (const DebugLineData& line : lines)
                {
                    if(m_debugDrawData.lineIndexCount >= MAX_QUADS)
                    {
                        break;
                    }


                    m_debugDrawData.lineDataBuffer.emplace_back(line.posOne, line.color);
                    m_debugDrawData.lineDataBuffer.emplace_back(line.posTwo, line.color);

                    m_debugDrawData.lineIndexCount +=2;
                }

                

                uint32_t dataSize = (uint32_t) sizeof(LineVertexElement) * m_debugDrawData.lineIndexCount;

                m_debugDrawData.VBO->SetData(dataSize, m_debugDrawData.lineDataBuffer.data());
                m_debugDrawData.VAO->Bind();

                DrawVertices(DrawType::LINES,0, m_debugDrawData.lineIndexCount);

                m_debugDrawData.VBO->UnBind();

                
                
            }


        }
     
        void Renderer::DebugPass(const CameraElement& camera)
        {
            if (m_lineShader == nullptr || m_pointShader == nullptr)
            {
                return;
            }

            // Two Passes one for no depth and other for Depthtested
            DebugPassInternal(camera, true);
            //DebugPassInternal(camera, true);

            DebugRenderer::Reset();
 
        }

        

        void Renderer::DrawElement(const CameraElement& camera, SharedPtr<Shader>& shader,const RenderElement& element)
        {
            m_pipeline.textureBindIndex = 0;

            uint32_t shaderId = shader->GetProgramId();


            SharedPtr<Mesh>& mesh = m_pipeline.MeshList[element.meshIndex];
            SharedPtr<Material>& mat = m_pipeline.MaterialList[element.materialIndex];

            if (mat != nullptr)
            {
                mat->textureMaps.albedoMap->Bind(m_pipeline.textureBindIndex++);
                shader->SetUniform("mapAlbedo", mat->textureMaps.albedoMap->GetBoundId());
                shader->SetUniform("materialProperties.AlbedoMapFactor", mat->albedomapFactor);
                shader->SetUniform("materialProperties.AlbedoColor", mat->albedoColour);

            }
           
          
           // mat->textureMaps.albedoMap->UnBind();
        
           
            shader->SetUniform("model", element.ModelMatrix);

            shader->SetUniform("normalMat",element.NormalMatrix);

            shader->SetUniform("cameraView", camera.viewPosition);

            
            
           

            //Always Bind the Buffer Array before adding Attributes 
            mesh->GetVBO()->Bind();

            m_pipeline.VAO->Bind();

            // Set the Shader Attributes
            m_pipeline.VAO->AddVertexAttribLayout(m_pipeline.vertexLayout);
            //m_pipeline.VAO->AddVertexAttributelayout(shaderId);

            //m_pipeline.VAO->AddVertexAttribLayout();
 
            // Bind the Index Buffer
            mesh->GetIBO()->Bind();


            DrawIndices(DrawType::TRIANGLES,mesh->GetIndexCount(), 0);



            // Unbind all the bound buffers 
            mesh->GetIBO()->UnBind();
            mesh->GetVBO()->UnBind();

           

        }

        void Renderer::SetLightUniform(SharedPtr<Shader>& shader)
        {
           
            shader->SetUniform("uboLights.lightCount", (int)m_pipeline.lightElementList.size());
            

            for (LightElement element : m_pipeline.lightElementList)
            {

                const std::string colorUniform = element.uniformName + ".color";
                const std::string positionUniform = element.uniformName + ".position";
                const std::string directionUniform = element.uniformName + ".direction";
                const std::string intensityUniform = element.uniformName + ".intensity";
                const std::string radiusUniform = element.uniformName + ".radius";
                const std::string typeUniform = element.uniformName + ".type";

                
                const std::string innerAngleUniform = element.uniformName + ".innerAngle";
                const std::string outerAngleUniform = element.uniformName + ".outerAngle";


                shader->SetUniform(colorUniform, element.color);
               
               
                shader->SetUniform(intensityUniform, element.intensity);
                shader->SetUniform(typeUniform, (int)element.type);

                switch (element.type)
                {
                case FanshaweGameEngine::LightType::DirectionLight :
                    shader->SetUniform(directionUniform, element.direction);

                        break;
              
                case FanshaweGameEngine::LightType::SpotLight:
                    shader->SetUniform(innerAngleUniform, element.innerAngle);
                    shader->SetUniform(outerAngleUniform, element.outerAngle);
                    shader->SetUniform(positionUniform, element.position);
                    shader->SetUniform(directionUniform, element.direction);

                    break;
                case FanshaweGameEngine::LightType::PointLight:
                    shader->SetUniform(radiusUniform, element.radius);
                    shader->SetUniform(positionUniform, element.position);

                    break;
                default:
                    break;
                }
            }

            
            
        }

      
      
        

        void Renderer::SetUpCameraElement(Camera& cameraRef, Transform& transform)
        {

          

            // Creating a new  Data only Camera element
            CameraElement camera;

            // Setting the details
            camera.aspectRatio = cameraRef.GetAspectRatio();
            camera.isOrtho = cameraRef.IsOrthographic();

            camera.viewPosition = transform.GetPosition();

//          Vector3 dir = camera.viewPosition + cameraRef->GetDirection();

            // For now , since the camera is not parented to anything. Later multiply the parent's transform to it
            //Matrix4 view = Math::GetLookAt(camera.viewPosition, camera.viewPosition + cameraRef.GetDirection(), cameraRef.GetUpVector());


            Matrix4 transformMatrix = transform.GetLocalMatrix();
            
           // get the inverse of the Camera trasfrom
            Matrix4 view = Math::Inverse(transformMatrix);

            // get the inverse of the Camera transform without any position data (only Rotation0
            Matrix4 staticView = Math::Inverse(Matrix4(Matrix3(transformMatrix)));

            // the Projection of the camera
            Matrix4 proj = (cameraRef.GetProjectionMatrix());

             // calculate the vie projection matrix
            Matrix4 projView = proj * (view);

            //calculate the view projection of the static view (no positional data)
            Matrix4 staticProjView = proj * (staticView);

            // Store the values
            camera.viewProjMatrix = projView;
            camera.staticViewProjectMatrix = staticProjView;

            m_pipeline.cameraList.push_back(camera);

       

        }


        const PipeLine& Renderer::GetPipeLine() const
        {
            return m_pipeline;
        }




        void Renderer::ProcessLightElement(Light& light, Transform& transform)
        {
            size_t currentIndex = m_pipeline.lightElementList.size();

            // Create anew Light Element;
            LightElement& lightElement = m_pipeline.lightElementList.emplace_back();

            lightElement.color = light.color;
            lightElement.direction = light.direction = transform.GetForwardVector();
            lightElement.innerAngle = light.innerAngle;
            lightElement.outerAngle = light.outerAngle;
            lightElement.intensity = light.intensity;
            lightElement.position = light.position = transform.GetPosition();
            lightElement.radius = light.radius;
            lightElement.type = light.type;

            lightElement.uniformName = "uboLights.lights[" + std::to_string(currentIndex) + "]";



        }
       
      
    }
}
