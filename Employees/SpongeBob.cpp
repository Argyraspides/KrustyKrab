//
// Created by gaugamela on 7/18/25.
//

#include "SpongeBob.hpp"
#include "MenuItemFactory.hpp"

const std::string YELLOW_ANSI_SEQ = "\033[93m";
const std::string PINK_ANSI_SEQ = "\033[0;95m";
const std::string RESET_ANSI_SEQ = "\033[0m";

SpongeBob::SpongeBob(
    std::weak_ptr<std::queue<Ticket>> ticketLine,
    std::mutex& ticketLineMutex,
    std::condition_variable& ticketCv,
    std::weak_ptr<Freezer> freezer,
    bool IsActuallyPatrick) :
    m_TicketLine(std::move(ticketLine)),
    m_TicketLineMutex(ticketLineMutex),
    m_TicketCv(ticketCv),
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
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        Ticket nextTicket = TryGetTicket();

        if (nextTicket.m_MenuItems.empty())
        {
            continue;
        }

        PrepareOrder(nextTicket);

        m_MenuItemsCompleted += nextTicket.m_MenuItems.size();
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

Ticket SpongeBob::TryGetTicket() const
{
    std::shared_ptr<std::queue<Ticket>> ticketLine = m_TicketLine.lock();
    if (!ticketLine)
    {
        return Ticket {};
    }

    {
        std::unique_lock<std::mutex> lock(m_TicketLineMutex);
        m_TicketCv.wait(lock, [&](){ return !ticketLine->empty() || !m_Running; });

        if (!ticketLine->empty())
        {
            Ticket t = ticketLine->front();
            ticketLine->pop();
            return t;
        }
    }

    return Ticket {};

}

std::string SpongeBob::WhoAmI() const
{
    return m_IsActuallyPatrick ? "Patrick" : "Spongebob";
}

