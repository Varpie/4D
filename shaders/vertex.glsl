/*#version 330

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 vs_fs_color;

void main(void)
{
    vs_fs_color = color;
    gl_Position = projection_matrix * (model_matrix * position);
}
*/

#version 330
#extension GL_ARB_explicit_uniform_location : enable

// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
layout (location = 0) in  vec4 in_Position;
layout (location = 1) in  vec4 in_Color;

layout (location = 2) uniform mat4 mvp;
 
// We output the ex_Color variable to the next shader in the chain
out vec4 ex_Color;

void main(void) {
    // Since we are using flat lines, our input only had two points: x and y.
    // Set the Z coordinate to 0 and W coordinate to 1
    vec4 pos = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
 	// mat4 mvp = mat4();
 	gl_Position =  in_Position;

    // Pass the color on to the fragment shader
    ex_Color = in_Color;
}
