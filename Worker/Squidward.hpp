//
// Created by gaugamela on 7/19/25.
//

#pragma once
#include <memory>

#include "Worker.hpp"
#include "ConcurrentQueue.hpp"
#include "Ticket.hpp"

class Squidward : public Worker
{

public:

    explicit Squidward(std::weak_ptr<ConcurrentQueue<Ticket>> ticketLine);
    ~Squidward() override;
    void PrintLn(const std::string& str);

protected:
    void Work() override;

private:
    std::weak_ptr<ConcurrentQueue<Ticket>> m_TicketLine;
};
