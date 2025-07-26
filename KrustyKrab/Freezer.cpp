//
// Created by gaugamela on 7/20/25.
//
#include "Freezer.hpp"

Freezer::Freezer(std::condition_variable& ingredientAvailCv) :
    m_Ingredients(std::vector<size_t>(Ingredient::INGREDIENT_COUNT)),
    m_IngredientAvailCv(ingredientAvailCv), // Given by delivery truck
    m_IngredientReqs(std::queue<IngredientRequest>()),
    m_IngredientsMutex(std::mutex())
{
    InitDefaultIngredientCount();
}

void Freezer::CheckRequests()
{

    while (m_Running)
    {

        std::unique_lock<std::mutex> lock(m_IngredientsMutex);
        m_IngredientAvailCv.wait(lock, [this](){ return !m_IngredientReqs.empty() || !m_Running; });

        // There might be more requests later in the queue we *can* fulfill, but
        // doing so might result in starvation. E.g., Patrick's always stealing the tomatoes
        // because he only ever needs 1, and SpongeBob needs 10, the delivery truck
        // only giving one tomato at a time ... SpongeBob will never get the tomatoes.

        IngredientRequest& req = m_IngredientReqs.front();

        if (m_Ingredients[req.m_Ingredient - 1] >= req.m_IngredientCount)
        {
            m_IngredientReqs.pop();
            m_Ingredients[req.m_Ingredient - 1] -= req.m_IngredientCount;
            req.m_IngredientCv.notify_one();
        }

    }

}

void Freezer::InitDefaultIngredientCount() {

    std::unique_lock<std::mutex> lock(m_IngredientsMutex);

    for (size_t &ingredientCt : m_Ingredients)
    {
        constexpr size_t INIT_INGREDIENT_CT = 100;
        ingredientCt = INIT_INGREDIENT_CT;
    }

}

void Freezer::RequestIngredient(IngredientRequest ingredientReq)
{
    std::unique_lock<std::mutex> lock(m_IngredientsMutex);
    m_IngredientReqs.push(ingredientReq);
}

void Freezer::AddIngredient(Ingredient i, size_t count)
{
    std::unique_lock<std::mutex> lock(m_IngredientsMutex);
    m_Ingredients[i - 1] += count;
}