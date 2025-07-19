//
// Created by gaugamela on 7/18/25.
//
#pragma once
#include <mutex>
#include <queue>
#include <optional>

template <typename T>
class ConcurrentQueue
{

public:

    ConcurrentQueue() = default;
    ~ConcurrentQueue() = default;

    void Enqueue(const T& item)
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_Queue.push(item);
    }

    std::optional<T> Dequeue()
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);

        if (m_Queue.empty())
        {
            return std::nullopt;
        }

        const T elem = m_Queue.front();
        m_Queue.pop();
        return elem;
    }

    size_t Count()
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        return static_cast<size_t>(m_Queue.size());
    }

private:
    std::queue<T> m_Queue;
    std::mutex m_QueueMutex;
};