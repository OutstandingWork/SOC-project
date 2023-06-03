#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Renderer1.h"
using namespace std;









int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    
    
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


    float position[] = { -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,0.5f,
        -0.5f, 0.5f };

    unsigned int indices[] = { 0,1,2 
        ,2,3,0};

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));
    

    VertexArray va;
    VertexBuffer vb(position, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    
   
    
    layout.Push<float>(2);

    va.AddBuffer(vb,layout);
    
    
    
    

    IndexBuffer ib(indices, 6);
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8, 0.3f, 0.8f, 1.0f);
    
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

    float r = 0.0f;
    float increment = 0.05f;



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        renderer.Draw(va, ib, shader);
          
        
        
        

       if (r > 1.0f)
           increment = -0.05f;
       else if(r<0.0f)
           increment = 0.05f;

       r += increment;

       

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
  
    glfwTerminate();
    return 0;
}