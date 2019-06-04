#version 330

in vec3 fColor;
in vec2 fUv;

uniform sampler2D texId;
uniform sampler2D texId2;

out vec4 fragColor;

void main()
{
    //fragColor = vec4( fColor, 1.0 );
    /*fragColor = vec4((texture2D(texId, fUv).rgb + fColor), ((texture2D(texId, fUv).a * 1.0)));
    clamp(fragColor, 0.0, 1.0);*/
    fragColor = texture2D(texId2, fUv);
    //fragColor = texture2D(texId, fUv) * vec4(fColor, 1.0f);
    //fragColor = vec4(fUv.xy, 0.0, 1.0);
}
