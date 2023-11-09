#pragma once
#include <memory>

class Counted
{
public:
    Counted() : m_counter(std::shared_ptr<void>(nullptr, [](void*) {})) { onLastDestruction(); };

    Counted(const Counted& a_other) : m_counter(a_other.m_counter) {};

    virtual ~Counted() = default;

    inline long Count() { return m_counter.use_count(); };

protected:
    virtual void onLastDestruction() {};

private:
    std::shared_ptr<void> m_counter;
};