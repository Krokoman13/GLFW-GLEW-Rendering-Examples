#include "Sprite.hpp"
#include <iostream>
#include "loaders/ShaderUtil.h"
#include "DefaultImageVariables.hpp"

ResourceCache<Texture>* Sprite::pTextureCache = nullptr;

Sprite::Sprite(const unsigned int a_resourceID) : Renderable(0, 0), m_resourceID(a_resourceID)
{
	m_textureTransform.SetParent(this);
}

Sprite::~Sprite()
{

}

bool Sprite::Load()
{
	bool succesful = true;

	if (m_minFilterParam < 0) m_minFilterParam = DefaultSpriteVariables::minFilterParam;
	if (m_magFilterParam < 0) m_magFilterParam = DefaultSpriteVariables::magFilterParam;
	
	GLint prevMinfilter = Texture::defMinFilter;
	GLint prevMagfilter = Texture::defMagFilter;

	Texture::defMinFilter = m_minFilterParam;
	Texture::defMagFilter = m_magFilterParam;

	if (pTextureCache) m_texture = pTextureCache->Get(m_resourceID);
	//else m_texture = Texture(m_filepath, m_minFilterParam, m_magFilterParam);

	Texture::defMinFilter = prevMinfilter;
	Texture::defMagFilter = prevMagfilter;

	Vec2 textureSize = Vec2(float(m_texture.GetWidth()), float(m_texture.GetHeight()));
	m_textureTransform.SetLocalScale(textureSize);

	if (!m_texture.SuccesfullLoad()) {
		std::cerr << "Error: Could not load texture" << std::endl;
		succesful = false;
	}

	//if (!useDefaultImageVariables()) {
	//	std::cerr << "Error: Could not use defaultImageVariables" << std::endl;
	//	succesful = false;
	//}

	// Create the shader program
	m_programID = ShaderUtil::createProgram("texture.vert", "texture.frag");
	if (m_programID == -1) {
		std::cerr << "Error: Could not create program" << std::endl;
		succesful = false;
	}

	// get index for the attributes in the shader
	m_vertexIndex = glGetAttribLocation(m_programID, "vertex");
	if (m_vertexIndex == -1) {
		std::cerr << "Error: Could not get vertex atribute" << std::endl;
		succesful = false;
	}

	m_uvIndex = glGetAttribLocation(m_programID, "uv");
	if (m_uvIndex == -1) {
		std::cerr << "Error: Could not get uv atribute" << std::endl;
		succesful = false;
	}

	m_projectionIndex = glGetUniformLocation(m_programID, "projection");
	if (m_projectionIndex == -1) {
		std::cerr << "Error: Could not get projection atribute" << std::endl;
		succesful = false;
	}

	m_identityMatrix = glGetUniformLocation(m_programID, "identity");
	if (m_identityMatrix == -1) {
		std::cerr << "Error: Could not get identity atribute" << std::endl;
		succesful = false;
	}
	m_diffuseTextureIndex = glGetUniformLocation(m_programID, "diffuseTexture");
	if (m_diffuseTextureIndex == -1) {
		std::cerr << "Error: Could not get diffuseTexure atribute" << std::endl;
		succesful = false;
	}

	const GLfloat vertices[8] = {
		//2 triangles forming a rectangle, 3 vertices per triangle, 2 floats per vertex = 8 floats in total
		-0.5f,  0.5f,  // Top left
		-0.5f, -0.5f,  // Bottom left
		 0.5f,  0.5f,  // Top right
		 0.5f, -0.5f,  // Bottom right
	};

	//create a handle to the buffer
	glGenBuffers(1, &m_vertexBufferId);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}

	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	const GLfloat uvs[8] = {
		//2 triangles forming a rectangle, 3 vertices per triangle, 2 floats per vertex = 8 floats in total
		0.f, 1.f,  // Top left
		0.f, 0.f,  // Bottom left
		1.f, 1.f,  // Top right
		1.f, 0.f,  // Bottom right
	};

	// create a handle to the buffer
	glGenBuffers(1, &m_uvsBufferId);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}
	// bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	// a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, m_uvsBufferId);
	// stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	// disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return succesful;
}

bool Sprite::useDefaultImageVariables()
{
	bool succesful = DefaultSpriteVariables::Initialize();

	m_programID = DefaultSpriteVariables::GetProgramID();

	m_vertexIndex = DefaultSpriteVariables::GetVertexIndex();
	m_uvIndex = DefaultSpriteVariables::GetUvIndex();

	m_projectionIndex = DefaultSpriteVariables::GetOffsetIndex();
	m_identityMatrix = DefaultSpriteVariables::GetAxisIndex();

	m_diffuseTextureIndex = DefaultSpriteVariables::GetDiffuseTextureIndex();

	m_uvsBufferId = DefaultSpriteVariables::GetUvsBufferId();
	m_vertexBufferId = DefaultSpriteVariables::GetVertexBufferId();

	return succesful;
}

void Sprite::SetFilterParam(GLint a_minFilter, GLint a_magFilter)
{
	if (Texture::NeedsMipmaps(a_magFilter))
	{
		std::cerr << "Warning: Mag filter cannot user mipmaps!";
		return;
	}

	m_minFilterParam = a_minFilter;
	m_magFilterParam = a_magFilter;
}


void Sprite::Display(const Matrix3& a_pojectionMatrix)
{
	//tell the GPU to use this program
	glUseProgram(m_programID);

	//Matrix3 thing = (Matrix3)(a_pojectionMatrix * m_textureTransform.GetGlobalMatrix());
	glUniformMatrix3fv(m_identityMatrix, 1, GL_FALSE, m_textureTransform.GetGlobalMatrix().GetArray().Data());
	glUniformMatrix3fv(m_projectionIndex, 1, GL_FALSE, a_pojectionMatrix.GetArray().Data());

	//tell OpenGL that the data for the vertexIndex is coming in from an array
	glEnableVertexAttribArray(m_vertexIndex);
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(m_vertexIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
	glEnableVertexAttribArray(m_uvIndex);
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, m_uvsBufferId);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(m_uvIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, m_texture.GetId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(m_diffuseTextureIndex, 0);

	//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(m_vertexIndex);
	glDisableVertexAttribArray(m_uvIndex);
}
