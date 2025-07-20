//
// Created by gaugamela on 7/18/25.
//

#include "KrustyKrab.hpp"
#include "MenuItemFactory.hpp"

KrustyKrab::KrustyKrab() :
    m_TicketLine(std::make_shared<ConcurrentQueue<Ticket>>()),
    m_RandomTicketGenerator(std::make_unique<RandomTicketGenerator>(m_TicketLine)),
    m_FinishedTicketLine(std::make_unique<ConcurrentQueue<Ticket>>()),
    m_Freezer(std::make_shared<Freezer>()),
    m_SpongeBob(std::make_unique<SpongeBob>(m_TicketLine, m_Freezer)),
    m_Patrick(std::make_unique<Patrick>(m_TicketLine, m_Freezer, true)),
    m_Squidward(std::make_unique<Squidward>(m_TicketLine))
{
    std::cout << "KrustyKrab()" << "\n";
}

KrustyKrab::~KrustyKrab()
{
    StopWorkers();
    std::cout << "Tickets remaining: " << std::to_string(m_TicketLine->Count()) << "\n";
    std::cout << "~KrustyKrab()" << "\n";
}

void KrustyKrab::Open()
{
    if (!WorkersReady())
    {
        return;
    }
    StartWorkers();
}

bool KrustyKrab::WorkersReady()
{
    if
    (
        !m_Patrick ||
        !m_SpongeBob ||
        !m_Squidward ||
        !m_RandomTicketGenerator
    )
    {
        std::cout << "CAN'T OPEN THE KRUSTY KRAB!" << std::endl;
        return false;
    }

    return true;
}

void KrustyKrab::StartWorkers()
{
    m_Patrick->Start();
    m_SpongeBob->Start();
    m_Squidward->Start();
    m_RandomTicketGenerator->Start();
}

void KrustyKrab::StopWorkers()
{
    m_RandomTicketGenerator->Stop();  // Give SpongeBob & Patrick a chance to finish
    const std::atomic<size_t>& queueSize = m_TicketLine->CountAtomic();

    // TODO: This is shit. Come up with clean event based solution.
    while (queueSize.load() != 0) {}
    std::cout << "All orders are now finished\n";

    m_Patrick->Stop();
    m_SpongeBob->Stop();
    m_Squidward->Stop();
}
