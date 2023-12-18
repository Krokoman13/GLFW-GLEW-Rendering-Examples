//HOLOGRAM VERTEX SHADER
#version 330
#extension GL_ARB_explicit_uniform_location : require

precision highp float;

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 uv;

layout(location = 0) uniform mat3 mvp; // combined model-view-projection matrix
layout(location = 1) uniform mat3 uvOffset; // matrix for offset of uv

out vec2 texCoord;
out vec3 worldVertex;

void main(void) {
	worldVertex = mvp * vec3(vertex, 1.f);
	gl_Position = vec4(worldVertex, 1.f);
	texCoord = vec2(uvOffset * vec3(uv, 1.f));
}