#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127
// Maximum number of vertices possible in an object
#define MAX_VERTICES 1000

#include <iostream>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Translation Parameters
GLfloat xpos = 0.0, ypos = 0.0, zpos = 0.0;

// Rotation Parameters
GLfloat xrot = 0.0, yrot = 0.0, zrot = 0.0;

//vertices in homogenous coordinates
glm::vec4 v_positions[MAX_VERTICES];

//RGBA colors
glm::vec4 v_colors[MAX_VERTICES];

// cuurent number of vertices
int num_vertices = 0;

//Running variable to toggle culling on/off
bool enable_culling = true;

//Running variable to toggle wireframe/solid modelling
bool solid = true;

// window_size
int window_size_x = 512;
int window_size_y = 512;

double view_x = 2.0;
double view_y = 2.0;
double view_z = 2.0;

//-------------------------------------------------------------------------

#endif
