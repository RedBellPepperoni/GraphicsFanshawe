#include "Window.h"
#include "Vertex.h"

#define GLFW_INCLUDE_NONE

#include "Math.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const unsigned int NumOfVertices = 3; 

Vertex vertices[NumOfVertices] =
{
    { Vector3( -0.6f, -0.4f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},
    { Vector3(0.6f, -0.4f, 0.f), Vector3(1.0f, 0.f,0.0f )},
    { Vector3(0.0f,  0.6f, 0.0f), Vector3(0.0f, 1.0f,0.0f) },
};
static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec3 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


Window::Window()
{
    width = 1280;
    height = 720;
    title = "OpenGl Window";

    Initialize();
}

Window::Window(int windowWidth, int windowHeight, const std::string& windowTitle)
{
    width = windowWidth;
    height = windowHeight;
    title = windowTitle;

    Initialize();
}

Window::~Window()
{
}


void Window::Update()
{
    
        float ratio;
        int width, height;
        Matrix4x4 m, p, v, mvp;

        glfwGetFramebufferSize(windowHandle, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);


        m = Matrix4x4(1.0f);

        p = glm::perspective(0.6f,
            ratio,
            0.1f,
            1000.0f);

        v = glm::mat4(1.0f);

        Vector3 cameraEye = Vector3(0.0, 0.0, -4.0f);
        Vector3 cameraTarget = Vector3(0.0f, 0.0f, 0.0f);
        Vector3 upVector = Vector3(0.0f, 1.0f, 0.0f);

        v = glm::lookAt(cameraEye,
            cameraTarget,
            upVector);


        mvp = p * v * m;

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
       
        glfwPollEvents();
       
    
}

void Window::Initialize()
{

    const unsigned int NumOfVertices = 3;
 
   
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    windowHandle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    
   
    if (!windowHandle)
    {
        glfwTerminate();

        std::cout << "MegaIssue";

        exit(EXIT_FAILURE);

       // isWindowOpen = false;
    }

    

    glfwSetKeyCallback(windowHandle, key_callback);

    glfwMakeContextCurrent(windowHandle);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    unsigned int SizeOfVertex = sizeof(Vertex) * NumOfVertices;

    glBufferData(GL_ARRAY_BUFFER, SizeOfVertex, vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location,
        3,                        // 2 floats 
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),                   //  sizeof(vertices[0]),
        (void*)offsetof(Vertex, position));    //  (void*)0);

    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),                  //  sizeof(vertices[0]),
        (void*)offsetof(Vertex, color));


    float xaxisRotation = 0.5;
    float yaxisRotation = 0.5;
    float zaxisRotation = 0.5;



    


}

bool Window::isOpen()
{
    if (windowHandle == nullptr)
    {
        // Log error here that the pointer to the wwindow doesnt exists    
        return false;
    }

    return !glfwWindowShouldClose(windowHandle);

}

void Window::SwapBuffers()
{
    glfwSwapBuffers(windowHandle);
    
}

void Window::CloseWindow()
{
    glfwDestroyWindow(windowHandle);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


