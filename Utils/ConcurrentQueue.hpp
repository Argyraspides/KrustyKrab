//
// Created by gaugamela on 7/18/25.
//
#pragma once
#include <atomic>
#include <mutex>
#include <queue>
#include <optional>
#include <functional>
#include <iostream>

template <typename T>
class ConcurrentQueue
{

public:

    ConcurrentQueue() :
    m_Queue(std::queue<T>()),
    m_QueueSize(std::atomic<size_t>(0)),
    m_QueueMutex(std::mutex())
    {
    }

    ~ConcurrentQueue() = default;

    void Enqueue(const T& item)
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_Queue.push(item);
        ++m_QueueSize;
    }

    std::optional<T> Dequeue()
    {
        std::unique_lock<std::mutex> lock1(m_QueueMutex);
        if (m_Queue.empty())
        {
            return std::nullopt;
        }

        const T elem = m_Queue.front();

        m_Queue.pop();
        --m_QueueSize;

        return elem;
    }

    [[nodiscard]] size_t Count() const {
        return m_QueueSize.load();
    }

    [[nodiscard]] const std::atomic<size_t>& CountAtomic() const {
        return m_QueueSize;
    }

private:

    std::queue<T> m_Queue;
    std::atomic<size_t> m_QueueSize;
    std::mutex m_QueueMutex;
};