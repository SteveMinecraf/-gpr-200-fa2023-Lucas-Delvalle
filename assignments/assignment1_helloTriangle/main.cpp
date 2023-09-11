#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

const char* vertexShaderSource = R"(
    #version 450
    layout(location = 0) in vec3 vPos;
    layout(location = 1) in vec4 vColor;
    out vec4 Color;
    uniform float _Time;
    void main(){
        Color = vColor;
        vec3 offset = vec3(0, sin(vPos.x + _Time), 0) * 0.5;
        gl_Position = vec4(vPos + offset, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 450
    layout(location = 6) uniform float _Time; // Explicitly set location to 6
    out vec4 FragColor;
    in vec4 Color;
    void main(){
        FragColor = Color * abs(sin(_Time));
    }
)";


float vertices[21] = {
    //x    //y    //z   //r   //g   //b   //a
    -0.5, -0.5,  0.0,  1.0, 0.0, 0.0, 1.0, // Bottom left
     0.5, -0.5,  0.0,  0.0, 1.0, 0.0, 1.0, // Bottom right
     0.0,  0.5,  0.0,  0.0, 0.0, 1.0, 1.0  // Top center
};

//Creates a new vertex array object with vertex data
unsigned int createVAO(float* vertexData, int numVertices) {
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 7, vertexData, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return vao;
}

// Creates a new shader of a given type.
// Possible types: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc
// Returns id of the shader object
unsigned int createShader(GLenum shaderType, const char* sourceCode) {
    //Create a new vertex shader object
    unsigned int shader = glCreateShader(shaderType);
    //Supply the shader object with source code
    glShaderSource(shader, 1, &sourceCode, NULL);
    //Compile the shader object
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        //512 is an arbitrary length, but should be plenty of characters for our error message.
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader compilation error: %s", infoLog);

        return 0; 
    }

    return shader;
}

//Creates a new shader program with vertex + fragment stages
//Returns id of new shader program if successful, 0 if failed
unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    //Attach each stage
    glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);
    //Link all the stages together
    glLinkProgram(shaderProgram);

    //Check for linking errors
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Failed to link shader program: %s", infoLog);

        return 0;
    }

    //The linked program now contains our compiled code, so we can delete these intermediate objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    printf("Initializing...");
    if (!glfwInit()) {
        printf("GLFW failed to init!");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
    if (window == NULL) {
        printf("GLFW failed to create window");
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("GLAD Failed to load GL headers");
        return 1;
    }

    // Create a VAO for the triangle
    unsigned int triangleVAO = createVAO(vertices, 3);

    // Create a shader program
    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    if (shaderProgram == 0) {

        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(triangleVAO);

        //The current time in seconds this frame
        float time = (float)glfwGetTime();
        //Get the location of the uniform by name
        int timeLocation = glGetUniformLocation(shaderProgram, "_Time");
        //Set the value of the variable at the location
        glUniform1f(timeLocation, time);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }


    printf("Shutting down...");
}