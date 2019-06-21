#pragma once
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <string>
#include "chf.h"

class InitShader {
 private:
  struct ShaderProgramSource {
    const std::string VertexSource;
    const std::string FragmentSource;
  };

  static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
      if (line.find("#shader") != std::string::npos) {
        if (line.find("vertex") != std::string::npos)
          type = ShaderType::VERTEX;
        else if (line.find("fragment") != std::string::npos)
          type = ShaderType::FRAGMENT;
      } else {
        ss[(int)type] << line << "\n";
      }
    }

    return {ss[0].str(), ss[1].str()};
  }

  int LinkShaders(const std::string filepath) {
    ShaderProgramSource source = ParseShader(filepath);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* x = source.VertexSource.c_str();
    glShaderSource(vertexShader, 1, &x, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                << infoLog << std::endl;
      system("pause");
      return -1;
    }

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    x = source.FragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &x, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                << infoLog << std::endl;

      return -1;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
      return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
  }

 public:
  // Links vertex and fragment shaders and returns an int GL ID for the shader
  // program, return -1 if linking failed
  InitShader(const std::string filepath, int* return_program) {
    *return_program = LinkShaders(filepath);    
  }
};
