#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

/*Vertex coords*/
GLfloat point[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

/*Vertex colors*/
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};


const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1)in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4 (vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main(){"
"   frag_color = vec4(color,1.0);"
"}";

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
     
    glClearColor(1,1,0,1);
    /*Create vertex shader vs*/
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    /*Source of vertex shader,1- stroke numbers, nullptr - lenght*/
    glShaderSource(vs,1,&vertex_shader, nullptr);
    /*Compile shader by OpenGl*/
    glCompileShader(vs);

    /*Create fragment shader vs*/
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    /*Source of fragment shader, nullptr - lenght*/
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    /*Compile fragment shader by OpenGl*/
    glCompileShader(fs);

    /* Link out value vertex shader with input value of fragment shader*/
    /*Generate shader program, return shader program identify*/
    GLuint shader_program = glCreateProgram();
    /*Attach fragment shader and vertex shader*/
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    /*For videocards drivers*/
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);// vbo -vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER,points_vbo); //make buffer as current
    glBufferData(GL_ARRAY_BUFFER,sizeof(point), point, GL_STATIC_DRAW);// for current GL_ARRAY_BUFFER 

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);// vbo -vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo); //make buffer as current
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);// for current GL_ARRAY_BUFFER

    GLuint vao = 0; //vao- vertex array objects 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);//set layout(location = 0)
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//0 -pointers ,3 -numbers of vertex, FLOAT- type, FALSE - not neded normalize

    glEnableVertexAttribArray(1);// layout(location = 1)
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);//works for current bind buffer


    /* Loop until the user closes the Window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);//Draw current bind vertex array objects
         
        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
    /*Release resources */
    glfwTerminate();
    return 0;
}