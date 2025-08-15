//
// Created by gaugamela on 7/20/25.
//
#include "Freezer.hpp"
#include <iostream>

Freezer::Freezer()
    : m_Ingredients(std::vector<size_t>(static_cast<size_t>(Menu::EIngredient::INGREDIENT_COUNT))),
      m_IngredientsMutex(std::mutex()),
      m_IngredientsCv(std::condition_variable()),
      m_IngredientReqs(std::queue<IngredientRequest_t>()),
      m_RequestsCv(std::condition_variable()),
      m_FreezerStats(FreezerStats_t())
{
    InitDefaultIngredientCount();
}

Freezer::~Freezer()
{
    std::cout << "~Freezer()\n";
}

void Freezer::InitDefaultIngredientCount()
{
    std::unique_lock<std::mutex> lock(m_IngredientsMutex);

    for (size_t& ingredientCt : m_Ingredients)
    {
        constexpr size_t INIT_INGREDIENT_CT = 100;
        ingredientCt = INIT_INGREDIENT_CT;
    }

    m_FreezerStats.m_InitialIngredientCts = m_Ingredients;
    m_FreezerStats.m_AddedIngredientCts = std::vector<size_t>(static_cast<size_t>(Menu::EIngredient::INGREDIENT_COUNT));
    m_FreezerStats.m_TakenIngredientCts = std::vector<size_t>(static_cast<size_t>(Menu::EIngredient::INGREDIENT_COUNT));
}

void Freezer::RequestIngredient(const IngredientRequest_t& ingredientReq)
{
    std::unique_lock<std::mutex> lock(m_IngredientsMutex);
    m_IngredientReqs.push(ingredientReq);
    m_IngredientsCv.notify_all();
}

void Freezer::AddIngredient(Menu::EIngredient i, size_t count)
{
    std::unique_lock<std::mutex> lock(m_IngredientsMutex);

    size_t newVal = m_Ingredients[static_cast<size_t>(i)] + count;
    if (newVal > m_MaxIngredients)
        return;

    m_Ingredients[static_cast<size_t>(i)] = newVal;

    m_FreezerStats.m_AddedIngredientCts[static_cast<size_t>(i)] += count;
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
            m_IngredientsCv.wait(lock, [this]() { return !m_IngredientReqs.empty() || !m_Running; });

            // There might be more requests later in the queue we *can* fulfill, but
            // doing so might result in starvation. E.g., Patrick's always stealing the tomatoes
            // because he only ever needs 1, and SpongeBob needs 10, the delivery truck
            // only giving one tomato at a time ... SpongeBob will never get the tomatoes.

            if (m_IngredientReqs.empty())
                break;

            IngredientRequest_t& req = m_IngredientReqs.front();
            size_t ingredientIdx = static_cast<size_t>(req.m_Ingredient);
            if (m_Ingredients[ingredientIdx] >= req.m_IngredientCount)
            {
                m_IngredientReqs.pop();

                m_Ingredients[ingredientIdx] -= req.m_IngredientCount;
                m_FreezerStats.m_TakenIngredientCts[ingredientIdx] += req.m_IngredientCount;

                bool discrepancy = m_FreezerStats.m_InitialIngredientCts[ingredientIdx] +
                                       m_FreezerStats.m_AddedIngredientCts[ingredientIdx] -
                                       m_FreezerStats.m_TakenIngredientCts[ingredientIdx] !=
                                   m_Ingredients[ingredientIdx];

                req.m_RequestFulfilled = true;
                req.m_IngredientCv.notify_one();
            }
        }
    }
    m_FreezerStats.m_RemainingIngredientCts = m_Ingredients;

    for (size_t i = 0; i < m_FreezerStats.m_RemainingIngredientCts.size(); i++)
    {
        size_t calculatedRemaining = m_FreezerStats.m_InitialIngredientCts[i] + m_FreezerStats.m_AddedIngredientCts[i] -
                                     m_FreezerStats.m_TakenIngredientCts[i];

        int discrepancy =
            static_cast<int>(m_FreezerStats.m_RemainingIngredientCts[i]) - static_cast<int>(calculatedRemaining);

        int discrepancy2 = static_cast<int>(m_Ingredients[i]) - static_cast<int>(calculatedRemaining);

        int x = 5;
    }

    int x = 5;
}
