#include "Window.h"
#include "Renderer.h"

Window::Window(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, const std::string SCR_TITLE, const bool fullscreen) 
  {
    m_data = {SCR_WIDTH,SCR_HEIGHT,SCR_TITLE,fullscreen};    
	
    if(m_window!=nullptr)
    {     
      this->~Window();
      std::cout<<"Window already created!\n";      
    }
   
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

     // glfw window creation
    // --------------------
   
    if(m_data.m_fullscreen==false)
    {
      m_window = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), NULL, NULL);
      const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());    
      glfwSetWindowPos(m_window, (mode->width/2-(m_data.m_width/2)), (mode->height/2)-(m_data.m_height/2));
    }
    else
    {     
      const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); 
      m_window = glfwCreateWindow(mode->width, mode->height, m_data.m_title.c_str(), glfwGetPrimaryMonitor(), NULL);
    }
    
    
    if (m_window == nullptr) 
    {
      std::cout << "Failed to create GLFW window" << std::endl;          
    }   

    glfwMakeContextCurrent(m_window);

    glfwSetWindowUserPointer(m_window, &m_data);//Provides a reference pointer for access to (non static) class variable
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {      
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      data.m_width = width;
      data.m_height = height;
      GLCall(glViewport(0, 0, width, height)); 
    });

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Status: Using GLFW %i.%i.%i\n", major, minor, revision);

    // glew: load all OpenGL function pointers
    // ---------------------------------------
    GLenum err = glewInit();
    if (GLEW_OK != err) {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));      
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    std::cout << "GPU: " << glGetString(GL_VERSION) << std::endl;

	 if (m_window == nullptr) 
	 {
      glfwTerminate();
      std::cout << "Error: Failed to instantiate GLFW Window!\n";      
    }  
  }
  Window::~Window()
  {
    
    glfwDestroyWindow(m_window);
    glfwTerminate();
    m_window = nullptr;   
    std::cout<<"Status: Window destroyed!\n";
  }

   GLFWwindow* Window::GetWindow()
  {
    return this->m_window;
  }
  int Window::GetWidth()
  {     
    return m_data.m_width;
  }
  int Window::GetHeight()
  {    
    
    return m_data.m_height;
  }


