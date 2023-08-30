#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow*window, int width, int height) {
    glViewport(0,0,width,height);
    }

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
    "   void main()\n"
    "   {\n"
    "       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   }\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "   out vec4 FragColor;\n"
    "   void main()\n"
    "   {\n"
    "       FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "   }\n\0";

const char *fragmentYellowShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

int main() {
    
    

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn   OpenGl", NULL, NULL);
    if(window == NULL){
        cout<<"Failed to create GLFW WINDOW"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD"<<endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    

    //Orange Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Yellow Shader
    unsigned int fragmentYellowShader;
    fragmentYellowShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentYellowShader, 1, &fragmentYellowShaderSource, NULL);
    glCompileShader(fragmentYellowShader);
    glGetShaderiv(fragmentYellowShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentYellowShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Orange Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    

    //Yellow Shader Program 
    unsigned int YellowshaderProgram = glCreateProgram();
    glAttachShader(YellowshaderProgram, vertexShader);
    glAttachShader(YellowshaderProgram, fragmentYellowShader);
    glLinkProgram(YellowshaderProgram);
    glad_glGetProgramiv(YellowshaderProgram, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(YellowshaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float box[] = {
         0.3f,  0.7f, 0.0f,  // top right
         0.3f, -0.5f, 0.0f,  // bottom right
        -0.3f, -0.5f, 0.0f,  // bottom left
        -0.3f,  0.7f, 0.0f   // top left
    };  

    float box2[] = {
         0.2f,  0.6f, 0.0f,  // top right
         0.2f, -0.4f, 0.0f,  // bottom right
        -0.2f, -0.4f, 0.0f,  // bottom left
        -0.2f,  0.6f, 0.0f   // top left
    };  

    unsigned int indices[] = {  
        0, 1, 3,   
        1, 2, 3    
    };  

   

    unsigned int VAOs[2], EBOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, EBOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Box 2

    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box2), box2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glUseProgram(YellowshaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0),

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, EBOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(YellowshaderProgram);

    glfwTerminate();
    return 0;
}