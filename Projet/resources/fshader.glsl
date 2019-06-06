#version 330

in vec3 fColor;
in vec2 fUv;

out vec4 fragColor;

void main()
{
    fragColor = vec4( fColor, 1.0 );
}
