//
// Created by gaugamela on 7/18/25.
//

#include "SpongeBob.hpp"
#include "MenuItemFactory.hpp"

const std::string YELLOW_ANSI_SEQ = "\033[93m";
const std::string PINK_ANSI_SEQ = "\033[0;95m";
const std::string RESET_ANSI_SEQ = "\033[0m";

SpongeBob::SpongeBob(std::weak_ptr<ConcurrentQueue<Ticket>> ticketLine, std::weak_ptr<Freezer> freezer, bool IsActuallyPatrick) :
    m_TicketLine(std::move(ticketLine)),
    m_Freezer(std::move(freezer)),
    m_IsActuallyPatrick(IsActuallyPatrick),
    m_TicketsCompleted(0),
    m_MenuItemsCompleted(0)
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
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::optional<Ticket> nextTicket = TryGetTicket();

        if (!nextTicket.has_value())
        {
            continue;
        }

        PrepareOrder(nextTicket.value());

        m_MenuItemsCompleted += nextTicket.value().m_MenuItems.size();
        m_TicketsCompleted++;
    }

    PrintLn(WhoAmI() + " finished " + std::to_string(m_TicketsCompleted) + " tickets and " + std::to_string(m_MenuItemsCompleted) + " menu items");
}

void SpongeBob::PrepareOrder(const Ticket& ticket)
{
    for (const auto& menuItem : ticket.m_MenuItems)
    {
        switch (menuItem.m_MenuItemName)
        {
            case Menu::EMenuItem::KrabbyPatty:
                MakeKrabbyPatty();
                break;
            default:;
        }
    }
}

void SpongeBob::MakeKrabbyPatty()
{
    const std::vector<Ingredient>& ingredients = MenuItemFactory::GetKrabbyPattyIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetKrabbyPattyIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        switch (ingredients[i])
        {
            case Ingredient::Bun:
                // Put in a request for buns. Once fulfilled, wake up SpongeBob and continue?
                break;
            default:;
        }
    }

}

std::optional<Ticket> SpongeBob::TryGetTicket()
{
    std::shared_ptr<ConcurrentQueue<Ticket>> ticketLine = m_TicketLine.lock();
    if (!ticketLine)
    {
        return std::nullopt;
    }

    std::optional<Ticket> nextTicket = ticketLine->Dequeue();

    if (!nextTicket.has_value())
    {
        return std::nullopt;
    }

    return nextTicket;
}

std::string SpongeBob::WhoAmI()
{
    return m_IsActuallyPatrick ? "Patrick" : "Spongebob";
}
