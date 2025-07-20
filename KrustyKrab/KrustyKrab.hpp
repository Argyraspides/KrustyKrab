//
// Created by gaugamela on 7/18/25.
//

#pragma once
#include "SpongeBob.hpp"
#include "Patrick.hpp"
#include "Squidward.hpp"
#include "Freezer.hpp"
#include "RandomTicketGenerator.hpp"
#include <memory>


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

    std::shared_ptr<ConcurrentQueue<Ticket>> m_TicketLine;

    std::unique_ptr<RandomTicketGenerator> m_RandomTicketGenerator;
    std::shared_ptr<ConcurrentQueue<Ticket>> m_FinishedTicketLine;
    std::shared_ptr<Freezer> m_Freezer;

    std::unique_ptr<SpongeBob> m_SpongeBob;
    std::unique_ptr<Patrick> m_Patrick;
    std::unique_ptr<Squidward> m_Squidward;
};
