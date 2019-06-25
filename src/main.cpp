#include "Shader.h"
#include "Window.h"
#include "vendors/stb_image/stb_image.h"
#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow* window);

int main() 
{
  // settings
  #define SCR_WIDTH 800
  #define SCR_HEIGHT 600
  #define SCR_TITLE "Sandbox"
  #define SHADER_PATH "../res/shader/Basic.shader"
  #define TEXTURE_PATH "../res/textures/container.jpg"
  #define TEXTURE_PATH2 "../res/textures/awesomeface.png"

  // Initiates Window context using GLFW and GLEW
  //--------------------------------------------
  GLFWwindow* window = nullptr;
  SetUpWindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE, window);
  //--------------------------------------------

  // Links vertex and fragment shaders and returns an int GL ID for the shader
  // program
  //--------------------------------------------
  int shaderProgram;
  InitShader(SHADER_PATH, &shaderProgram);
  if (shaderProgram == -1) 
  {
    std::cout << "Failed to Link Shaders!\n";
    return -1;
  }
  //glUniform1f(glGetUniformLocation(shaderProgram, "ourTexture"), 1.0f); 
  //--------------------------------------------

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glGenBuffers(1, &VBO));
    GLCall(glGenBuffers(1, &EBO));

    GLCall(glBindVertexArray(VAO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // position attribute
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));
    // texture coord attribute
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    GLCall(glEnableVertexAttribArray(1));
  //TEXTURE CONFIGURATION

  // load and create a texture
  // -------------------------
  unsigned int texture1, texture2;
  // texture 1
  // ---------
  GLCall(glGenTextures(1, &texture1));
  GLCall(glBindTexture(GL_TEXTURE_2D, texture1));
  // set the texture wrapping parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT));  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  // set texture filtering parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  // The FileSystem::getPath(...) is part of the GitHub repository so we can
  // find files on any IDE/platform; replace it with your own image path.
  unsigned char* data =
      stbi_load(TEXTURE_PATH, &width, &height, &nrChannels, 0);
  if (data) 
  {
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  // texture 2
  // ---------
  stbi_set_flip_vertically_on_load(
      true);  // tell stb_image.h to flip loaded texture's on the y-axis.
  GLCall(glGenTextures(1, &texture2));
  GLCall(glBindTexture(GL_TEXTURE_2D, texture2));
  // set the texture wrapping parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  // set texture filtering parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // load image, create texture and generate mipmaps
  data = stbi_load(TEXTURE_PATH2, &width,
      &height, &nrChannels, 0);
  if (data) 
  {
    // note that the awesomeface.png has transparency and thus an alpha channel,
    // so make sure to tell OpenGL the data type is of GL_RGBA
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
  } 
  else 
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  GLCall(glUseProgram(shaderProgram)); 
  GLCall(glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0));                   // set it manually
  GLCall(glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1));                   // set it manually
  
  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) 
  {
    // input
    // -----
    processInput(window);

    // render
    // ------
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
		
    // bind textures on corresponding texture units
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, texture1));
    GLCall(glActiveTexture(GL_TEXTURE1));
    GLCall(glBindTexture(GL_TEXTURE_2D, texture2));

    // transformations
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    GLCall(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)));


	  //render container      
    GLCall(glBindVertexArray(VAO));   
     
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  std::cout << "Application Succesfully terminated!\n";
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) 
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}