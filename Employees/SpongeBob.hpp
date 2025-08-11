#pragma once
#include <iostream>
#include <memory>
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
    std::string WhoAmI() const;
    void PrepareOrder(const Ticket& ticket);
    Ticket TryGetTicket() const;
    void GetIngredients(const std::vector<Menu::EIngredient>& ingredients, const std::vector<size_t>& ingredientCount);


private:
    // Original Krabby Patty variations
    void MakeKrabbyPatty();
    void MakeDoubleKrabbyPatty();
    void MakeTripleKrabbyPattySupreme();
    void MakeKrabbyPattyDeluxe();
    void MakeMonsterKrabbyPatty();
    void MakeKrabbyPattyPizza();

    // Other burgers
    void MakeBarnacleBurger();
    void MakePlanktonsBurger();
    void MakeChumBucket();
    void MakeGoldenSpatula();

    // Beverages
    void MakeKelpShake();

    // Sides and salads
    void MakeSeaweedSalad();
    void MakeBarnacleRings();
    void MakeKrustyCrab();

    // Sauces and condiments
    void MakeVolcanoSauce();
    void MakeTarTarSauce();

    // Desserts
    void MakeSundae();
    void MakeIceCream();

    // Specialty items
    void MakeJellyfishJelly();
    void MakeGaryTreat();

    // Chum-based items
    void MakeChumFritters();
    void MakeChumOnAStick();

    // Snacks
    void MakeKelpJerky();

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