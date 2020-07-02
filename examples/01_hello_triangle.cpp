#include "GLPGWindow.hpp"
#include "GLPGContext.hpp"
#include "utils/GLPGShaderUtils.hpp"
#include "utils/GLPGUtils.hpp"

using namespace GLPG;

const float vertexData[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const char *vertexShaderSource =
    "#version 450 core\n"
    "layout (location = 0) in vec3 vertexPosition;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(vertexPosition, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = 
    "#version 450 core\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    "   fragmentColor = vec4(1.0, 0.0, 0.0, 0.0);\n"
    "}\0";

int main()
{
    GLPGWindow win(640, 480);
    GLPGContext gc;
    GLuint VBO = 0;
    GLuint VAO = 0;
    GLuint vtxShaderObj = 0;
    GLuint fragShaderObj = 0;
    GLuint programObj = 0;

    if (!win.createNativeWindow()) {
        std::cout << "Failed to create Native Window" << std::endl;
        return -1;
    }

    if (!gc.initializeGlContext(win, 4, 6)) {
        std::cout << "Failed to initialize GL Context" << std::endl;
        return -1;
    }

    vtxShaderObj = glCreateShader(GL_VERTEX_SHADER);
    fragShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
    programObj = glCreateProgram();
    if (!compileShader(vtxShaderObj, vertexShaderSource)) {
        std::cout << "Vertex Shader Compilation Failed" << std::endl;
        return -1;
    }
    if (!compileShader(fragShaderObj, fragmentShaderSource)) {
        std::cout << "Fragment Shader Compilation Failed" << std::endl;
        return -1;
    }

    glAttachShader(programObj, vtxShaderObj);
    glAttachShader(programObj, fragShaderObj);

    if (!linkShaders(programObj)) {
        std::cout << "Failed to link Shaders" << std::endl;
        return -1;
    }

    glUseProgram(programObj);
    glEnable(GL_STENCIL_TEST);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFlush();
    gc.swapBuffers();
    while (1) {
        glClearColor(0.0, 1.0, 1.0, 1.0);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glClear(GL_COLOR_BUFFER_BIT);
        //glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        gc.swapBuffers();
    }
    return 0;
}
