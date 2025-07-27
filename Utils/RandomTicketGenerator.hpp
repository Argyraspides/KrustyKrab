//
// Created by gaugamela on 7/19/25.
//

#pragma once

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
    RandomTicketGenerator(std::weak_ptr<std::queue<Ticket>> ticketLine, std::mutex& ticketLineMutex, std::condition_variable& ticketCv) :
    m_TicketLine(std::move(ticketLine)),
    m_TicketLineMutex(ticketLineMutex),
    m_TicketCv(ticketCv),
    m_TotalTicketsGenerated(0),
    m_TotalMenuItemsGenerated(0),
    m_RandomDevice(std::random_device()),
    m_MinRandomTickets(1),
    m_MaxRandomTickets(5),
    m_GenerationWaitTimeMs(std::chrono::milliseconds(1000)),
    m_UniformIntDist(std::uniform_int_distribution<size_t>(m_MinRandomTickets, m_MaxRandomTickets)),
    m_MenuItemDist(std::uniform_int_distribution<size_t>(0, Menu::TotalMenuItems() - 1)),
    m_MerseneTwister(std::mt19937(m_RandomDevice())),
    m_RandomItemFuncs(std::vector<std::function<Menu::MenuItem_t()>>())
    {
        std::cout << "RandomTicketGenerator()" << "\n";
        InitRandomMenuItemFuncs();
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
            std::this_thread::sleep_for(m_GenerationWaitTimeMs);
            Ticket randomTicket;
            size_t randomMenuItemCount = m_UniformIntDist(m_MerseneTwister);
            for (size_t i = 0; i < randomMenuItemCount; i++)
            {
                // Get random factory function from MenuItemFactory
                size_t randomItemIndex = m_MenuItemDist(m_MerseneTwister);
                Menu::MenuItem_t randomItem = m_RandomItemFuncs[randomItemIndex]();
                randomTicket.m_MenuItems.push_back(randomItem);
            }

            std::shared_ptr<std::queue<Ticket>> ticketLine = m_TicketLine.lock();
            if (!ticketLine) break;
            {
                std::unique_lock<std::mutex> lock(m_TicketLineMutex);
                ticketLine->push(randomTicket);
            }
            m_TicketCv.notify_all();

            m_TotalTicketsGenerated++;
            m_TotalMenuItemsGenerated += randomMenuItemCount;
        }

        std::cout << "RandomTicketGenerator made a total of " + std::to_string(m_TotalTicketsGenerated) + " tickets and " + std::to_string(m_TotalMenuItemsGenerated) + " menu items\n";
    }

private:
    void InitRandomMenuItemFuncs()
    {
        m_RandomItemFuncs.reserve(Menu::TotalMenuItems());

        m_RandomItemFuncs.emplace_back(MenuItemFactory::MakeKrabbyPatty);
    }

private:
    std::weak_ptr<std::queue<Ticket>> m_TicketLine;
    std::mutex& m_TicketLineMutex;
    std::condition_variable& m_TicketCv;
    unsigned long long int m_TotalTicketsGenerated;
    unsigned long long int m_TotalMenuItemsGenerated;

    std::random_device m_RandomDevice;
    const size_t m_MinRandomTickets;
    const size_t m_MaxRandomTickets;
    std::chrono::milliseconds m_GenerationWaitTimeMs;
    std::uniform_int_distribution<size_t> m_UniformIntDist;
    std::uniform_int_distribution<size_t> m_MenuItemDist;
    std::mt19937 m_MerseneTwister;
    std::vector<std::function<Menu::MenuItem_t()>> m_RandomItemFuncs;

};