//
// Created by gaugamela on 7/18/25.
//

#pragma once
#include <memory>
#include <condition_variable>
#include "SpongeBob.hpp"
#include "Patrick.hpp"
#include "Squidward.hpp"
#include "Freezer.hpp"
#include "DeliveryTruck.hpp"

class KrustyKrab
{

public:
    KrustyKrab();
    ~KrustyKrab();

    void Open();
    bool WorkersReady();
    void StartWorkers();
    void StopWorkers();

private:
    void PrintLn(const std::string& msg);
    void PrintFinalStats() const;

private:

    std::mutex m_TicketLineMutex;
    std::condition_variable m_TicketCv;
    std::shared_ptr<std::queue<Ticket>> m_TicketLine;

    std::shared_ptr<Freezer> m_Freezer;
    std::shared_ptr<DeliveryTruck> m_DeliveryTruck;

    std::unique_ptr<Squidward> m_Squidward;
    std::unique_ptr<SpongeBob> m_SpongeBob;
    std::unique_ptr<Patrick> m_Patrick;
};
