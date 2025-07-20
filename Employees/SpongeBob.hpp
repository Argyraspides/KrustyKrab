#pragma once
#include <iostream>
#include <memory>
#include "ConcurrentQueue.hpp"
#include "../Utils/Worker.hpp"
#include "Ticket.hpp"
#include "Freezer.hpp"

class SpongeBob : public Worker
{

public:
    SpongeBob(std::weak_ptr<ConcurrentQueue<Ticket>> ticketLine, std::weak_ptr<Freezer> freezer, bool IsActuallyPatrick = false);
    ~SpongeBob() override;
    void PrintLn(const std::string& str);

protected:
    void Work() override;

private:
    // I'm sorry, Patrick ...
    std::string WhoAmI();
    void PrepareOrder(const Ticket& ticket);
    void MakeKrabbyPatty();
    std::optional<Ticket> TryGetTicket();

private:
    std::weak_ptr<ConcurrentQueue<Ticket>> m_TicketLine;
    std::weak_ptr<Freezer> m_Freezer;

    // I'M SORRY, PATRICK!
    bool m_IsActuallyPatrick;

    unsigned long long int m_TicketsCompleted;
    unsigned long long int m_MenuItemsCompleted;

};