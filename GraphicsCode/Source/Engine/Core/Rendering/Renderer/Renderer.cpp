#include "Renderer.h"
#include "Engine/Core/System/Window/Window.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Core/Application/Application.h"

// Forward Declaration Headers
#include "Engine/Core/Rendering/Essentials/Material.h"
#include "Engine/Core/Rendering/Essentials/Mesh.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/Rendering/Buffers/VertexArray.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Rendering/Essentials/Camera.h"
#include "Engine/Core/Rendering/Shader/Shader.h"

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
                newElement.materialIndex = m_pipeline.MeshList.size();
                m_pipeline.MaterialList.push_back(material);
            }


           

            newElement.ModelMatrix = transform.GetLocalMatrix();


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


      

       

        void Renderer::RenderElements(SharedPtr<Shader> shader, const MaterialType type)
        {
            // Binding the VAO for the Particular Shader
           /* m_pipeline.VAO->Bind();*/


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


            SharedPtr<Mesh> mesh = m_pipeline.MeshList[element.meshIndex];

            uint32_t shaderId = shader->GetProgramId();
        

            shader->SetUniform("model", element.ModelMatrix);

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

        

        void Renderer::SetUpCameraElement(Camera& cameraRef, Transform& transform)
        {
            // Creating a new  Data only Camera element
            CameraElement camera;

            // Setting the details
            camera.aspectRatio = cameraRef.GetAspectRatio();
            camera.isOrtho = cameraRef.IsOrthographic();

            camera.viewPosition = transform.GetPosition();

//            Vector3 dir = camera.viewPosition + cameraRef->GetDirection();

            // For now , since the camera is not parented to anything. Later multiply the parent's transform to it
            Matrix4 view = Math::GetLookAt(camera.viewPosition, camera.viewPosition + cameraRef.GetDirection(), cameraRef.GetUpVector());
            Matrix4 proj = cameraRef.GetProjectionMatrix();
            Matrix4 projView = proj * view;

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
