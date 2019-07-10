#include "Shader.h"
#include "Window.h"
#include "vendors/stb_image/stb_image.h"
#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow* window);

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(int argc,char* argv[]) 
{ 
  // settings
  #define SCR_WIDTH 1920
  #define SCR_HEIGHT 1080
  
  #define SCR_TITLE "Sandbox"
  #define SHADER_PATH "../res/shader/Basic.shader"
  #define TEXTURE_PATH "../res/textures/container.jpg"
  #define TEXTURE_PATH2 "../res/textures/awesomeface.png"


  bool SCR_FULLSCREEN = false;  
       
    if(argc>=2) 
    { 
        for(int i = 0; i < argc; i++)
        {
          if(std::string(argv[i]) == "-f")
          {
            SCR_FULLSCREEN = true;
          }            
        }
    }

  // Initiates Window context using GLFW and GLEW
  //-------------------------------------------- 
  Window window = Window(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE, SCR_FULLSCREEN);
  //--------------------------------------------

 // build and compile our shader zprogram
	// ------------------------------------
  Shader ourShader(SHADER_PATH);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
  /* unsigned int indices[] = 
  {
	  0, 1, 3, // first triangle
	  1, 2, 3  // second triangle
  };
  */
  unsigned int VBO, VAO, EBO;
  GLCall(glGenVertexArrays(1, &VAO));
  GLCall(glGenBuffers(1, &VBO));
  GLCall(glGenBuffers(1, &EBO));

  GLCall(glBindVertexArray(VAO));

  GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

  //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
  //GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

  // position attribute
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
  GLCall(glEnableVertexAttribArray(0));
  // texture coord attribute
  GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
  GLCall(glEnableVertexAttribArray(1));


  // load and create a texture 
  // -------------------------
  unsigned int texture1, texture2;
  // texture 1
  // ---------
  GLCall(glGenTextures(1, &texture1));
  GLCall(glBindTexture(GL_TEXTURE_2D, texture1));
  // set the texture wrapping parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  // set texture filtering parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
  unsigned char* data = stbi_load(TEXTURE_PATH, &width, &height, &nrChannels, 0);
  if (data)
  {
	  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
	  GLCall(glGenerateMipmap(GL_TEXTURE_2D));
  }
  else
  {
	  std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  // texture 2
  // ---------
  GLCall(glGenTextures(1, &texture2));
  GLCall(glBindTexture(GL_TEXTURE_2D, texture2));
  // set the texture wrapping parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  // set texture filtering parameters
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // load image, create texture and generate mipmaps
  data = stbi_load(TEXTURE_PATH2, &width, &height, &nrChannels, 0);
  if (data)
  {
	  // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
	  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	  GLCall(glGenerateMipmap(GL_TEXTURE_2D));
  }
  else
  {
	  std::cout << "Failed to load texture\n";
  }
  stbi_image_free(data);

  // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
  // -------------------------------------------------------------------------------------------
  ourShader.use();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);

  glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f)  
};

  glEnable(GL_DEPTH_TEST);  

  

  // render loop
  // -----------
  std::cout << "Status: Render Loop Started!\n";
  while (!glfwWindowShouldClose(window.GetWindow()))
  {

    // per-frame time logic
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    
	  // input
	  // -----
	  processInput(window.GetWindow());

	  // render
	  // ------
	  GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	  GLCall(glClear(GL_COLOR_BUFFER_BIT));

	  // bind textures on corresponding texture units
	  GLCall(glActiveTexture(GL_TEXTURE0));
	  GLCall(glBindTexture(GL_TEXTURE_2D, texture1));
	  GLCall(glActiveTexture(GL_TEXTURE1));
	  GLCall(glBindTexture(GL_TEXTURE_2D, texture2));

    
    ourShader.use();
    // projection transformation
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(90.0f), float(window.GetWidth())/float(window.GetHeight()), 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    ourShader.setMat4("view", view);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  // render containers
    // model transformation
	  glBindVertexArray(VAO);
    for(unsigned int i = 0; i < 10; i++)
    {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i * sin((float)glfwGetTime()); 
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      ourShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }    

    //Assigning Shader Input
    /*/int modelLoc = glGetUniformLocation(ourShader.getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    */

    

	  // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	  // -------------------------------------------------------------------------------
	  glfwSwapBuffers(window.GetWindow());
	  glfwPollEvents();
    
    
  }
  std::cout << "Status: Render Loop End!\n";
  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  GLCall(glDeleteVertexArrays(1, &VAO));
  GLCall(glDeleteBuffers(1, &VBO));
  GLCall(glDeleteBuffers(1, &EBO));

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS)
        cameraPos.y -=1.0f*cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos.y +=1.0f*cameraSpeed;

   
}