#include "AnimationSprite.hpp"
#include <glew.h>

#include "../../../resourceManager/ResourceManager.hpp"
#include "../../../Resources/fileIndex.hpp"

AnimationSprite::AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows)
	:AnimationSprite(a_resourceID, a_columns, a_rows, a_columns* a_rows)
{
}

AnimationSprite::AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows, const unsigned int a_frameCountAnimation) 
	: Sprite(a_resourceID)
{
	setValues(a_columns, a_rows);

	const unsigned int maxFrameCount = a_columns * a_rows;
	const unsigned int frameCountAnimation = (a_frameCountAnimation > maxFrameCount) ? maxFrameCount : a_frameCountAnimation;
	AddAnimation(Animation(0, frameCountAnimation - 1, 1.f / 60.f), "Default");
}

AnimationSprite::AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows, const Animation& a_animation)
	: Sprite(a_resourceID)
{
	setValues(a_columns, a_rows);
	AddAnimation(a_animation, "Default");
}

void AnimationSprite::setValues(const unsigned int a_columns, const unsigned int a_rows)
{
	m_xValue = 1.f / (float)(m_columns = a_columns);
	m_yValue = 1.f / (float)(m_rows = a_rows);

	m_uvOffset.Scale(Vec2(m_xValue, m_yValue));
}

bool AnimationSprite::isValidAnimation(const Animation& a_animation)
{
	if (a_animation.frames.size() < 2) return false;

	const unsigned int maxIndex = m_columns * m_rows;

	for (const AnimationFrame& frame : a_animation.frames)
	{
		if (frame.GetFrameIndex() > maxIndex) return false;
	}

	return true;
}

void AnimationSprite::Update()
{
	SetCurrentFrame(GetCurrentAnimation().CurrentFrame().GetFrameIndex());
}

void AnimationSprite::SetCurrentFrame(const unsigned int a_frame)
{
	if (a_frame >= (m_columns * m_rows))
	{
		std::cout << "Warning: frame does not exist, did not cyhange the frame" << std::endl;
		return;
	}

	m_uvOffset.SetXPos(m_xValue * (a_frame % m_columns));
	m_uvOffset.SetYPos(m_yValue * (a_frame / m_columns));
}

void AnimationSprite::SetCurrentAnimation(const unsigned int a_animationIndex)
{
	if (a_animationIndex == m_currentAnimationIndex) return;
	if (a_animationIndex >= m_animations.size()) throw std::out_of_range("Frame does not exist");
	m_currentAnimationIndex = a_animationIndex;
	GetCurrentAnimation().Reset();
}

void AnimationSprite::SetCurrentAnimation(const std::string_view a_name)
{
	auto it = m_animationNames.find(a_name);
	if (it != m_animationNames.end()) {
		SetCurrentAnimation(m_animationNames[a_name]);
		return;
	}

	std::cout << "Warning: passed animation with the name " << a_name << " does not exist" << std::endl;
}

unsigned int AnimationSprite::AddAnimation(const Animation& a_animation, std::string_view a_name)
{
	const unsigned int index = m_animations.size();

	if (!isValidAnimation(a_animation))
	{
		std::cout << "Warning: passed animation was invalid unexpected results will occur" << std::endl;
		return 0;
	}

	auto it = m_animationNames.find(a_name);
	if (it != m_animationNames.end()) {
		std::cout << "Warning: Name already exists, animation will be overwritten" << std::endl;
		m_animations[it->second] = a_animation;
		return it->second;
	}

	m_animationNames[a_name] = index;
	m_animations.push_back(a_animation);

	return index;
}

Animation& AnimationSprite::GetAnimation(const unsigned int a_animationIndex)
{
	if (a_animationIndex >= m_animations.size()) throw std::out_of_range("Index for animation is out of range");
	return m_animations[a_animationIndex];
}

Animation& AnimationSprite::GetAnimation(const std::string_view a_animationName)
{
	auto it = m_animationNames.find(a_animationName);
	if (it == m_animationNames.end()) {
		throw std::invalid_argument("Provided animation name does not exist");
	}
	return m_animations[m_animationNames[a_animationName]];
}

void AnimationSprite::GenerateDefaultAnimations(const float a_duration)
{
	m_animations.clear();

	for (unsigned int i = 0; i < m_rows; i++)
	{
		const unsigned int startFrame = m_columns * i;
		m_animations.push_back(Animation(startFrame, startFrame+ m_columns, a_duration));
	}
}