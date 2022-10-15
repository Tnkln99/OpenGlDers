#version 450 core

out vec4 color;

void main()
{
    color = vec4(
        sin(gl_FragCoord.x * 0.25) *0.5 + 0.5,
        cos(gl_FragCoord.y * 0.25) *0.5 + 0.5,
        sin(gl_FragCoord.z * 0.15) * cos(gl_FragCoord.y * 0.15),
        1.0
    );
} 