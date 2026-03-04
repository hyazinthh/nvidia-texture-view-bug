#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

static const char* glErrorString(const GLenum err) {
    switch (err) {
    case GL_NO_ERROR:                      return "GL_NO_ERROR";
    case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
    case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default:                               return "GL_UNKNOWN_ERROR";
    }
}

#define GL_CHECK(x) \
    x; \
    { \
        GLenum err; \
        while ((err = glGetError()) != GL_NO_ERROR) { \
            std::cerr << "OpenGL Error [" << glErrorString(err) << "] (0x" << std::hex << err << ") " \
                      << "in " << #x << " at " << __FILE__ << ":" << std::dec << __LINE__ << std::endl; \
        } \
    }