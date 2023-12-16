#pragma once

class AnimationFrame
{
private:
	const float minDuration = 0.001f;

	float m_duration;	//In seconds
	unsigned int m_frameIndex;

public:
	AnimationFrame(const unsigned int a_frameIndex, const float a_durationSeconds) : m_frameIndex(a_frameIndex) { SetDuration(a_durationSeconds); };
	AnimationFrame(const AnimationFrame& a_other) : m_frameIndex(a_other.m_frameIndex), m_duration(a_other.m_duration) {};
	AnimationFrame& operator=(const AnimationFrame& a_other) 
	{ 
		m_frameIndex = a_other.m_frameIndex; 
		m_duration = a_other.m_duration; 
		return *this;
	};

public:
	inline float GetDuration() const { return m_duration; }
	inline void SetDuration(const float a_durationSeconds) { m_duration = (a_durationSeconds < minDuration) ? minDuration : a_durationSeconds; }
	inline unsigned int GetFrameIndex() const { return m_frameIndex; };
	virtual void OnFrame() {};
};

