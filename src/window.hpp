#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "chf.hpp"

namespace WindowHandler
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);    

    //Initiates Window context using GLFW and GLEW
    GLFWwindow* SetUpWindow(const unsigned int SCR_WIDTH,const unsigned int SCR_HEIGHT,const std::string SCR_TITLE )
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
        #endif

        // glfw window creation
        // --------------------
        char str[SCR_TITLE.size()+1];
        strcpy(str, SCR_TITLE.c_str());
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, str, NULL, NULL);
        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            return nullptr;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        printf("Status: Using GLFW %i.%i.%i\n", major, minor, revision);    

        // glew: load all OpenGL function pointers
        // ---------------------------------------
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));               
            return nullptr;  
        }
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
        std::cout<<"GPU: " <<glGetString(GL_VERSION)<<std::endl;
        return window;
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes  
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

}
