//
// Created by gaugamela on 7/18/25.
//

#pragma once
#include <chrono>
#include <thread>

class Worker
{

  public:
    Worker()
        : m_Running(false)
    {
    }

    virtual ~Worker()
    {
        Stop();
    }

    void Start()
    {
        m_Running = true;
        m_WorkerThread = std::thread(&Worker::Work, this);
    }

    void Stop()
    {
        StopLoop();
        if (!m_WorkerThread.joinable())
        {
            return;
        }
        m_WorkerThread.join();
    }

    void StopLoop()
    {
        m_Running = false;
    }

  protected:
    virtual void Work() {};
    bool m_Running;

  private:
    std::thread m_WorkerThread;
};
