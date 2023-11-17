#pragma once

struct DynamicFloatArray
{
private:
	unsigned int m_size;
	float* m_pArray;

public:
	DynamicFloatArray(const unsigned int a_size);
	DynamicFloatArray(const DynamicFloatArray& a_other);
	~DynamicFloatArray();

private:
	void initialize(unsigned int a_size);

public:
	inline unsigned int GetSize() const { return m_size; };
	inline const float* Data() const { return m_pArray; };

	DynamicFloatArray operator=(const DynamicFloatArray& a_other);
	float& operator[](unsigned int a_value);
	const float operator[](unsigned int a_value)const;
};

