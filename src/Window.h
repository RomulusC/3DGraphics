#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


class SetUpWindow 
{
 public:
  // Initiates Window context using GLFW and GLEW
  SetUpWindow(const unsigned int SCR_WIDTH,
              const unsigned int SCR_HEIGHT,
              const std::string SCR_TITLE,
              GLFWwindow*& RETURN_WINDOW) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(
        GLFW_OPENGL_FORWARD_COMPAT,
        GL_TRUE);  // uncomment this statement to fix compilation on OS X
#endif

	RETURN_WINDOW = return_window(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE);
  }

 private:
  // glfw: whenever the window size changed (by OS or user resize) this callback
  // function executes
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
  }

  GLFWwindow* return_window(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, const std::string SCR_TITLE) 
  {
    // glfw window creation
    // --------------------
    GLFWwindow* window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE.c_str(), NULL, NULL);
    if (window == nullptr) {
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
    if (GLEW_OK != err) {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      return nullptr;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    std::cout << "GPU: " << glGetString(GL_VERSION) << std::endl;

	 if (window == nullptr) 
	 {
      glfwTerminate();
      std::cout << "Error: Failed to instantiate GLFW Window!\n";      
    }
    return window;
  }
};