#include "gl_framework.hpp"

extern GLfloat xrot, yrot, zrot;
extern GLfloat xpos, ypos, zpos;
extern glm::vec4 v_positions[];
extern glm::vec4 v_colors[];
extern int num_vertices;
extern int window_size_x, window_size_y;
extern double view_x, view_y, view_z;

namespace csX75 {
    //! Initialize GL State
    void initGL(void) {
        //Set framebuffer clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //Set depth buffer furthest depth
        glClearDepth(1.0);
        //Set depth test to less-than
        glDepthFunc(GL_LESS);
        //Enable depth testing
        glEnable(GL_DEPTH_TEST);
    }

    //!GLFW Error Callback
    void error_callback(int error, const char *description) {
        std::cerr << description << std::endl;
    }

    //!GLFW framebuffer resize callback
    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        //!Resize the viewport to fit the window size - draw to entire window
        glViewport(0, 0, width, height);
    }

    //!GLFW keyboard callback
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        //!Close the window if the ESC key was pressed
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {
            yrot -= 0.1;
        }
        else if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
            yrot += 0.1;
        }
        else if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
            xrot += 0.1;
        }
        else if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
            xrot -= 0.1;
        }
        else if (key == GLFW_KEY_PAGE_UP && action == GLFW_REPEAT) {
            zrot += 0.1;
        }
        else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_REPEAT) {
            zrot -= 0.1;
        }
        else if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
            xpos += 0.1;
        }
        else if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
            xpos -= 0.1;
        }
        else if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
            ypos += 0.1;
        }
        else if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
            ypos -= 0.1;
        }
        else if (key == GLFW_KEY_Z && action == GLFW_REPEAT) {
            zpos += 0.1;
        }
        else if (key == GLFW_KEY_X && action == GLFW_REPEAT) {
            zpos -= 0.1;
        }
    }

    void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
        // Get mouse position
        if (action == GLFW_PRESS) {

        }
    }
};
