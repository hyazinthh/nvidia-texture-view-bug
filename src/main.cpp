#include "main.h"

// Using a depth-only or color format is fine, using a depth-stencil format crashes.
constexpr auto FORMAT     = GL_DEPTH24_STENCIL8;
constexpr auto ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT;

// Using a texture view of layer 0 is fine, otherwise crashes.
constexpr auto TEXTURE_LAYER = 1;

int main() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Minimal GLFW OpenGL", nullptr, nullptr);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (gladLoadGL(glfwGetProcAddress) == 0) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

    // Texture Array
    GLuint textureArray;
    glGenTextures(1, &textureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, FORMAT, 512, 512, 2))

    // Texture views
    GLuint textureViews[2];
    glGenTextures(2, &textureViews[0]);
    GL_CHECK(glTextureView(textureViews[0], GL_TEXTURE_2D, textureArray, FORMAT, 0, 1, 0, 1))
    GL_CHECK(glTextureView(textureViews[1], GL_TEXTURE_2D, textureArray, FORMAT, 0, 1, 1, 1))

    // Framebuffer
    GLuint fbo;

    GL_CHECK(glGenFramebuffers(1, &fbo))
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo))

    GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, ATTACHMENT, GL_TEXTURE_2D, textureViews[TEXTURE_LAYER], 0))

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer is not complete\n");
        return -1;
    }

    // Render
    GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT))
    GL_CHECK(glFinish())

    // Cleanup
    GL_CHECK(glDeleteFramebuffers(1, &fbo))
    GL_CHECK(glDeleteTextures(2, &textureViews[0]))
    GL_CHECK(glDeleteTextures(1, &textureArray))

    glfwTerminate();

    printf("Program completed successfully\n");
    return 0;
}