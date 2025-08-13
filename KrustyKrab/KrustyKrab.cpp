//
// Created by gaugamela on 7/18/25.
//

#include <iomanip>
#include "KrustyKrab.hpp"
#include "MenuItemFactory.hpp"

const std::string RED_ANSI_SEQ = "\033[31m";
const std::string RESET_ANSI_SEQ = "\033[0m";

KrustyKrab::KrustyKrab() :
    m_TicketLineMutex(std::mutex()),
    m_TicketCv(std::condition_variable()),
    m_TicketLine(std::make_shared<std::queue<Ticket>>()),
    m_Freezer(std::make_shared<Freezer>()),
    m_DeliveryTruck(std::make_shared<DeliveryTruck>(m_Freezer)),
    m_Squidward(std::make_unique<Squidward>(m_TicketLine, m_TicketLineMutex, m_TicketCv)),
    m_SpongeBob(std::make_unique<SpongeBob>(m_TicketLine, m_TicketLineMutex, m_TicketCv, m_Freezer)),
    m_Patrick(std::make_unique<Patrick>(m_TicketLine, m_TicketLineMutex, m_TicketCv, m_Freezer, true))
{
    PrintLn("KrustyKrab()");
}

KrustyKrab::~KrustyKrab()
{
    StopWorkers();
    PrintFinalStats();
    PrintLn("~KrustyKrab()");
}

void KrustyKrab::Open()
{
    if (!WorkersReady())
    {
        return;
    }
    StartWorkers();
}

bool KrustyKrab::WorkersReady()
{
    if
    (
        !m_Patrick ||
        !m_SpongeBob ||
        !m_Squidward
    )
    {
        std::cout << "CAN'T OPEN THE KRUSTY KRAB!" << std::endl;
        return false;
    }

    return true;
}

void KrustyKrab::StartWorkers()
{
    m_Squidward->Start();
    m_Freezer->Start();
    m_DeliveryTruck->Start();
    m_Patrick->Start();
    m_SpongeBob->Start();
}

void KrustyKrab::WaitUntilTicketsEmpty()
{
    PrintLn("The Krusty Krab is about to close. Waiting for Patrick & SpongeBob to finish their tickets ...");
    {
        std::unique_lock<std::mutex> lock(m_TicketLineMutex);
        m_TicketCv.wait(lock, [this](){ return m_TicketLine->empty(); });
    }
    PrintLn("Patrick & SpongeBob have finished their tickets!");
}

void KrustyKrab::StopWorkers()
{
    m_Squidward->Stop();

    WaitUntilTicketsEmpty();

    m_Patrick->StopLoop();
    m_Patrick->WakeUp();
    m_Patrick->Stop();

    m_SpongeBob->StopLoop();
    m_SpongeBob->WakeUp();
    m_SpongeBob->Stop();

    m_Freezer->StopLoop();
    m_Freezer->WakeUp();
    m_Freezer->Stop();

    m_DeliveryTruck->Stop();
}

void KrustyKrab::PrintLn(const std::string &msg)
{
    std::cout << RED_ANSI_SEQ << msg << "\n" << RESET_ANSI_SEQ;
}

void KrustyKrab::PrintFinalStats() const
{
    const FrycookStats_t& spongebobStats = m_SpongeBob->WorkerStats();
    const FrycookStats_t& patrickStats = m_Patrick->WorkerStats();
    const RandomTicketStats_t ticketGeneratorStats = m_Squidward->TicketStats();
    const FreezerStats_t freezerStats = m_Freezer->FreezerStats();

    std::cout << std::endl;
    std::cout << "================================================================================\n";
    std::cout << "                            KRUSTY KRAB FINAL STATISTICS\n";
    std::cout << "================================================================================\n\n";

    // INGREDIENT STATS
    std::cout << "┌─ INGREDIENT INVENTORY ─────────────────────────────────────────────────────┐\n";
    std::cout << "│                                                                            │\n";

    // Header
    std::cout << "│ Ingredient          │ Initial │ Added   │ Taken   │ Remaining │ Calculated│\n";
    std::cout << "│─────────────────────┼─────────┼─────────┼─────────┼───────────┼───────────│\n";

    for (size_t i = 0; i < freezerStats.m_RemainingIngredientCts.size(); i++)
    {
        size_t calculatedRemaining = freezerStats.m_InitialIngredientCts[i] +
                                   freezerStats.m_AddedIngredientCts[i] -
                                   freezerStats.m_TakenIngredientCts[i];

        std::cout << "│ " << std::setw(19) << std::left << Menu::IngredientNames[i]
                  << " │ " << std::setw(7) << std::right << freezerStats.m_InitialIngredientCts[i]
                  << " │ " << std::setw(7) << std::right << freezerStats.m_AddedIngredientCts[i]
                  << " │ " << std::setw(7) << std::right << freezerStats.m_TakenIngredientCts[i]
                  << " │ " << std::setw(9) << std::right << freezerStats.m_RemainingIngredientCts[i]
                  << " │ " << std::setw(9) << std::right << calculatedRemaining << " │\n";
    }
    std::cout << "└────────────────────────────────────────────────────────────────────────────┘\n\n";

    // WORKER STATS
    std::cout << "┌─ FRYCOOK PERFORMANCE ──────────────────────────────────────────────────────┐\n";
    std::cout << "│                                                                            │\n";

    // SpongeBob Stats
    std::cout << "│ 🧽 SPONGEBOB SQUAREPANTS                                                   │\n";
    std::cout << "│   Tickets Completed: " << std::setw(3) << spongebobStats.m_TicketsCompleted << "                                                    │\n";
    std::cout << "│   Menu Items Prepared:                                                     │\n";

    for (const auto& item : spongebobStats.m_CompletedMenuItems) {
        std::cout << "│     • " << std::setw(25) << std::left << Menu::MenuItemNames[static_cast<size_t>(item.first)]
                  << ": " << std::setw(3) << std::right << item.second << " items                                    │\n";
    }

    std::cout << "│                                                                            │\n";

    // Patrick Stats
    std::cout << "│ ⭐ PATRICK STAR                                                            │\n";
    std::cout << "│   Tickets Completed: " << std::setw(3) << patrickStats.m_TicketsCompleted << "                                                    │\n";
    std::cout << "│   Menu Items Prepared:                                                     │\n";

    if (patrickStats.m_CompletedMenuItems.empty()) {
        std::cout << "│     • No items completed                                                   │\n";
    } else {
        for (const auto& item : patrickStats.m_CompletedMenuItems) {
            std::cout << "│     • " << std::setw(25) << std::left << Menu::MenuItemNames[static_cast<size_t>(item.first)]
                      << ": " << std::setw(3) << std::right << item.second << " items                                    │\n";
        }
    }

    std::cout << "└────────────────────────────────────────────────────────────────────────────┘\n\n";

    // TICKET GENERATOR STATS
    std::cout << "┌─ ORDER MANAGEMENT ─────────────────────────────────────────────────────────┐\n";
    std::cout << "│                                                                            │\n";
    std::cout << "│ 🦑 SQUIDWARD TENTACLES (Order Manager)                                    │\n";
    std::cout << "│   Total Tickets Generated: " << std::setw(3) << ticketGeneratorStats.m_TicketsGenerated << "                                          │\n";
    std::cout << "│   Menu Items Requested:                                                    │\n";

    for (const auto& item : ticketGeneratorStats.m_MenuItemsGenerated) {
        std::cout << "│     • " << std::setw(25) << std::left << Menu::MenuItemNames[static_cast<size_t>(item.first)]
                  << ": " << std::setw(3) << std::right << item.second << " orders                                   │\n";
    }

    std::cout << "└────────────────────────────────────────────────────────────────────────────┘\n\n";

    // SUMMARY STATS
    std::cout << "┌─ SUMMARY ──────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│                                                                            │\n";

    size_t totalTicketsCompleted = spongebobStats.m_TicketsCompleted + patrickStats.m_TicketsCompleted;
    size_t totalItemsCompleted = 0;
    for (const auto& item : spongebobStats.m_CompletedMenuItems) {
        totalItemsCompleted += item.second;
    }
    for (const auto& item : patrickStats.m_CompletedMenuItems) {
        totalItemsCompleted += item.second;
    }

    double completionRate = ticketGeneratorStats.m_TicketsGenerated > 0 ?
                           (static_cast<double>(totalTicketsCompleted) / ticketGeneratorStats.m_TicketsGenerated) * 100.0 : 0.0;

    std::cout << "│   Total Orders Generated:    " << std::setw(6) << ticketGeneratorStats.m_TicketsGenerated << "                                      │\n";
    std::cout << "│   Total Orders Completed:    " << std::setw(6) << totalTicketsCompleted << "                                      │\n";
    std::cout << "│   Total Items Prepared:      " << std::setw(6) << totalItemsCompleted << "                                      │\n";
    std::cout << "│   Completion Rate:           " << std::setw(5) << std::fixed << std::setprecision(1) << completionRate << "%                                     │\n";
    std::cout << "│                                                                            │\n";
    std::cout << "└────────────────────────────────────────────────────────────────────────────┘\n\n";

    std::cout << "================================================================================\n";
    std::cout << "                        \"I'm ready, I'm ready, I'm ready!\"\n";
    std::cout << "================================================================================\n";

}
