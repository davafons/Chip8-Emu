#include <iostream>

#include "displayOpenGL.h"
#include "memory/memory.h"

const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec3 ppos;\n"
    "void main()\n"
    "{\n"
    "   ppos = aPos;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ppos;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ppos.x, ppos.y, ppos.z, 1.0f);\n"
    "}\n\0";

DisplayOpenGL::DisplayOpenGL(Memory &memory)
    : memory_(memory) {
  std::cout << "- Loading DisplayOpenGL.." << std::endl;

  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    throw SDL_GetError();

  window_ = SDL_CreateWindow("Chip-8 emulator", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, width_, height_,
                             SDL_WINDOW_OPENGL);

  if (!window_)
    throw SDL_GetError();

  context_ = SDL_GL_CreateContext(window_);
  SDL_GL_MakeCurrent(window_, context_);

  std::cout << "\t - Loading GLAD..." << std::endl;
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    throw SDL_GetError();
  std::cout << "\t - GLAD loaded." << std::endl;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetSwapInterval(1);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glViewport(0, 0, width_, height_);
  glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

  int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  int success;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    throw "\t - ERROR::SHADER::VERTEX::COMPILATION_FAILED: " +
        std::string(infoLog);
  }

  int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
    throw "\t - ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: " +
        std::string(infoLog);
  }

  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vertex_shader);
  glAttachShader(shader_program_, fragment_shader);
  glLinkProgram(shader_program_);

  glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
  if(!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(shader_program_, 512, NULL, infoLog);
    throw "\t - ERROR::SHADER::PROGRAM::LINKING_FAILED: " +
        std::string(infoLog);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
      // positions   // texCoords
      -1.0f,  1.0f,  0.0f, 1.0f,
      -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

      -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
  };

  glGenVertexArrays(1, &quadVAO_);
  glGenBuffers(1, &quadVBO_);

  glBindVertexArray(quadVAO_);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices,
      GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); glEnableVertexAttribArray(0);


  std::cout << "- DisplayOpenGL loaded." << std::endl;
}

DisplayOpenGL::~DisplayOpenGL() {
  SDL_GL_DeleteContext(context_);
  SDL_DestroyWindow(window_);
}

void DisplayOpenGL::toggleFullScreen() {
  std::cout << "TODO: Fullscreen" << std::endl;
}

void DisplayOpenGL::saveScreenshot() const {
  std::cout << "TODO: Screenshot" << std::endl;
}

void DisplayOpenGL::render() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shader_program_);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  SDL_GL_SwapWindow(window_);
}
