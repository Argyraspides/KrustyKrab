//
// Created by gaugamela on 7/19/25.
//

#include "Squidward.hpp"
#include <iostream>
#include <ostream>
#include <utility>

const std::string GRAYBLUE_ANSI_SEQ = "\033[96m";
const std::string RESET_ANSI_SEQ = "\033[0m";

Squidward::Squidward(std::weak_ptr<ConcurrentQueue<Ticket>> ticketLine) : m_TicketLine(std::move(ticketLine))
{
    PrintLn("Squidward()");
}

Squidward::~Squidward()
{
    PrintLn("~Squidward()");
}

void Squidward::PrintLn(const std::string &str) {
    std::cout << (GRAYBLUE_ANSI_SEQ + str + "\n" + RESET_ANSI_SEQ);
}

void Squidward::Work()
{
    while (m_Running)
    {
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    PrintLn("Squidward stopped working");
}

