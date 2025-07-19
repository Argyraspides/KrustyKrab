//
// Created by gaugamela on 7/18/25.
//

#include "SpongeBob.hpp"

const std::string YELLOW_ANSI_SEQ = "\033[93m";
const std::string PINK_ANSI_SEQ = "\033[0;95m";
const std::string RESET_ANSI_SEQ = "\033[0m";

SpongeBob::SpongeBob(std::weak_ptr<ConcurrentQueue<Ticket>> ticketLine, std::weak_ptr<Freezer> freezer, bool IsActuallyPatrick) :
    m_TicketLine(std::move(ticketLine)),
    m_Freezer(std::move(freezer)),
    m_IsActuallyPatrick(IsActuallyPatrick)
{
   PrintLn(WhoAmI() + "()");
}

SpongeBob::~SpongeBob()
{
   PrintLn("~" + WhoAmI() + "()");
}

void SpongeBob::PrintLn(const std::string &str) {
    std::cout << ((m_IsActuallyPatrick ? PINK_ANSI_SEQ : YELLOW_ANSI_SEQ) + str + "\n" + RESET_ANSI_SEQ);
}

void SpongeBob::Work()
{
    while (m_Running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::shared_ptr<ConcurrentQueue<Ticket>> ticketLine = m_TicketLine.lock();
        if (!ticketLine)
        {
            break;
        }

        std::optional<Ticket> nextTicket = ticketLine->Dequeue();

        if (!nextTicket.has_value())
        {
            PrintLn("No tickets for " + WhoAmI() + " right now...");
            continue;
        }

        for (int i = 0; i < nextTicket.value().m_MenuItems.size(); i++)
        {
            PrintLn(WhoAmI() + " is going to make a " + nextTicket.value().m_MenuItems[i].m_MenuItemName);
        }
    }
    PrintLn(WhoAmI() + " stopped working");
}

std::string SpongeBob::WhoAmI() {
    return m_IsActuallyPatrick ? "Patrick" : "Spongebob";
}
