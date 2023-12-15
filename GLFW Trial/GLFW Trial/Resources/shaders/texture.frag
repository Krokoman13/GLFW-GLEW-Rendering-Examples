//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330
#extension GL_ARB_explicit_uniform_location : require

precision highp float;

layout(location = 1) uniform sampler2D diffuseTexture;
layout(location = 2) uniform vec4 diffuseColor = vec4(1.0f);

in vec2 texCoord;

out vec4 fragment_color;

void main( void ) {
	fragment_color = texture(diffuseTexture,texCoord) * diffuseColor;
}
