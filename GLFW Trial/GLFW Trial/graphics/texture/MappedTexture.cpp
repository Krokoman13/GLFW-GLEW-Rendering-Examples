#include "MappedTexture.hpp"
#include "TextureMapper.hpp"

MappedTexture::MappedTexture()
{
}

MappedTexture::MappedTexture(const std::shared_ptr<Texture>& a_pTexture) : m_pTexture(a_pTexture)
{
}

MappedTexture::~MappedTexture()
{
	if (!m_pTexture) return;
	if (m_pTexture.use_count() == 2) TextureMapper::Release(*this);
}
