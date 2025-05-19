#shader vertex
#version 410 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

// Per-instance attributes
layout(location = 2) in vec2 i_Position;
layout(location = 3) in vec2 i_Size;
layout(location = 4) in vec4 i_Color1;
layout(location = 5) in vec4 i_Color2;
layout(location = 6) in vec4 i_BorderColor1;
layout(location = 7) in vec4 i_BorderColor2;
layout(location = 8) in vec4 i_BorderSizes;
layout(location = 9) in vec4 i_Radius;
layout(location =10) in float i_Time;
layout(location =11) in float i_Speed;
layout(location =12) in float i_Angle;
layout(location =13) in float i_HasTexture;
layout(location =14) in float i_TextureIndex;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec4 v_Color1;
out vec4 v_Color2;
out vec4 v_BorderColor1;
out vec4 v_BorderColor2;
out vec4 v_BorderSizes;
out vec4 v_Radius;
out float v_Time;
out float v_Speed;
out float v_Angle;
out float v_HasTexture;

out vec2 v_LocalPos;
out vec2 v_Size;

mat2 rotate(float angle){
    return mat2(
        cos(angle), -sin(angle),
        sin(angle),  cos(angle)
    );
}

void main()
{

    vec2 adjustedPos = rotate(i_Angle) * ( a_Position * i_Size);

    vec2 worldPos = adjustedPos + i_Position + (i_Size * 0.5);

    gl_Position = u_ViewProjection * vec4(worldPos, 0.0, 1.0);

    v_TexCoord = a_TexCoord;
    v_Color1 = i_Color1;
    v_Color2 = i_Color2;
    v_BorderColor1 = i_BorderColor1;
    v_BorderColor2 = i_BorderColor2;
    v_BorderSizes = i_BorderSizes;
    v_Radius = i_Radius;
    v_Time = i_Time;
    v_Speed = i_Speed;
    v_Angle = i_Angle;


    // Pass size and relative position to fragment shader
    v_Size = i_Size;
    //Rotate back for SDF
    v_LocalPos = rotate(-i_Angle) * adjustedPos;
}

#shader fragment
#version 410 core

in vec2 v_TexCoord;
in vec4 v_Color1;
in vec4 v_Color2;
in vec4 v_BorderColor1;
in vec4 v_BorderColor2;
in vec4 v_BorderSizes;
in vec4 v_Radius;
in float v_Time;
in float v_Speed;
in float v_Angle;
in float v_HasTexture;

in vec2 v_LocalPos;
in vec2 v_Size;

uniform sampler2D u_Texture;

out vec4 FragColor;

float sdRoundedBox(in vec2 p, in vec2 b, in vec4 r)
{
    r.xy = (p.x > 0.0) ? r.xy : r.zw;
    r.x  = (p.y > 0.0) ? r.x  : r.y;
    vec2 q = abs(p) - b + r.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

float selectBorderThickness(vec2 p, vec2 b) {
    float dx = abs(p.x) - b.x;
    float dy = abs(p.y) - b.y;

    if (dx > dy) {
        return (p.x > 0.0) ?  v_BorderSizes.w : v_BorderSizes.y ; // Right : Left
    } else {
        return (p.y > 0.0) ? v_BorderSizes.z : v_BorderSizes.x ; // Top : Bottom
    }

}

void main()
{
    vec2 center = vec2(0.0); // local space
    vec2 p = v_LocalPos - center;

    vec2 b = v_Size * 0.5;
    vec4 r = vec4(v_Radius.w , v_Radius.y , v_Radius.z, v_Radius.x);

    float thickness = selectBorderThickness(p, b);
    float dist = sdRoundedBox(p, b, r) + thickness;

    float gradient = (p.x + b.x + sin(v_Time * v_Speed) * b.x * 0.5) / (2.0 * b.x);
    vec4 gradientColor = mix(v_Color1, v_Color2, gradient);
    vec4 gradientBorderColor = mix(v_BorderColor1, v_BorderColor2, gradient);
    vec4 texColor = texture(u_Texture, v_TexCoord);

    if (dist < 0.0) {
        FragColor =  gradientColor;
    } else if (dist < thickness) {
        FragColor = gradientBorderColor;
    } else {
        discard;
    }
}
