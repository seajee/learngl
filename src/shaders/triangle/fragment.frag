#version 330 core

out vec4 o_FragColor;
in vec3 color;

void main()
{
    o_FragColor = vec4(color, 1.0f);
}