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
#include "Engine/Core/Rendering/Lights/PointLight.h"


namespace FanshaweGameEngine
{

    namespace Rendering
    {


        void Renderer::DrawVertices(uint32_t vertexOffset, size_t vertexCount)
        {
            // Drawing all the vertices in tthe Vertex buffer
            // Hacky way to convert long long int to GLsizei which is somw how a vanilla int
            GLDEBUG(glDrawArrays(GL_TRIANGLES, (GLint)vertexOffset, (GLsizei)vertexCount));
            //glDrawArrays(GL_TRIANGLES, (GLint)vertexOffset, (GLsizei)vertexCount);

        }


       
        void Renderer::Init()
        {
            // Creating a new Vertex Array Object foe the Pipeline
            m_pipeline.VAO = Factory<VertexArray>::Create();    


           // SharedPtr<TextureLibrary> lib = Application::GetCurrent().GetTextureLibrary();

           m_pipeline.defaultTextureMap = Application::GetCurrent().GetTextureLibrary()->LoadTexture("DefaultTexture", "Engine\\Textures\\DefaultTexture.png", TextureFormat::RGB);
            
             

        }

       


        void Renderer::DrawIndices(uint32_t indexCount, uint32_t indexOffset)
        {
            // Increase Drawcalls here
           
            

            // Drawing the Indices
            GLDEBUG(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));

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
            RenderElement newElement = RenderElement();

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
            m_pipeline.VAO = nullptr;

        }


      

       

        void Renderer::RenderElements(SharedPtr<Shader> shader, const MaterialType type)
        {
            // Binding the VAO for the Particular Shader
           /* m_pipeline.VAO->Bind();*/


            m_pipeline.MaterialList;


            int cameraIndex = Application::GetCurrent().GetMainCameraIndex();

            if (cameraIndex < 0)
            {
                LOG_WARN("No Rendering Cameras");
                return;
            }

           
            shader->Bind();

            // Getting the Selected camera's Index from the CameraList
            CameraElement camera = m_pipeline.cameraList[cameraIndex];

           
           

            // ============Set Shader Unifroms here ==================

            // Setting teh View Projection Matrix from the camera
            shader->SetUniform("viewProj", camera.viewProjMatrix);
            
      
            SetUpDirLightUniform(shader);
            SetUpSpotLights(shader);
            SetUpPointLightUniform(shader);

           //entt::registry& registry =  Application::GetCurrent().GetCurrentScene()->GetRegistry();

           //auto pointlightview = registry.view<PointLight>();
           //auto transformview = registry.view<Transform>();

           //int index = 0;

           //for (entt::entity Light: pointlightview)
           //{
           //    PointLight* light = &pointlightview.get<PointLight>(Light);
           //    Transform* transform = &transformview.get<Transform>(Light);

           //    SetUpPointLightUniform(shader, index, light, transform);
           //    index++;
           //}



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

     

        

        void Renderer::DrawElement(const CameraElement& camera, SharedPtr<Shader>& shader,const RenderElement& element)
        {
            int textureBindIndex = 0;

            uint32_t shaderId = shader->GetProgramId();


            SharedPtr<Mesh>& mesh = m_pipeline.MeshList[element.meshIndex];
            SharedPtr<Material>& mat = m_pipeline.MaterialList[element.materialIndex];

            if (mat != nullptr)
            {
                mat->textureMaps.albedoMap->Bind(textureBindIndex++);


                shader->SetUniform("matColor", mat->albedoColour);
                shader->SetUniform("mapAlbedo", mat->textureMaps.albedoMap->GetBoundId());
            }
            else
            {
                shader->SetUniform("matColor",Vector4(1.0f));
            }
          

        
           
            shader->SetUniform("model", element.ModelMatrix);

            shader->SetUniform("normalMat",element.NormalMatrix);

            shader->SetUniform("cameraView", camera.viewPosition);

            
            
           

            //Always Bind the Buffer Array before adding Attributes 
            mesh->GetVBO()->Bind();

            // Set the Shader Attributes
            m_pipeline.VAO->AddVertexAttributelayout(shaderId);

 
            // Bind the Index Buffer
            mesh->GetIBO()->Bind();


            DrawIndices(mesh->GetIndexCount(), 0);

            // Unbind all the bound buffers 
            mesh->GetIBO()->UnBind();
            mesh->GetVBO()->UnBind();

        }

        void Renderer::SetUpDirLightUniform(SharedPtr<Shader>& shader)
        {
            // Hardcoding for now
            shader->SetUniform("dirLight.direction", Vector3(60.0f, 40.0f, -40.0f));

            shader->SetUniform("dirLight.color", Vector3(0.0f, 0.6f, 1.0f));

            shader->SetUniform("dirLight.intensity", Vector3(0.5f));

            shader->SetUniform("dirLight.specular", Vector3(0.8f));

            //shader->SetUniform("lightList[0].properties", Vector4(2.0f, 0.0f, 0.0f, 0.0f));


        }

        void Renderer::SetUpPointLightUniform(SharedPtr<Shader>& shader)
        {
            Vector3 intensity = Vector3(0.9f);


            std::string uniformName = "pointLightList[0]";

            shader->SetUniform(uniformName + ".position", Vector3(-1.0f, 1.0f, 3.0f));
            shader->SetUniform(uniformName + ".color", Vector3(20.0f,1.0f,0.0f));
            shader->SetUniform(uniformName + ".intensity", intensity);
            shader->SetUniform(uniformName + ".constant", 1.0f);
            shader->SetUniform(uniformName + ".linear", 0.2f);
            shader->SetUniform(uniformName + ".quadratic", 0.27f);

          /*  uniformName = "pointLightList[1]";

            shader->SetUniform(uniformName + ".position", Vector3(20.0f, 8.0f, 8.0f));
            shader->SetUniform(uniformName + ".color", Vector3(0.0f, 1.0f, 0.0f));
            shader->SetUniform(uniformName + ".intensity", intensity);
            shader->SetUniform(uniformName + ".constant", 1.0f);
            shader->SetUniform(uniformName + ".linear", 0.003f);
            shader->SetUniform(uniformName + ".quadratic", 0.009f);*/

        }


        // Hardest of hard coding here :(
        void Renderer::SetUpSpotLights(SharedPtr<Shader>& shader)
        {
            Vector3 SpotLightPos_01 = Vector3(0.4f, 0.95f,-0.4f);
            Vector3 SpotLightColor_01 = Vector3(5.0f, 5.0f,0.0f);

            Vector3 SpotLightPos_02 = Vector3(0.4f, 0.95f, -1.6f);

     
           
          

            Vector3 intensity = Vector3(0.8f);


            std::string uniformName = "spotLightList[0]";
            shader->SetUniform(uniformName + ".position", SpotLightPos_01);
            shader->SetUniform(uniformName + ".color", SpotLightColor_01);
            shader->SetUniform(uniformName + ".intensity", intensity);
            shader->SetUniform(uniformName + ".direction", Vector3(1.0f,-0.4f,0.1f));
            shader->SetUniform(uniformName + ".cutOff", glm::cos(glm::radians(30.5f)));
            shader->SetUniform(uniformName + ".outerCutOff", glm::cos(glm::radians(35.5f)));
            shader->SetUniform(uniformName + ".constant", 1.0f);
            shader->SetUniform(uniformName + ".linear", 0.01f);
            shader->SetUniform(uniformName + ".quadratic", 0.032f);


            // Hard Penumbra

             uniformName = "spotLightList[1]";
            shader->SetUniform(uniformName + ".position", SpotLightPos_02);
            shader->SetUniform(uniformName + ".color", SpotLightColor_01);
            shader->SetUniform(uniformName + ".intensity", intensity);
            shader->SetUniform(uniformName + ".direction", Vector3(1.0f, -0.4f, 0.1f));
            shader->SetUniform(uniformName + ".cutOff", glm::cos(glm::radians(20.5f)));
            shader->SetUniform(uniformName + ".outerCutOff", glm::cos(glm::radians(35.0f)));
            shader->SetUniform(uniformName + ".constant", 1.0f);
            shader->SetUniform(uniformName + ".linear", 0.01f);
            shader->SetUniform(uniformName + ".quadratic", 0.032f);


            
            

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

            
            Matrix4 view = Math::Inverse(transform.GetLocalMatrix());

            Matrix4 proj = (cameraRef.GetProjectionMatrix());


            Matrix4 projView = proj * (view);

            // Set the View Projection matrix
            camera.viewProjMatrix = projView;


            m_pipeline.cameraList.push_back(camera);

       

        }


        const PipeLine Renderer::GetPipeLine() const
        {

            return m_pipeline;
        }
       
      
    }
}
