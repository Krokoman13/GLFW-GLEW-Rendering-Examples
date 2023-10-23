#pragma once
#include "Texture.hpp"
#include <Memory>

class MappedTexture
{
private:
	friend class TextureMapper;
	std::shared_ptr<Texture> m_pTexture;

protected:
	MappedTexture(const std::shared_ptr<Texture>& a_pTexture);

public:
	MappedTexture();
	virtual ~MappedTexture();

	Texture& Get() { return *m_pTexture.get(); };
	operator std::shared_ptr<Texture>& () { return m_pTexture; };
	operator Texture& () { return *m_pTexture.get(); };
};

