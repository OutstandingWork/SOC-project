#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "Renderer.h"
#include "Renderer1.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Renderer1.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);


    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        cout << "Error!" << endl;
    cout << glGetString(GL_VERSION) << endl;


    float position[] = { 100.0f, 100.0f,0.0f,0.0f,
        200.0f, 100.0f,1.0f,0.0f,
        200.0f,200.0f,1.0f,1.0f,
        100.0f, 200.0f,0.0f,1.0f };

    unsigned int indices[] = { 0,1,2
        ,2,3,0 };
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glEnable(GL_BLEND);

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));


    VertexArray va;
    VertexBuffer vb(position, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;



    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);





    IndexBuffer ib(indices, 6);

    

   
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8, 0.3f, 0.8f, 1.0f);

    Texture texture("res/textures/Proj stage 3.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);


    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();

    Renderer1 renderer;

    unsigned int a;
    glGenBuffers(1, &a);

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




    Renderer1 renderer1;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer1.clear();

        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
       
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 proj;
        proj = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);




        glm::mat4 mvp = proj *view* model;


        shader.Bind();
        shader.SetUniform4f("u_Color", 0.9, 0.3f, 0.8f, 1.0f);


        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);








        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}