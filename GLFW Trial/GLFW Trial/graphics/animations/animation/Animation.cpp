#include "Animation.hpp"

#include <iostream>

Animation::Animation(const unsigned int a_firstSpriteFrame, const unsigned int a_lastSpriteFrame, const float a_durationEachFrame)
{
	if (a_firstSpriteFrame == a_lastSpriteFrame) throw std::invalid_argument("Last frame cannot be equal to the first frame");

	int step = (a_firstSpriteFrame < a_lastSpriteFrame) ? 1 : -1;

	for (unsigned int i = a_firstSpriteFrame; i != a_lastSpriteFrame + step; i += step)
	{
		frames.push_back(AnimationFrame(i, a_durationEachFrame));
	}
}

void Animation::Reset()
{
	m_timeOnCurrentFrame = 0.f;
	setFrame(0);
}


void Animation::AddFunctionOnFrame(const unsigned int a_frameIndex, const std::function<void()>& a_function)
{
	if (a_frameIndex >= frames.size()) throw std::out_of_range("Index is out of range");

	auto it = m_functions.find(a_frameIndex);
	if (it != m_functions.end()) {
		std::cout << "Warning: Index already has a function, will be overriden" << std::endl;
	}

	m_functions[a_frameIndex] = a_function;
}

void Animation::Animate(const float a_deltaTime)
{
	if (paused) return;

	m_timeOnCurrentFrame += a_deltaTime * speed;

	const float currentDuration = frames[m_currentFrameIndex].GetDuration();
	if (m_timeOnCurrentFrame < currentDuration) return;

	m_timeOnCurrentFrame -= currentDuration;	//Instead of setting the time to 0 the ecces time is kept
	
	if (m_currentFrameIndex == frames.size() - 1)
	{	
		if (m_onOver) m_onOver();
		setFrame(0);
	}
	else setFrame(m_currentFrameIndex + 1);

	Animate(0.f);	//It is possible that during one animate() call there are multiple frames, to make sure they are all handled recursion is used
}

void Animation::setFrame(const unsigned int a_frameIndex)
{
	if (a_frameIndex == m_currentFrameIndex) m_timeOnCurrentFrame = 0.f;

	//Executing the function retlated to this frame if it exists
	auto it = m_functions.find(a_frameIndex);
	if (it != m_functions.end()) {
		it->second();	
	}

	m_currentFrameIndex = a_frameIndex;
}

