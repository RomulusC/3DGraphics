#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
  private:
  GLFWwindow* m_window = nullptr;  
  struct WindowData
  {
    unsigned int m_width;
    unsigned m_height;
    std::string m_title;
    bool m_fullscreen;
  };
  WindowData m_data;

   public: 
	 

  // Initiates Window context using GLFW and GLEW
  Window(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, const std::string SCR_TITLE, const bool fullscreen);
 ~Window();
  GLFWwindow* GetWindow();
  int GetWidth();
  int GetHeight();

};
