#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// 处理所有的输入：查询当前帧与GLFW相关联的按键是否有按下或释放, 并作出相应动作
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// 当窗口大小改变时, 将执行该回调函数
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// 设置屏幕初始长和宽
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 顶点着色器源码
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

// 片段着色器源码
const char* fragmentShaderSource1 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

// 片段着色器源码
const char* fragmentShaderSource2 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                   "}\0";

int main(int argc, char* argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // GLAD加载所有OpenGL函数指针
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 初始化: 包括渲染程序和渲染数据

    // 创建顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 编译顶点着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // 检测着色器是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建和编译片段着色器1
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建和编译片段着色器2
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建着色器程序1
    unsigned int shaderProgram1 = glCreateProgram();
    // 把之前编译的着色器附加到程序对象上，然后用glLinkProgram链接它们
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    // 检查着色程序是否成功
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(fragmentShader1);

    // 创建着色器程序2
    unsigned int shaderProgram2 = glCreateProgram();
    // 把之前编译的着色器附加到程序对象上，然后用glLinkProgram链接它们
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    // 检查着色程序是否成功
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader2);


    int triangle_nums = 2;

    unsigned int shaderPrograms[] = {
            shaderProgram1,
            shaderProgram2
    };


    // 定义三角形的三个顶点
    float vertices[][9] = {
        {0.5f, -0.5f, 0.0f,
         0.0f, 0.5f, 0.0f,
         0.9f, 0.0f, 0.0f},

        {-0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f, 0.5f, 0.0f}
    };


    unsigned int VBO[triangle_nums];
    unsigned int VAO[triangle_nums];
    glGenBuffers(triangle_nums, VBO);
    glGenVertexArrays(triangle_nums, VAO);
    for (int i = 0; i < triangle_nums; i++) {
        // 将VBO缓冲绑定到GL_ARRAY_BUFFER目标上
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        // 将之前定义的顶点数据复制到缓冲的内存中
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);

        // 绑定VAO
        glBindVertexArray(VAO[i]);
        // 设置顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // 解绑VAO
        glBindVertexArray(0);
        // 解绑VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // 设定线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 渲染loop
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        processInput(window);

        // 渲染图形
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < triangle_nums; i++) {
            glUseProgram(shaderPrograms[i]);
            glBindVertexArray(VAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        // 交换缓冲区、轮询IO事件(键盘按下/释放、鼠标移动等)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放着色器程序和缓冲数据
    glDeleteVertexArrays(triangle_nums, VAO);
    glDeleteBuffers(triangle_nums, VBO);
    for (int i = 0; i < triangle_nums; i++) {
        glDeleteProgram(shaderPrograms[i]);
    }

    // 终止GLFW, 清理所有GLFW分配的资源
    glfwTerminate();
    return 0;
}
