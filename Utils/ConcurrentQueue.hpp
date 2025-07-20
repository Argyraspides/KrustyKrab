//
// Created by gaugamela on 7/18/25.
//
#pragma once
#include <atomic>
#include <mutex>
#include <queue>
#include <optional>
#include <condition_variable>
#include <iostream>

template <typename T>
class ConcurrentQueue
{

public:

    ConcurrentQueue() :
    m_Queue(std::queue<T>()),
    m_QueueSize(std::atomic<size_t>(0)),
    m_QueueMutex(std::mutex()),
    m_QueueEmptyCv(std::condition_variable())
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

        if (m_Queue.empty()) return std::nullopt;

        const T elem = m_Queue.front();

        m_Queue.pop();

        if (--m_QueueSize == 0) m_QueueEmptyCv.notify_all();

        return elem;
    }

    [[nodiscard]] size_t Count() const {
        return m_QueueSize.load();
    }

    void WaitUntilEmpty()
    {
        std::unique_lock<std::mutex> lock(m_QueueMutex);
        m_QueueEmptyCv.wait(lock, [&]() { return Count() == 0; });
    }

private:

    std::queue<T> m_Queue;
    std::atomic<size_t> m_QueueSize;
    std::mutex m_QueueMutex;
    std::condition_variable m_QueueEmptyCv;
};