#version 330

uniform mat4 mvp;

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 uv;
in int id;

out vec3 fColor;
out vec2 fUv;

void main()
{
	if(id < 500) {
		gl_Position = mvp * vec4( position, 2.0 );
	}
	else {
		gl_Position = mvp * vec4( position, 1.0 );
	}
    

    fColor = color;
    fUv = uv;
}
