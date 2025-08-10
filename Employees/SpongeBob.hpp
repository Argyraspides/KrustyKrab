#pragma once
#include <iostream>
#include <memory>
#include "ConcurrentQueue.hpp"
#include "Worker.hpp"
#include "Ticket.hpp"
#include "Freezer.hpp"

struct FrycookStats_t
{
    unsigned long long int m_TicketsCompleted;
    std::unordered_map<Menu::EMenuItem, size_t> m_CompletedMenuItems;
};

class SpongeBob : public Worker
{

public:
    SpongeBob(
            std::weak_ptr<std::queue<Ticket>> ticketLine,
            std::mutex& ticketLineMutex,
            std::condition_variable& ticketCv,
            std::weak_ptr<Freezer> freezer,
            bool IsActuallyPatrick = false
        );
    ~SpongeBob() override;
    void PrintLn(const std::string& str) const;
    void WakeUp();
    const FrycookStats_t& WorkerStats() const;

protected:
    void Work() override;

private:
    // I'm sorry, Patrick ...
    [[nodiscard]] std::string WhoAmI() const;
    void PrepareOrder(const Ticket& ticket);
    void MakeKrabbyPatty();
    [[nodiscard]] Ticket TryGetTicket() const;
    void PrintStatistics() const;

private:
    std::weak_ptr<std::queue<Ticket>> m_TicketLine;
    std::mutex& m_TicketLineMutex;
    std::condition_variable& m_TicketCv;
    std::chrono::milliseconds m_RestTimeMs;

    std::weak_ptr<Freezer> m_Freezer;
    std::condition_variable m_IngredientsCv;

    // I'M SORRY, PATRICK!
    bool m_IsActuallyPatrick;

    FrycookStats_t m_FrycookStats;

};