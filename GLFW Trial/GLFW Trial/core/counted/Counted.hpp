#pragma once
#include <memory>

class Counted
{
private:
    std::shared_ptr<int> m_counter;

public:
    Counted() : m_counter(new int(0)) { };
    Counted(const Counted& a_other) : m_counter(a_other.m_counter) {};

    Counted operator=(const Counted& a_other)
    {
        m_counter = a_other.m_counter;
        return *this;
    }

    virtual ~Counted() { };
    inline long Count() const { return m_counter.use_count(); };
    inline bool LastCopy() const { return Count() == 1; }
};