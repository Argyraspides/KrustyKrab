//
// Created by gaugamela on 7/18/25.
//

#pragma once
#include <thread>
#include <chrono>

class Worker {

public:

    Worker() : m_Running(false) {}

    virtual ~Worker()
    {
        StopLoop();
        Join();
    }

    void Start()
    {
        m_Running = true;
        m_WorkerThread = std::thread(&Worker::Work, this);
    }

    void StopLoop()
    {
        m_Running = false;
    }

    void Join()
    {
        if (!m_WorkerThread.joinable())
        {
            return;
        }
        m_WorkerThread.join();
    }

protected:

    virtual void Work() {};
    bool m_Running;

private:

    std::thread m_WorkerThread;
};
