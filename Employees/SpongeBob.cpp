//
// Created by gaugamela on 7/18/25.
//

#include "SpongeBob.hpp"
#include "MenuItemFactory.hpp"

const std::string YELLOW_ANSI_SEQ = "\033[93m";
const std::string PINK_ANSI_SEQ = "\033[0;95m";
const std::string RESET_ANSI_SEQ = "\033[0m";

SpongeBob::SpongeBob(
    std::weak_ptr<std::queue<Ticket> > ticketLine,
    std::mutex &ticketLineMutex,
    std::condition_variable &ticketCv,
    std::weak_ptr<Freezer> freezer,
    bool IsActuallyPatrick) : m_TicketLine(std::move(ticketLine)),
                              m_TicketLineMutex(ticketLineMutex),
                              m_TicketCv(ticketCv),
                              m_RestTimeMs(std::chrono::milliseconds(500)),
                              m_Freezer(std::move(freezer)),
                              m_IngredientsCv(std::condition_variable()),
                              m_IsActuallyPatrick(IsActuallyPatrick),
                              m_FrycookStats(FrycookStats_t()) {
    PrintLn(WhoAmI() + "()");
}

SpongeBob::~SpongeBob() {
    PrintLn("~" + WhoAmI() + "()");
}

void SpongeBob::PrintLn(const std::string &str) const {
    std::cout << ((m_IsActuallyPatrick ? PINK_ANSI_SEQ : YELLOW_ANSI_SEQ) + str + "\n" + RESET_ANSI_SEQ);
}

void SpongeBob::WakeUp() {
    m_TicketCv.notify_all();
    m_IngredientsCv.notify_all();
}

const FrycookStats_t &SpongeBob::WorkerStats() const {
    return m_FrycookStats;
}

void SpongeBob::Work() {
    while (m_Running) {
        std::this_thread::sleep_for(m_RestTimeMs);
        Ticket nextTicket = TryGetTicket();

        if (nextTicket.m_MenuItems.empty()) {
            continue;
        }

        PrepareOrder(nextTicket);
    }
}

void SpongeBob::PrepareOrder(const Ticket &ticket) {
    for (auto &menuItem: ticket.m_MenuItems) {
        // Just assume that by getting the ingredients, SpongeBob has finished the order lol
        //  TODO: Maybe add an assembly time delay in future?
        GetIngredients(menuItem.m_Ingredients, menuItem.m_IngredientCounts);
        m_FrycookStats.m_CompletedMenuItems[menuItem.m_MenuItemName]++;
    }
    m_FrycookStats.m_TicketsCompleted++;
}

Ticket SpongeBob::TryGetTicket() const {
    Ticket finalTicket = {};

    std::shared_ptr<std::queue<Ticket> > ticketLine = m_TicketLine.lock();
    if (!ticketLine) {
        return finalTicket;
    }

    bool nowEmpty = false;
    {
        std::unique_lock<std::mutex> lock(m_TicketLineMutex);
        m_TicketCv.wait(lock, [&]() { return !ticketLine->empty() || !m_Running; });

        if (!ticketLine->empty()) {
            finalTicket = ticketLine->front();
            ticketLine->pop();
            nowEmpty = ticketLine->empty();
        }
    }

    // To notify the krusty krab that the tickets are now empty.
    // Idk why but I don't like this. Why should spongebob give a shit about notifying the krusty krab?
    if (nowEmpty) m_TicketCv.notify_all();

    return finalTicket;
}

void SpongeBob::GetIngredients(const std::vector<Menu::EIngredient> &ingredients,
                               const std::vector<size_t> &ingredientCount) {
    for (int i = 0; i < ingredients.size(); i++) {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir{m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i]};
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());

        // TODO GAUGAMELA() { If the krusty krab closes, and so the delivery truck stops, if we do not have enough ingredients for the final orders,
        // we will be waiting here forever .... since the krusty krab waits for all tickets to be finished first }
        m_IngredientsCv.wait(lock, [&]() { return requestFulfilled || !m_Running; });
    }
}

std::string SpongeBob::WhoAmI() const {
    return m_IsActuallyPatrick ? "Patrick" : "Spongebob";
}

