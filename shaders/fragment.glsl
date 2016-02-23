/*#version 330

in vec4 vs_fs_color;

layout (location = 0) out vec4 color;

void main(void)
{
    color = vs_fs_color;

}
*/

#version 150
// It was expressed that some drivers required this next line to function properly
precision highp float;
 
in  vec4 ex_Color;
 
void main(void) {
    gl_FragColor = vec4(ex_Color);
}
