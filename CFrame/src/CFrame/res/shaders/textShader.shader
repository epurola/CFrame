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
uniform vec4 u_Color2;
uniform float u_Speed;
uniform float u_Time;

out vec4 color;
uniform sampler2D u_Texture;

void main()
{
    //Todo; Pass in the length of text so the gradient is not just applied to each char independetly
    float gradient = v_TexCoord.x + sin(u_Time * u_Speed);

    vec4 color1 = u_Color;
    vec4 color2 = u_Color2;
    // Interpolate between the colors
    vec4 c = mix(color1, color2, gradient);

    float alpha = texture(u_Texture, v_TexCoord).r;
    color = vec4(c.r, c.b, c.b, alpha * u_Opacity); 
}
