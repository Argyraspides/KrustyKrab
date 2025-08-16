//
// Created by gaugamela on 7/19/25.
//

#pragma once

#include "MenuItemFactory.hpp"
#include "Rng.hpp"
#include "Ticket.hpp"
#include "Worker.hpp"
#include <functional>
#include <memory>
#include <random>
#include <thread>

struct RandomTicketStats_t
{
    unsigned long long m_TicketsGenerated = 0;
    std::unordered_map<Menu::EMenuItem, size_t> m_MenuItemsGenerated;
};

class RandomTicketGenerator : public Worker
{
  public:
    RandomTicketGenerator(std::queue<Ticket>& ticketLine,
                          std::mutex& ticketLineMutex,
                          std::condition_variable& ticketCv)
        : m_TicketLine(ticketLine),
          m_TicketLineMutex(ticketLineMutex),
          m_TicketCv(ticketCv),
          m_RandomDevice(std::random_device()),
          m_MinRandomTickets(1),
          m_MaxRandomTickets(5),
          m_GenerationWaitTimeMs(Rng::RandomInt(MINIMUM_NEXT_TICKET_GEN_TIME_MS, MAXIMUM_NEXT_TICKET_GEN_TIME_MS)),
          m_UniformIntDist(std::uniform_int_distribution<size_t>(m_MinRandomTickets, m_MaxRandomTickets)),
          m_MenuItemDist(
              std::uniform_int_distribution<size_t>(0, static_cast<size_t>(Menu::EMenuItem::MENU_ITEM_COUNT) - 1)),
          m_MerseneTwister(std::mt19937(m_RandomDevice())),
          m_RandomItemFuncs(std::vector<std::function<Menu::MenuItem_t()>>()),
          m_RandomTicketStats(RandomTicketStats_t())
    {
        std::cout << "RandomTicketGenerator()" << "\n";
    }

    ~RandomTicketGenerator() override
    {
        std::cout << "~RandomTicketGenerator()" << "\n";
    }

    const RandomTicketStats_t& TicketStats() const
    {
        return m_RandomTicketStats;
    }

  protected:
    void Work() override
    {

        while (m_Running)
        {
            m_GenerationWaitTimeMs = std::chrono::milliseconds(
                Rng::RandomInt(MINIMUM_NEXT_TICKET_GEN_TIME_MS, MAXIMUM_NEXT_TICKET_GEN_TIME_MS));
            std::this_thread::sleep_for(m_GenerationWaitTimeMs);

            Ticket randomTicket;
            size_t randomNumberOfMenuItems = m_UniformIntDist(m_MerseneTwister);
            for (size_t i = 0; i < randomNumberOfMenuItems; i++)
            {
                // Get random factory function from MenuItemFactory
                size_t randomItemIndex = m_MenuItemDist(m_MerseneTwister);
                Menu::MenuItem_t randomItem =
                    MenuItemFactory::CreateMenuItem(static_cast<Menu::EMenuItem>(randomItemIndex));
                randomTicket.m_MenuItems.push_back(randomItem);

                // Add to generated statistics
                m_RandomTicketStats.m_MenuItemsGenerated[randomItem.m_MenuItemName]++;
            }

            {
                std::unique_lock<std::mutex> lock(m_TicketLineMutex);
                m_TicketLine.push(randomTicket);
            }

            m_TicketCv.notify_all();

            m_RandomTicketStats.m_TicketsGenerated++;
        }
    }

  private:
    std::queue<Ticket>& m_TicketLine;
    std::mutex& m_TicketLineMutex;
    std::condition_variable& m_TicketCv;

    std::random_device m_RandomDevice;
    const size_t m_MinRandomTickets;
    const size_t m_MaxRandomTickets;
    std::chrono::milliseconds m_GenerationWaitTimeMs;
    std::uniform_int_distribution<size_t> m_UniformIntDist;
    std::uniform_int_distribution<size_t> m_MenuItemDist;
    std::mt19937 m_MerseneTwister;
    std::vector<std::function<Menu::MenuItem_t()>> m_RandomItemFuncs;

    RandomTicketStats_t m_RandomTicketStats;

    static constexpr int MINIMUM_NEXT_TICKET_GEN_TIME_MS = 10;
    static constexpr int MAXIMUM_NEXT_TICKET_GEN_TIME_MS = 75;
};