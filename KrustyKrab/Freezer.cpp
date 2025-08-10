//
// Created by gaugamela on 7/20/25.
//
#include "Freezer.hpp"
#include <exception>
Freezer::Freezer() :
    m_Ingredients       (std::vector<size_t>(EIngredient::INGREDIENT_COUNT)),
    m_IngredientsMutex  (std::mutex()),
    m_IngredientsCv     (std::condition_variable()),
    m_IngredientReqs    (std::queue<IngredientRequest_t>()),
    m_RequestsCv        (std::condition_variable()),
    m_FreezerStats      (FreezerStats_t())
{
    InitDefaultIngredientCount();
}

Freezer::~Freezer()
{
    std::cout << "~Freezer()\n";
}

void Freezer::InitDefaultIngredientCount() {

    std::unique_lock<std::mutex> lock(m_IngredientsMutex);

    for (size_t &ingredientCt : m_Ingredients)
    {
        constexpr size_t INIT_INGREDIENT_CT = 100;
        ingredientCt = INIT_INGREDIENT_CT;
    }

    m_FreezerStats.m_InitialIngredientCts = m_Ingredients;
    m_FreezerStats.m_AddedIngredientCts = std::vector<size_t>(EIngredient::INGREDIENT_COUNT);
    m_FreezerStats.m_TakenIngredientCts = std::vector<size_t>(EIngredient::INGREDIENT_COUNT);
}

void Freezer::RequestIngredient(const IngredientRequest_t& ingredientReq)
{
    std::unique_lock<std::mutex> lock(m_IngredientsMutex);
    m_IngredientReqs.push(ingredientReq);
    m_IngredientsCv.notify_all();
}

void Freezer::AddIngredient(EIngredient i, size_t count)
{
    std::unique_lock<std::mutex> lock(m_IngredientsMutex);

    size_t newVal = m_Ingredients[i] + count;
    if (newVal > m_MaxIngredients) return;

    m_Ingredients[i] = newVal;

    m_FreezerStats.m_AddedIngredientCts[i] += count;
}

std::mutex& Freezer::IngredientsMutex()
{
    return m_IngredientsMutex;
}

void Freezer::WakeUp()
{
    m_IngredientsCv.notify_all();
}

const FreezerStats_t& Freezer::FreezerStats()
{
    return m_FreezerStats;
}

// TODO: Current basically a busy wait despite condition variable. If a request cannot be fulfilled,
//  we don't pop from queue, thus queue is not empty and the while loop continues like a normal loop.
void Freezer::Work()
{
    while (m_Running)
    {
        {
            std::unique_lock<std::mutex> lock(m_IngredientsMutex);
            m_IngredientsCv.wait(lock, [this](){ return !m_IngredientReqs.empty() || !m_Running; });

            // There might be more requests later in the queue we *can* fulfill, but
            // doing so might result in starvation. E.g., Patrick's always stealing the tomatoes
            // because he only ever needs 1, and SpongeBob needs 10, the delivery truck
            // only giving one tomato at a time ... SpongeBob will never get the tomatoes.

            if (m_IngredientReqs.empty()) break;

            IngredientRequest_t& req = m_IngredientReqs.front();
            if (m_Ingredients[req.m_Ingredient] >= req.m_IngredientCount)
            {
                m_IngredientReqs.pop();

                m_Ingredients[req.m_Ingredient] -= req.m_IngredientCount;
                m_FreezerStats.m_TakenIngredientCts[req.m_Ingredient] += req.m_IngredientCount;

                req.m_RequestFulfilled = true;
                req.m_IngredientCv.notify_one();
            }
        }
    }

    m_FreezerStats.m_RemainingIngredientCts = m_Ingredients;
}
