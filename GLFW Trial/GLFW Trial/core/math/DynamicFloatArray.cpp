#include "DynamicFloatArray.hpp"
#include <stdexcept>

DynamicFloatArray::DynamicFloatArray(const unsigned int a_size)
{
	initialize(a_size);
}

DynamicFloatArray::DynamicFloatArray(const DynamicFloatArray& a_other)
{
	initialize(a_other.m_size);
	for (unsigned int i = 0; i < a_other.m_size; i++)
	{
		m_pArray[i] = a_other.m_pArray[i];
	}
}

DynamicFloatArray::~DynamicFloatArray()
{
	delete[] m_pArray;
}

void DynamicFloatArray::initialize(unsigned int a_size)
{
	m_size = a_size;
	m_pArray = new float[a_size];

	for (unsigned int i = 0; i < m_size; i++)
	{
		m_pArray[i] = 0;
	}
}

DynamicFloatArray DynamicFloatArray::operator=(const DynamicFloatArray& a_other)
{
	if (this == &a_other) return *this;
	delete[] m_pArray;

	initialize(a_other.GetSize());
	for (unsigned int i = 0; i < a_other.m_size; i++)
	{
		m_pArray[i] = a_other.m_pArray[i];
	}

	return *this;
}

bool DynamicFloatArray::operator==(const DynamicFloatArray& a_other)
{
	if (m_size != a_other.m_size) return false;

	for (unsigned int i = 0; i < m_size; i++)
	{
		if (m_pArray[i] != a_other.m_pArray[i]) return false;
	}

	return true;
}

float& DynamicFloatArray::operator[](unsigned int i)
{
	if (i > GetSize() - 1) throw std::out_of_range("Index is out of range");
	return m_pArray[i];
}

const float DynamicFloatArray::operator[](unsigned int i) const
{
	if (i > GetSize() - 1) throw std::out_of_range("Index is out of range");
	return m_pArray[i];
}
