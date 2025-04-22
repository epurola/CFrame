#shader vertex
#version 410 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_MVP;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_MVP * vec4(a_Position, 0.0, 1.0);
}


#shader fragment
#version 410 core

in vec2 v_TexCoord;

uniform float u_Opacity;
uniform vec4 u_Color;

out vec4 color;

uniform sampler2D u_Texture;

void main()
{
    float alpha = texture(u_Texture, v_TexCoord).r;
    color = vec4(u_Color.r, u_Color.b, u_Color.b, alpha * u_Opacity); 
}
