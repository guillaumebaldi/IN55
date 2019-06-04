#version 330

uniform mat4 mvp;
uniform int N;
uniform int M;
uniform vec3 colorN;
uniform vec3 colorM;

in vec3 position;
in vec3 color;

out vec3 fColor;

void main()
{ 
    gl_Position = mvp * vec4(position, 1.0 );


}
