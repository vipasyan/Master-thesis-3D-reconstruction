#include <iostream>
#include <sstream>
#include <string>
// #define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include <vector>
#include "happly.h"
#include "Camera.h"
#include "Shader.h"

const char *APP_TITLE = "OpenGL Task";
int gWindowWidth = 1024;
int gWindowHeight = 768;
OrbitCamera orbitCamera;
float gRadius = 20.0f;
float gYaw = 215.0f;
float gPitch = 23.0f;

const double ZOOM_SENSITIVITY = 30.0;
const float MOVE_SPEED = 5.0; // units per second
const float MOUSE_SENSITIVITY = 0.2f;
glm::mat4 modelMat(1.0);

GLFWwindow *window = NULL;
glm::vec4 gClearColor(1.0f, 1.0f, 1.0f, 1.0f);
void initOpengl();
void readData(happly::PLYData &plyIn);
std::vector<glm::vec3> vert;
std::vector<glm::vec3> norm;
std::vector<glm::vec3> col;
void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mode);
void glfw_onMouseMove(GLFWwindow *window, double posX, double posY);
using namespace std;

int main(int argc, char **argv)
{
    initOpengl();
    happly::PLYData plyIn("L:\\proj\\models\\Lego.ply");
    //happly::PLYData plyIn("L:\\proj\\models\\Chair.ply");
    readData(plyIn);
    Shader basicShader;
    basicShader.loadShaders("shaders/basic_shader.vert", "shaders/basic_shader.frag");
    GLuint mVAO;
    GLuint mVBO_vert;
    GLuint mVBO_norm;
    GLuint mVBO_col;
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO_vert);
    glGenBuffers(1, &mVBO_norm);
    glGenBuffers(1, &mVBO_col);
    glBindVertexArray(mVAO);
    // vbo vertices info
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_vert);
    glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(glm::vec3), &vert[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(0);
    // vbo normal info
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_norm);
    glBufferData(GL_ARRAY_BUFFER, norm.size() * sizeof(glm::vec3), &norm[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(1);
    // vbo color info
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_col);
    glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec3), &col[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(2);

    // glBindVertexArray(mVAO);
    // // glBindBuffer(GL_ELEMEsNT_ARRAY_BUFFER, mEBO);
    // glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, (void *)0);
    // glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model(1.0), view(1.0), projection(1.0);

        orbitCamera.setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        orbitCamera.rotate(gYaw, gPitch);
        orbitCamera.setRadius(gRadius);
        view = orbitCamera.getViewMatrix();
        projection = glm::perspective(glm::radians(orbitCamera.getFOV()), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 200.0f);
        basicShader.use();
        basicShader.setUniform("model", model);
        basicShader.setUniform("view", view);
        basicShader.setUniform("projection", projection);

        glBindVertexArray(mVAO);
        glDrawArrays(GL_POINTS, 0, vert.size());
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;

    cout << "done";
}
void readData(happly::PLYData &plyIn)
{
    std::vector<double> vx_ = plyIn.getElement("vertex").getProperty<double>("x");
    std::vector<double> vy_ = plyIn.getElement("vertex").getProperty<double>("y");
    std::vector<double> vz_ = plyIn.getElement("vertex").getProperty<double>("z");
    std::vector<double> nx_ = plyIn.getElement("vertex").getProperty<double>("nx");
    std::vector<double> ny_ = plyIn.getElement("vertex").getProperty<double>("ny");
    std::vector<double> nz_ = plyIn.getElement("vertex").getProperty<double>("nz");
    std::vector<unsigned char> cr_ = plyIn.getElement("vertex").getProperty<unsigned char>("red");
    std::vector<unsigned char> cg_ = plyIn.getElement("vertex").getProperty<unsigned char>("green");
    std::vector<unsigned char> cb_ = plyIn.getElement("vertex").getProperty<unsigned char>("blue");
    for (int i = 0; i < vx_.size(); i++)
    {
        glm::vec3 v = glm::vec3(static_cast<float>(vx_[i]), static_cast<float>(vy_[i]), static_cast<float>(vz_[i]));
        glm::vec3 n = glm::vec3(static_cast<float>(nx_[i]), static_cast<float>(ny_[i]), static_cast<float>(nz_[i]));
        int red = static_cast<int>(cr_[i]);
        int green = static_cast<int>(cg_[i]);
        int blue = static_cast<int>(cb_[i]);
        float red_ = red / 255.0;
        float green_ = green / 255.0;
        float blue_ = blue / 255.0;
        glm::vec3 c = glm::vec3(red_, green_, blue_);
        vert.push_back(v);
        norm.push_back(n);
        col.push_back(c);
    }
    vx_.clear();
    vy_.clear();
    vz_.clear();
    nx_.clear();
    ny_.clear();
    nz_.clear();
    cb_.clear();
    cg_.clear();
    cr_.clear();
}
void initOpengl()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(gWindowWidth, gWindowHeight, "OpenGL-VBO", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }
    glfwMakeContextCurrent(window);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
        exit(0);
	}
    glfwSetKeyCallback(window, glfw_onKey);
    glfwSetCursorPosCallback(window, glfw_onMouseMove);

    glClearColor(gClearColor.r, gClearColor.g, gClearColor.b, gClearColor.a);
    glViewport(0, 0, gWindowWidth, gWindowHeight);
    glEnable(GL_DEPTH_TEST);
}

void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void glfw_onMouseMove(GLFWwindow *window, double posX, double posY)
{

    static glm::vec2 lastMousePos = glm::vec2(0, 0);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == 1)
    {
        gYaw -= ((float)posX - lastMousePos.x) * MOUSE_SENSITIVITY;
        gPitch += ((float)posY - lastMousePos.y) * MOUSE_SENSITIVITY;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == 1)
    {
        float dx = 0.01f * ((float)posX - lastMousePos.x);
        float dy = 0.01f * ((float)posY - lastMousePos.y);
        gRadius += dx - dy;
    }

    lastMousePos.x = (float)posX;
    lastMousePos.y = (float)posY;
}