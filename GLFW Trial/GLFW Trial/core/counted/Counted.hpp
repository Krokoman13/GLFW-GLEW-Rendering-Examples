#pragma once
#include <memory>

class Counted
{
private:
    mutable unsigned int* m_counter;

public:
    Counted() : m_counter(new unsigned int(1)){ };
    Counted(const Counted& a_other) : m_counter(a_other.m_counter) 
    {
        m_counter = a_other.m_counter;
        (*m_counter)++;
    };

    Counted operator=(const Counted& a_other)
    {
        onDestroyed();
        m_counter = a_other.m_counter;
        (*m_counter)++;
        return *this;
    }

    virtual ~Counted() { onDestroyed(); };
    inline long Count() const { return *m_counter; };

protected:
    virtual void onLastDestruction() {};

private:
    void onDestroyed()
    {
        unsigned int& count = (*m_counter);
        count--;

        if (count == 0)
        {
            delete m_counter;
            onLastDestruction();
        }
    }
};