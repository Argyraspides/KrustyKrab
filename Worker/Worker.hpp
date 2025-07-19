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
        m_Running = false;
        m_WorkerThread.join();
    }

    void Start()
    {
        m_Running = true;
        m_WorkerThread = std::thread(&Worker::Work, this);
    }

protected:

    virtual void Work() {};
    bool m_Running;

private:

    std::thread m_WorkerThread;
};
