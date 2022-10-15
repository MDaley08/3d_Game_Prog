#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 color;
    vec4 highlight;
} ubo;

out gl_PerVertex
{
    vec4 gl_Position;
};

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec4 colorMod;

void main()
{
    vec4 temp4;
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    temp4 = ubo.model * vec4(inNormal,1);
    fragNormal.x = temp4.x;
    fragNormal.y = temp4.y;
    fragNormal.z = temp4.z;
    fragTexCoord = inTexCoord;
    colorMod = ubo.color;
}
