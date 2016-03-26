/*
CS775: Legolization Project

Modified from An Introduction to OpenGL Programming,
Ed Angel and Dave Shreiner, SIGGRAPH 2013

Modified from Tutorial 3
Written by Parag Chaudhuri, 2015
*/


#include "application.hpp"

GLuint shaderProgram;
GLuint position_vbo, color_vbo, object_vao;

glm::mat4 translation_matrix;
glm::mat4 rotation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

// Load shaders and use the resulting shader program
void initShaders(void) {
    std::string vertex_shader_file("vshader.glsl");
    std::string fragment_shader_file("fshader.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = csX75::CreateProgramGL(shaderList);
    glUseProgram(shaderProgram);

}

//-----------------------------------------------------------------
void initBuffersGL(void) {
    //Ask GL for a Vertex Attribute Object (vao)
    glGenVertexArrays(1, &object_vao);
    //Set it as the current array to be used by binding it
    glBindVertexArray(object_vao);

    //Ask GL for a Vertex Buffer Object (vbo)
    glGenBuffers(1, &position_vbo);
    //Set it as the current buffer to be used by binding it
    glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
    //Copy the points into the current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_positions), v_positions, GL_STATIC_DRAW);

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation(shaderProgram, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    //Ask GL for a Vertex Buffer Object (vbo)
    glGenBuffers(1, &color_vbo);
    //Set it as the current buffer to be used by binding it
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    //Copy the points into the current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_colors), v_colors, GL_STATIC_DRAW);

    GLuint vColor = glGetAttribLocation(shaderProgram, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");
}

void renderGL(void) {

    glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
    //Copy the points into the current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_positions), v_positions, GL_STATIC_DRAW);
    //Set it as the current buffer to be used by binding it
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    //Copy the points into the current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_colors), v_colors, GL_STATIC_DRAW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f, 0.0f, 0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f, 1.0f, 0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f, 0.0f, 1.0f));

    ortho_matrix = glm::ortho(-1 * view_x, view_x, -1 * view_y, view_y, -1 * view_z, view_z);
    modelview_matrix = ortho_matrix *
                       translation_matrix *
                       rotation_matrix;

    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
}

int main(int argc, char **argv) {
    //! The pointer to the GLFW window
    GLFWwindow *window;

    //! Setting up the GLFW Error callback
    glfwSetErrorCallback(csX75::error_callback);

    //! Initialize GLFW
    if (!glfwInit())
        return -1;

    //We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //This is for MacOSX - can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //! Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(window_size_x, window_size_y, "CS775 Project: Legolization", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //! Make the window's context current
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    //Turn this on to get Shader based OpenGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        //Problem: glewInit failed, something is seriously wrong.
        std::cerr << "GLEW Init Failed : %s" << std::endl;
    }

    //Print and see what context got enabled
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    //Keyboard Callback
    glfwSetMouseButtonCallback(window, csX75::mouse_callback);
    glfwSetKeyCallback(window, csX75::key_callback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Initialize GL state
    csX75::initGL();
    initShaders();
    initBuffersGL();

    // Loop until the user closes the window
    while (glfwWindowShouldClose(window) == 0) {

        // Render here
        renderGL();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//-------------------------------------------------------------------------
