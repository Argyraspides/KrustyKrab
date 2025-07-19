//
// Created by gaugamela on 7/18/25.
//

#include "KrustyKrab.hpp"
#include "MenuItemFactory.hpp"

KrustyKrab::KrustyKrab() :
    m_TicketLine(std::make_shared<ConcurrentQueue<Ticket>>()),
    m_Freezer(std::make_shared<Freezer>()),
    m_SpongeBob(std::make_unique<SpongeBob>(m_TicketLine, m_Freezer)),
    m_Patrick(std::make_unique<Patrick>(m_TicketLine, m_Freezer, true)),
    m_Squidward(std::make_unique<Squidward>(m_TicketLine))
{
}

KrustyKrab::~KrustyKrab()
{
}

void KrustyKrab::LoadTickets()
{
    Ticket t1;
    t1.m_MenuItems = std::vector< MenuItem > { MenuItemFactory::MakeKrabbyPatty() };
    t1.m_MenuItemCounts = std::vector< uint32_t > { 1 };

    m_TicketLine->Enqueue(t1);
    m_TicketLine->Enqueue(t1);
    m_TicketLine->Enqueue(t1);
    m_TicketLine->Enqueue(t1);
    m_TicketLine->Enqueue(t1);

}


void KrustyKrab::Open()
{
    if (!WorkersReady())
    {
        return;
    }

    LoadTickets();
    StartWorkers();
}

bool KrustyKrab::WorkersReady()
{
    if (!m_Patrick || !m_SpongeBob || !m_Squidward)
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
