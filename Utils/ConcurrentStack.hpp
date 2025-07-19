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
    ConcurrentStack() = default;
    ~ConcurrentStack() = default;

    void Push(T elem)
    {
        std::unique_lock<std::mutex> lock(m_StackMutex);
        m_Stack.push(elem);
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
        return elem;
    }

private:
    std::stack<T> m_Stack;
    std::mutex m_StackMutex;

};