#pragma once
#include "Freezer.hpp"
#include "Ticket.hpp"
#include "Worker.hpp"
#include <iostream>
#include <memory>

struct FrycookStats_t
{
    unsigned long long int m_TicketsCompleted;
    std::unordered_map<Menu::EMenuItem, size_t> m_CompletedMenuItems;
};

class SpongeBob : public Worker
{

  public:
    SpongeBob(std::queue<Ticket>& ticketLine,
              std::mutex& ticketLineMutex,
              std::condition_variable& ticketCv,
              Freezer& freezer,
              bool IsActuallyPatrick = false);
    ~SpongeBob() override;
    void PrintLn(const std::string& str) const;
    void WakeUp();
    const FrycookStats_t& WorkerStats() const;

  protected:
    void Work() override;

  private:
    // I'm sorry, Patrick ...
    std::string WhoAmI() const;
    void PrepareOrder(const Ticket& ticket);
    Ticket TryGetTicket() const;
    void GetIngredients(const std::vector<Menu::EIngredient>& ingredients, const std::vector<size_t>& ingredientCount);

  private:
    std::queue<Ticket>& m_TicketLine;
    std::mutex& m_TicketLineMutex;
    std::condition_variable& m_TicketCv;
    std::chrono::milliseconds m_RestTimeMs;

    Freezer& m_Freezer;
    std::condition_variable m_IngredientsCv;

    // I'M SORRY, PATRICK!
    bool m_IsActuallyPatrick;

    FrycookStats_t m_FrycookStats;
};