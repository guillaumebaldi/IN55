#version 330

const int BONES = 19;
const int WEIGHTS = 5;

uniform mat4 mvp;
uniform mat4 transform[BONES];

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 uv;
in vec4 idBones;
in vec4 weight;
//in int[WEIGHTS] idBones;
//in int[WEIGHTS] weight;

out vec3 fColor;
out vec2 fUv;

void main()
{
	vec4 vertexPos = vec4(position, 1.0);
	vec4 finalPos = vec4(0.0);
	for(int i = 0; i < WEIGHTS; i++) {
		if(idBones[i] != -1) {
			mat4 bt = transform[int(idBones[i])];
			vec4 p = bt * vertexPos;
			finalPos += p * weight[i];
		}
	}
	
	gl_Position = mvp * finalPos;

	

    fColor = color;
    fUv = uv;
}
