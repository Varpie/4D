#version 330
 
in  vec4 ex_Color;

layout (location = 0) out vec4 color;
 
void main(void) {
    color = vec4(ex_Color);
}
