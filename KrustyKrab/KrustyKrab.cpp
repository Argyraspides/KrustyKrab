//
// Created by gaugamela on 7/18/25.
//

#include "KrustyKrab.hpp"
#include "MenuItemFactory.hpp"

const std::string RED_ANSI_SEQ = "\033[31m";
const std::string RESET_ANSI_SEQ = "\033[0m";

KrustyKrab::KrustyKrab() :
    m_TicketLineMutex(std::mutex()),
    m_TicketCv(std::condition_variable()),
    m_TicketLine(std::make_shared<std::queue<Ticket>>()),
    m_Freezer(std::make_shared<Freezer>()),
    m_DeliveryTruck(std::make_shared<DeliveryTruck>(m_Freezer)),
    m_Squidward(std::make_unique<Squidward>(m_TicketLine, m_TicketLineMutex, m_TicketCv)),
    m_SpongeBob(std::make_unique<SpongeBob>(m_TicketLine, m_TicketLineMutex, m_TicketCv, m_Freezer)),
    m_Patrick(std::make_unique<Patrick>(m_TicketLine, m_TicketLineMutex, m_TicketCv, m_Freezer, true))
{
    PrintLn("KrustyKrab()");
}

KrustyKrab::~KrustyKrab()
{
    StopWorkers();
    std::unique_lock<std::mutex> lock(m_TicketLineMutex);
    PrintLn("Tickets remaining: " + std::to_string(m_TicketLine->size()));
    PrintLn("~KrustyKrab()");
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
    m_Squidward->Start();
    m_Freezer->Start();
    m_DeliveryTruck->Start();
    m_Patrick->Start();
    m_SpongeBob->Start();
}

void KrustyKrab::StopWorkers()
{
    m_Squidward->Stop();

    PrintLn("The Krusty Krab is about to close. Waiting for Patrick & SpongeBob to finish their tickets ...");
    m_Freezer->WaitUntilReqsEmpty();
    PrintLn("Patrick & SpongeBob have finished their tickets!");

    m_Freezer->StopLoop();
    m_Freezer->WakeUp();
    m_Freezer->Stop();

    m_DeliveryTruck->Stop();

    m_Patrick->StopLoop();
    m_Patrick->WakeUp();
    m_Patrick->Stop();

    m_SpongeBob->StopLoop();
    m_SpongeBob->WakeUp();
    m_SpongeBob->Stop();
}

void KrustyKrab::PrintLn(const std::string &msg)
{
    std::cout << RED_ANSI_SEQ << msg << "\n" << RESET_ANSI_SEQ;
}

void KrustyKrab::PrintFinalStats()
{
    const FrycookStats_t& spongebobStats = m_SpongeBob->WorkerStats();
    const FrycookStats_t& patrickStats = m_Patrick->WorkerStats();
    const RandomTicketStats_t ticketGeneratorStats = m_Squidward->TicketStats();
    const FreezerStats_t freezerStats = m_Freezer->


}
