#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <stdexcept>

#include "AnimationFrame.hpp"

class Animation
{
public:
	std::vector<AnimationFrame> frames;

	float speed = 1.f;
	bool paused = false;

private:
	unsigned int m_currentFrameIndex = 0;
	float m_timeOnCurrentFrame = 0.f;

	std::unordered_map<unsigned int, std::function<void()>> m_functions;
	std::function<void()> m_onOver;

public:
	Animation(const std::vector<AnimationFrame>& a_frames) 
		: frames(a_frames) { if (a_frames.size() < 2) throw std::invalid_argument("Not enough frames"); };
	Animation(const std::vector<AnimationFrame>& a_frames, const std::function<void()>& a_onOverFunction) 
		: Animation(a_frames) { AddOverFunction(a_onOverFunction); };
	Animation(const unsigned int a_firstSpriteFrame, const unsigned int a_lastSpriteFrame, const float a_durationEachFrame);
	Animation(const unsigned int a_firstSpriteFrame, const unsigned int a_lastSpriteFrame, const float a_durationEachFrame, const std::function<void()>& a_onOverFunction)
		: Animation(a_firstSpriteFrame, a_lastSpriteFrame, a_durationEachFrame) { AddOverFunction(a_onOverFunction); };

public:
	void Reset();

	AnimationFrame& CurrentFrame() { return frames[m_currentFrameIndex]; }
	unsigned int GetCurrentFrameIndex() { return m_currentFrameIndex; }

	void AddFunctionOnFrame(const unsigned int a_frameIndex, const std::function<void()>& a_function);
	void AddOverFunction(const std::function<void()>& a_function) { m_onOver = a_function; };
	void Animate(const float a_deltaTime);

private:
	void setFrame(const unsigned int a_frameIndex);
};

