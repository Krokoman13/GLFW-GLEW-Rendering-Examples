//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1
#extension GL_ARB_explicit_uniform_location : require

precision highp float;

layout(location = 1) uniform sampler2D diffuseTexture;

in vec2 texCoord;

out vec4 fragment_color;

void main( void ) {
	fragment_color = texture(diffuseTexture,texCoord);
}
