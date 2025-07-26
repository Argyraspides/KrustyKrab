//
// Created by gaugamela on 7/18/25.
//

#include "KrustyKrab.hpp"
#include "MenuItemFactory.hpp"

KrustyKrab::KrustyKrab() :
    m_TicketLine(std::make_shared<std::queue<Ticket>>()),
    m_TicketLineMutex(std::mutex()),
    m_TicketCv(std::condition_variable()),
    m_Squidward(std::make_unique<Squidward>(m_TicketLine, m_TicketLineMutex, m_TicketCv)),
    m_Freezer(std::make_shared<Freezer>()),
    m_SpongeBob(std::make_unique<SpongeBob>(m_TicketLine, m_TicketLineMutex, m_TicketCv, m_Freezer)),
    m_Patrick(std::make_unique<Patrick>(m_TicketLine, m_TicketLineMutex, m_TicketCv, m_Freezer, true))
{
    std::cout << "KrustyKrab()" << "\n";
}

KrustyKrab::~KrustyKrab()
{
    StopWorkers();
    std::unique_lock<std::mutex> lock(m_TicketLineMutex);
    std::cout << "Tickets remaining: " << std::to_string(m_TicketLine->size()) << "\n";
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
        !m_Squidward
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
}

void KrustyKrab::StopWorkers()
{
    m_Squidward->StopLoop();
    m_Patrick->StopLoop();
    m_SpongeBob->StopLoop();

    m_TicketCv.notify_all();
}
