#include "Window.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>


namespace FanshaweGameEngine
{
    namespace Rendering
    {


    const unsigned int NumOfVertices = 3;



    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        const float CAMERA_MOVEMENT_SPEED = 0.1f;

        if (key == GLFW_KEY_A && action)
        {
            // InputLibrary::instance->isAPressed = true;
        }
        if (key == GLFW_KEY_D && action)
        {
            // cameraEye.x += CAMERA_MOVEMENT_SPEED;
        }

        if (key == GLFW_KEY_W && action)
        {
            //cameraEye.z += CAMERA_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_S && action)
        {
            // cameraEye.z -= CAMERA_MOVEMENT_SPEED;
        }


        if (key == GLFW_KEY_Q && action)
        {
            // cameraEye.y -= CAMERA_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_E && action)
        {
            // cameraEye.y += CAMERA_MOVEMENT_SPEED;
        }
        return;
    }

    static void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }



    Window::Window()
    {
        width = 1280;
        height = 720;
        title = "OpenGl Window";


    }

    Window::Window(int windowWidth, int windowHeight, const std::string& windowTitle)
    {
        width = windowWidth;
        height = windowHeight;
        title = windowTitle;


    }

    Window::~Window()
    {
    }


    void Window::UpdateViewPort()
    {



        glfwGetFramebufferSize(windowHandle, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // While drawing a pixel, see if the pixel that's already there is closer or not?
        glEnable(GL_DEPTH_TEST);




    }

    void Window::PollEvents()
    {

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

            // std::cout << "MegaIssue";

            exit(EXIT_FAILURE);

            // isWindowOpen = false;
        }



        glfwSetKeyCallback(windowHandle, key_callback);

        glfwMakeContextCurrent(windowHandle);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1);

        // NOTE: OpenGL error checks have been omitted for brevity






    }

    bool Window::isOpen()
    {
        if (windowHandle == nullptr)
        {
            // Log error here that the pointer to the wwindow doesnt exists    
           // printf("Error creating window");

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
    }
}





