//
// Created by gaugamela on 7/19/25.
//

#include "MenuItemFactory.hpp"
#include "ConcurrentQueue.hpp"
#include "Ticket.hpp"
#include "Worker.hpp"
#include <memory>
#include <thread>

class RandomTicketGenerator : public Worker
{
public:
    RandomTicketGenerator(std::weak_ptr<ConcurrentQueue<Ticket>> ticketLine) :
    m_TicketLine(std::move(ticketLine)),
    m_TotalTicketsGenerated(0),
    m_TotalMenuItemsGenerated(0)
    {
        std::cout << "RandomTicketGenerator()" << "\n";
    }

    ~RandomTicketGenerator()
    {
        std::cout << "~RandomTicketGenerator()" << "\n";
    }

protected:
    void Work() override {

        while (m_Running) {
            std::this_thread::sleep_for(std::chrono::seconds(2));

            int randomItemCount = 3;

            Ticket randomTicket;
            for (int i = 0; i < randomItemCount; i++) {
                MenuItem randomItem = MenuItemFactory::MakeKrabbyPatty();
                randomTicket.m_MenuItems.push_back(randomItem);
            }

            std::shared_ptr<ConcurrentQueue<Ticket>> ticketLine = m_TicketLine.lock();

            if (!ticketLine) {
                break;
            }

            ticketLine->Enqueue(randomTicket);
            m_TotalTicketsGenerated++;
            m_TotalMenuItemsGenerated += randomItemCount;
        }

        std::cout << "RandomTicketGenerator made a total of " + std::to_string(m_TotalTicketsGenerated) + " tickets and " + std::to_string(m_TotalMenuItemsGenerated) + " menu items\n";

    }

private:
    std::weak_ptr<ConcurrentQueue<Ticket>> m_TicketLine;
    unsigned long long int m_TotalTicketsGenerated;
    unsigned long long int m_TotalMenuItemsGenerated;

};