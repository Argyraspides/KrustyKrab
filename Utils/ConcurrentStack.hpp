//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <stack>
#include <mutex>
#include <optional>

template <typename T>
class ConcurrentStack
{

public:
    ConcurrentStack() : m_Stack(std::stack<T>()), m_StackMutex(std::mutex()), m_StackSize(std::atomic<size_t>(0)) {}
    ~ConcurrentStack() = default;

    void Push(T elem)
    {
        std::unique_lock<std::mutex> lock(m_StackMutex);
        m_Stack.push(elem);
        ++m_StackSize;
    }

    std::optional<T> Pop()
    {
        std::unique_lock<std::mutex> lock(m_StackMutex);

        if (m_Stack.empty())
        {
            return std::nullopt;
        }

        T elem = m_Stack.top();
        m_Stack.pop();
        --m_StackSize;
        return elem;
    }

    [[nodiscard]] size_t Count() const
    {
        return m_StackSize.load();
    }

private:
    std::stack<T> m_Stack;
    std::mutex m_StackMutex;

    std::atomic<size_t> m_StackSize;

};