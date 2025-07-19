#pragma once
#include <iostream>
#include <memory>
#include "ConcurrentQueue.hpp"
#include "Worker.hpp"
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
    std::string WhoAmI();

private:
    std::weak_ptr<ConcurrentQueue<Ticket>> m_TicketLine;
    std::weak_ptr<Freezer> m_Freezer;
    bool m_IsActuallyPatrick;

};