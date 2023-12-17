#pragma once
#include "../../sprite/Sprite.hpp"
#include "../animation/Animation.hpp"

class AnimationSprite : public Sprite
{
private:
	unsigned int m_columns;
	unsigned int m_rows;

	float m_xValue;
	float m_yValue;

	unsigned int m_currentAnimationIndex = 0;
	std::vector<Animation> m_animations;
	std::unordered_map<std::string_view, unsigned int> m_animationNames;

public:
	AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows);
	AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows, const unsigned int a_frameCountAnimation);
	AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows, const Animation& a_animation);

public:
	void Update();
	void SetCurrentFrame(const unsigned int a_frame);

	void SetCurrentAnimation(const unsigned int a_animationIndex);
	void SetCurrentAnimation(const std::string_view a_name);
	inline Animation& GetCurrentAnimation() { return m_animations[m_currentAnimationIndex]; };

	unsigned int AddAnimation(const Animation& a_animation, const std::string_view a_name);
	Animation& GetAnimation(const unsigned int a_animationIndex);
	Animation& GetAnimation(const std::string_view a_animationName);

	void GenerateDefaultAnimations(const float a_duration);

private:
	void setValues(const unsigned int a_columns, const unsigned int a_rows);
	bool isValidAnimation(const Animation& a_animation);
};

