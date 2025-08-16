//
// Created by gaugamela on 7/18/25.
//

#include "SpongeBob.hpp"
#include "MenuItemFactory.hpp"
#include "Rng.hpp"

const std::string YELLOW_ANSI_SEQ = "\033[93m";
const std::string PINK_ANSI_SEQ = "\033[0;95m";
const std::string RESET_ANSI_SEQ = "\033[0m";
constexpr int MINIMUM_REST_TIME_MS = 1;
constexpr int MAXIMUM_REST_TIME_MS = 15;

SpongeBob::SpongeBob(std::queue<Ticket>& ticketLine,
                     std::mutex& ticketLineMutex,
                     std::condition_variable& ticketCv,
                     Freezer& freezer,
                     bool IsActuallyPatrick)
    : m_TicketLine(ticketLine),
      m_TicketLineMutex(ticketLineMutex),
      m_TicketCv(ticketCv),
      m_RestTimeMs(std::chrono::milliseconds(Rng::RandomInt(MINIMUM_REST_TIME_MS, MAXIMUM_REST_TIME_MS))),
      m_Freezer(freezer),
      m_IngredientsCv(std::condition_variable()),
      m_IsActuallyPatrick(IsActuallyPatrick),
      m_FrycookStats(FrycookStats_t())
{
    PrintLn(WhoAmI() + "()");
}

SpongeBob::~SpongeBob()
{
    PrintLn("~" + WhoAmI() + "()");
}

void SpongeBob::PrintLn(const std::string& str) const
{
    std::cout << ((m_IsActuallyPatrick ? PINK_ANSI_SEQ : YELLOW_ANSI_SEQ) + str + "\n" + RESET_ANSI_SEQ);
}

void SpongeBob::WakeUp()
{
    m_TicketCv.notify_all();
    m_IngredientsCv.notify_all();
}

const FrycookStats_t& SpongeBob::WorkerStats() const
{
    return m_FrycookStats;
}

void SpongeBob::Work()
{
    while (m_Running)
    {
        Ticket nextTicket = TryGetTicket();

        if (nextTicket.m_MenuItems.empty())
            continue;

        PrepareOrder(nextTicket);
    }
}

void SpongeBob::PrepareOrder(const Ticket& ticket)
{
    for (auto& menuItem : ticket.m_MenuItems)
    {
        GetIngredients(menuItem.m_Ingredients, menuItem.m_IngredientCounts);

        // SpongeBob is very inconsistent with his preparation times
        m_RestTimeMs = std::chrono::milliseconds(Rng::RandomInt(MINIMUM_REST_TIME_MS, MAXIMUM_REST_TIME_MS));
        std::this_thread::sleep_for(m_RestTimeMs);

        m_FrycookStats.m_CompletedMenuItems[menuItem.m_MenuItemName]++;
    }
    m_FrycookStats.m_TicketsCompleted++;
}

Ticket SpongeBob::TryGetTicket() const
{
    Ticket finalTicket = {};

    bool nowEmpty = false;
    {
        std::unique_lock<std::mutex> lock(m_TicketLineMutex);
        m_TicketCv.wait(lock, [&]() { return !m_TicketLine.empty() || !m_Running; });

        if (!m_TicketLine.empty())
        {
            finalTicket = m_TicketLine.front();
            m_TicketLine.pop();
            nowEmpty = m_TicketLine.empty();
        }
    }

    // To notify the krusty krab that the tickets are now empty.
    // Idk why but I don't like this. Why should spongebob give a shit about notifying the krusty krab?
    if (nowEmpty)
        m_TicketCv.notify_all();

    return finalTicket;
}

void SpongeBob::GetIngredients(const std::vector<Menu::EIngredient>& ingredients,
                               const std::vector<size_t>& ingredientCount)
{
    for (int i = 0; i < ingredients.size(); i++)
    {
        bool requestFulfilled = false;

        IngredientRequest_t ir{m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i]};
        m_Freezer.RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(m_Freezer.IngredientsMutex());

        m_IngredientsCv.wait(lock, [&]() { return requestFulfilled || !m_Running; });
    }
}

std::string SpongeBob::WhoAmI() const
{
    return m_IsActuallyPatrick ? "Patrick" : "Spongebob";
}
