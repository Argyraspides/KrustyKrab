//
// Created by gaugamela on 7/18/25.
//

#pragma once
#include "DeliveryTruck.hpp"
#include "Freezer.hpp"
#include "Patrick.hpp"
#include "SpongeBob.hpp"
#include "Squidward.hpp"
#include <condition_variable>
#include <memory>

class KrustyKrab
{

  public:
    KrustyKrab();
    ~KrustyKrab();

    void Open();
    bool WorkersReady() const;
    void StartWorkers();
    void WaitUntilTicketsEmpty();
    void StopWorkers();

  private:
    static void PrintLn(const std::string& msg);
    void PrintFinalStats() const;

  private:
    std::mutex m_TicketLineMutex;
    std::condition_variable m_TicketCv;
    std::shared_ptr<std::queue<Ticket>> m_TicketLine;

    std::shared_ptr<Freezer> m_Freezer;

    DeliveryTruck m_DeliveryTruck;

    Squidward m_Squidward;
    SpongeBob m_SpongeBob;
    Patrick m_Patrick;
};
