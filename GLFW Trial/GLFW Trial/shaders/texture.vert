//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec2 vertex;
in vec2 uv;

uniform mat3 projection;
uniform mat3 identity;

out vec2 texCoord; //make sure the texture coord is interpolated

void main( void ){
	gl_Position = vec4(projection * identity * vec3(vertex, 1.f), 1.f);
	texCoord = uv;
}