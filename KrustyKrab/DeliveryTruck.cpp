//
// Created by gaugamela on 7/26/25.
//
#include "DeliveryTruck.hpp"
#include "Ingredient.hpp"

DeliveryTruck::DeliveryTruck(std::weak_ptr<Freezer> freezer) :
m_Freezer(std::move(freezer)),
m_IngredientCv(std::condition_variable()),
m_NextDeliveryTime(std::chrono::milliseconds(1000)),
m_RandomDevice(std::random_device()),
m_MerseneTwister(std::mt19937(m_RandomDevice())),
m_MinRandomIngredients(1),
m_MaxRandomIngredients(100),
m_IngredientCtDist(std::uniform_int_distribution<size_t>(m_MinRandomIngredients, m_MaxRandomIngredients)),
m_IngredientTypeDist(std::uniform_int_distribution<size_t>(Ingredient::Bun, Ingredient::INGREDIENT_COUNT - 1))
{
}

DeliveryTruck::~DeliveryTruck()
{
}

void DeliveryTruck::Work()
{
    while (m_Running)
    {
        std::this_thread::sleep_for(m_NextDeliveryTime);
        // get random ingredient count
        size_t randomIngredientCt = m_IngredientCtDist(m_MerseneTwister);
        Ingredient randomIngredient = static_cast<Ingredient>(m_IngredientTypeDist(m_MerseneTwister));

        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) continue;

        freezer->AddIngredient(randomIngredient, randomIngredientCt);
    }
}
