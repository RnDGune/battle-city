#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


int g_windowSizeX = 640;
int g_windowSizeY = 480;

/*Function for resize window callback */
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSizeX = width;
    g_windowSizeY = height;
    /*Position where we want to print window, and it size */
    /*Start point is left,lower corner*/
    glViewport(0,0,g_windowSizeX,g_windowSizeY);
}

/*Function for key pushing callback */
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    /*If push escape*/
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cerr << "glfwInit error!\n";
        return -1;
    }

    /* Required 4.6 version of OpenGL*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    /* Use only actualy features, wihtout backward compatibility with older profile */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode Window and its OpenGL context */
    pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle City", nullptr, nullptr);
    if (!pWindow) 
    {
        std::cerr << "glfwCreateWindow() error!\n";
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the context OpenGl for current window,cause we can make a few windows*/
    glfwMakeContextCurrent(pWindow); 

    if(!gladLoadGL()){
        std::cerr<<"Can't load GLAD!\n";
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version:" << glGetString(GL_VERSION) << std::endl;
     
    glClearColor(0,1,1,1);

    /* Loop until the user closes the Window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
    /*Release resources */
    glfwTerminate();
    return 0;
}