//
// Created by gaugamela on 7/19/25.
//

#include "MenuItemFactory.hpp"
#include "ConcurrentQueue.hpp"
#include "Ticket.hpp"
#include "Worker.hpp"
#include <memory>
#include <thread>
#include <random>
#include <functional>

class RandomTicketGenerator : public Worker
{
public:
    RandomTicketGenerator(std::weak_ptr<ConcurrentQueue<Ticket>> ticketLine) :
    m_TicketLine(std::move(ticketLine)),
    m_TotalTicketsGenerated(0),
    m_TotalMenuItemsGenerated(0),
    m_RandomDevice(std::random_device()),
    m_MinRandomTickets(1),
    m_MaxRandomTickets(5),
    m_UniformIntDist(std::uniform_int_distribution<size_t>(m_MinRandomTickets, m_MaxRandomTickets)),
    m_MenuItemDist(std::uniform_int_distribution<size_t>(0, MenuItems::TotalMenuItems() - 1)),
    m_MerseneTwister(std::mt19937(m_RandomDevice())),
    m_RandomItemFuncs(std::vector<std::function<MenuItem()>>())
    {
        std::cout << "RandomTicketGenerator()" << "\n";
        m_RandomItemFuncs.reserve(MenuItems::TotalMenuItems());
        m_RandomItemFuncs.push_back(MenuItemFactory::MakeKrabbyPatty);
    }

    ~RandomTicketGenerator()
    {
        std::cout << "~RandomTicketGenerator()" << "\n";
    }

protected:
    void Work() override
    {

        while (m_Running)
        {
            size_t randomItemCount = m_UniformIntDist(m_MerseneTwister);
            Ticket randomTicket;
            for (size_t i = 0; i < randomItemCount; i++)
            {
                size_t randomItemIndex = m_MenuItemDist(m_MerseneTwister);
                MenuItem randomItem = m_RandomItemFuncs[randomItemIndex]();
                randomTicket.m_MenuItems.push_back(randomItem);
            }

            std::shared_ptr<ConcurrentQueue<Ticket>> ticketLine = m_TicketLine.lock();
            if (!ticketLine)
            {
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

    std::random_device m_RandomDevice;
    const size_t m_MinRandomTickets;
    const size_t m_MaxRandomTickets;
    std::uniform_int_distribution<size_t> m_UniformIntDist;
    std::uniform_int_distribution<size_t> m_MenuItemDist;
    std::mt19937 m_MerseneTwister;
    std::vector<std::function<MenuItem()>> m_RandomItemFuncs;

};