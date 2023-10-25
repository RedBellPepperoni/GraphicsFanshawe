#include "Window.h"
#include "Engine/Utils/GLUtils.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Engine/Core/System/Events/WindowEvent.h"
#include "Engine/Core/System/Events/KeyEvent.h"
#include "Engine/Core/System/Events/MouseEvent.h"
#include "Engine/Core/System/Input/InputKeyCodes.h"


namespace FanshaweGameEngine
{
    namespace Rendering
    {

        const unsigned int NumOfVertices = 3;

       

        static void error_callback(int error, const char* description)
        {
            fprintf(stderr, "Error: %s\n", description);
        }



        inline void Window::WindowSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
        {
            Window& handle = *static_cast<Window*>((glfwGetWindowUserPointer(window)));

            WindowResizeEvent resizeevent(Vector2Int(handle.m_properties.width, handle.m_properties.height), Vector2Int(newWidth, newHeight));
            handle.CallEvent(resizeevent);

        }

        inline void Window::WindowCloseCallback(GLFWwindow* window)
        {

            Window& handle = *static_cast<Window*>((glfwGetWindowUserPointer(window)));
            WindowCloseEvent event;

            handle.CallEvent(event);
           
        }

        inline void Window::WindowFocusCallback(GLFWwindow* window, int focus)
        {
            Window& handle = *static_cast<Window*>((glfwGetWindowUserPointer(window)));

            if (focus)
            {
                WindowFocusEvent event;
                handle.CallEvent(event);
            }
            else
            {
                WindowLostFocusEvent event;
                handle.CallEvent(event);
            }
        }

        inline void Window::WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {


            Window& handle = *static_cast<Window*>((glfwGetWindowUserPointer(window)));

        

            switch (action)
            {
              case GLFW_PRESS:
              {
                KeyDownEvent pressedevent(Input::OpenGLKeys::GetKeyboardKey(key), 0);
                handle.CallEvent(pressedevent);
                break;
              }

              case GLFW_RELEASE:
              {
                KeyUpEvent releasedevent(Input::OpenGLKeys::GetKeyboardKey(key));
                handle.CallEvent(releasedevent);
                break;
              }

              case GLFW_REPEAT:
              {
                KeyDownEvent repeatevent(Input::OpenGLKeys::GetKeyboardKey(key), 1);
                handle.CallEvent(repeatevent);
                break;
              }
            }

        }

      

       

        Window::Window()
        {
            m_properties.width = 1280;
            m_properties.height = 720;
            m_properties.title = "OpenGl Window!!";



        }

        Window::Window(const WindowProperties& properties)
            
        {
            m_properties.width = properties.width;
            m_properties.height = properties.height;
            m_properties.title = properties.title;

           

        }

        Window::~Window()
        {
        }


        void Window::UpdateViewPort()
        {

            glfwGetFramebufferSize(windowHandle, &m_properties.width, &m_properties.height);

            m_properties.aspectRatio = m_properties.width / (float)m_properties.height;

            GLDEBUG(glViewport(0, 0, m_properties.width, m_properties.height));
            GLDEBUG(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
            GLDEBUG(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));



            // While drawing a pixel, see if the pixel that's already there is closer or not?
            GLDEBUG(glEnable(GL_DEPTH_TEST));




        }

        void Window::PollEvents()
        {

            glfwPollEvents();
        }

        void Window::SetEventCallback(const EventCallBackFn& callback)
        {
            m_properties.eventHandler = callback;
        }

        void Window::CallEvent(EventBase& event)
        {


            if (!m_properties.eventHandler)
            { return; }

            m_properties.eventHandler(event);
        }

        void Window::Initialize()
        {

            const unsigned int NumOfVertices = 3;


            glfwSetErrorCallback(error_callback);

            if (!glfwInit())
                exit(EXIT_FAILURE);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            windowHandle = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), NULL, NULL);

           

            if (!windowHandle)
            {
                glfwTerminate();

                // std::cout << "MegaIssue";

                exit(EXIT_FAILURE);

                // isWindowOpen = false;
            }


            glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, true);

            glfwSetWindowUserPointer(windowHandle, this);
         


            glfwMakeContextCurrent(windowHandle);
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

            //glfwSetWindowSizeCallback(windowHandle, WindowSizeCallback);

            //glfwSetWindowCloseCallback(windowHandle, WindowCloseCallback);

           // glfwSetWindowFocusCallback(windowHandle, WindowFocusCallback);

            glfwSetKeyCallback(windowHandle, WindowKeyCallback);


            glfwSwapInterval(1);

            






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

        float Window::GetGLFWTime() const
        {
            return (float)glfwGetTime();
        }


        void Window::SetMousePosition(Vector2 position)
        {
            
            glfwSetCursorPos(windowHandle, position.x, position.y);
        }

        void Window::SetMouseHidden(bool isHidden)
        {
            if (isHidden)
            {
                glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else
            {
                glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
    }

    
}





