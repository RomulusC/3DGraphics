#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);

int main()
{
  std::cout<<"Started...\n";
  if(!glfwInit())
  {
    std::cout<<"glfwInit failed!\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MAC OS COMPATIBILITY 

  GLFWwindow* window = glfwCreateWindow(1250,720, "Sandbox", NULL, NULL);
  if(window == nullptr)
  {
    std::cout<<"Failed to create GLFW Window!\n";
    glfwTerminate();
    return -1;
  }
    glfwMakeContextCurrent(window);
  
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout<<"Failed to initialize GLAD!\n";
      return -1;
    }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

  while(!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();    
  }

  glfwTerminate();
  return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

