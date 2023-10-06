#include "Renderer.h"
#include "Engine/Core/System/Window/Window.h"

namespace FanshaweGameEngine
{

    namespace Rendering
    {


        void Renderer::DrawVertices(int vertexOffset, size_t vertexCount)
        {
            // Drawing all the vertices in tthe Vertex buffer
            // Hacky way to convert long long int to GLsizei which is somw how a vanilla int
            glDrawArrays(GL_TRIANGLES, vertexOffset, (GLsizei)vertexCount);

        }




        //void Renderer::LoadMeshToPipeline(const Mesh mesh)
        //{
        //    glGenBuffers(1, &vertex_buffer);
        //
        //    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        //
        //    unsigned int sizeVert = sizeof(Vertex);
        //
        //    size_t SizeOfVertex = sizeVert * mesh.expandedVertexArray.size();
        //
        //   
        //
        //    glBufferData(GL_ARRAY_BUFFER, SizeOfVertex, mesh.expandedVertexArray.data(), GL_STATIC_DRAW);
        //
        //    
        //    loadedMeshArray.push_back(mesh);
        //
        //
        //    CreateShader("shader01", "Assets\\vertexShader01.glsl" , "Assets\\fragmentShader01.glsl");
        //
        //    UseShader("shader01");
        //
        //   
        //
        //}

        void Renderer::DrawFrame()
        {
            /// Load All objects in vertex Buffers

            //m_activeCamera.Update(Application);



          //  glUseProgram(shaderProgramId);
            //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(m_activeCamera.GetMVP()));
           // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL /*GL_LINE*/ /*GL_FILL*/);


            // DrawVertices(0, loadedMeshArray[0].expandedVertexArray.size());
             /// Then Draw the vertices in buffer

        }

      

        void Renderer::UseShader(const std::string shaderName)
        {
           /* shaderProgramId = m_shaderManagerHandle->getIDFromFriendlyName(shaderName);

            printf("Using Shader ID:");

            mvp_location = glGetUniformLocation(shaderProgramId, "MVP");

            GLint vpos_location = glGetAttribLocation(shaderProgramId, "vPos");
            GLint vcol_location = glGetAttribLocation(shaderProgramId, "vCol");*/




        }

      /*  Camera Renderer::GetActiveCamera()
        {
            return m_activeCamera;
        }*/

        void Renderer::Initialize()
        {

            
            

        }
    }
}
