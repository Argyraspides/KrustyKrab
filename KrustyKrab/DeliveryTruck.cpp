//
// Created by gaugamela on 7/26/25.
//
#include "DeliveryTruck.hpp"
#include "IngredientRequest.hpp"
#include "Rng.hpp"
#include <iostream>

constexpr int MINIMUM_NEXT_DELIVERY_TIME_MS = 1;
constexpr int MAXIMUM_NEXT_DELIVERY_TIME_MS = 15;

DeliveryTruck::DeliveryTruck(Freezer& freezer)
    : m_Freezer(freezer),
      m_IngredientCv(std::condition_variable()),
      m_NextDeliveryTime(Rng::RandomInt(MINIMUM_NEXT_DELIVERY_TIME_MS, MAXIMUM_NEXT_DELIVERY_TIME_MS)),
      m_RandomDevice(std::random_device()),
      m_MerseneTwister(std::mt19937(m_RandomDevice())),
      m_MinRandomIngredients(1),
      m_MaxRandomIngredients(100),
      m_IngredientCtDist(std::uniform_int_distribution<size_t>(m_MinRandomIngredients, m_MaxRandomIngredients)),
      m_IngredientTypeDist(std::uniform_int_distribution<size_t>(
          static_cast<size_t>(Menu::EIngredient::Bun), static_cast<size_t>(Menu::EIngredient::INGREDIENT_COUNT) - 1)),
      m_DeliveredIngredients(std::array<size_t, static_cast<size_t>(Menu::EIngredient::INGREDIENT_COUNT)>())
{
}

DeliveryTruck::~DeliveryTruck()
{
    std::cout << "~DeliveryTruck()" << std::endl;
}

void DeliveryTruck::Work()
{
    while (m_Running)
    {
        m_NextDeliveryTime =
            std::chrono::milliseconds(Rng::RandomInt(MINIMUM_NEXT_DELIVERY_TIME_MS, MAXIMUM_NEXT_DELIVERY_TIME_MS));
        std::this_thread::sleep_for(m_NextDeliveryTime);

        size_t randomIngredientCt = m_IngredientCtDist(m_MerseneTwister);
        Menu::EIngredient randomIngredient = static_cast<Menu::EIngredient>(m_IngredientTypeDist(m_MerseneTwister));

        m_Freezer.AddIngredient(randomIngredient, randomIngredientCt);
        m_DeliveredIngredients[static_cast<size_t>(randomIngredient)] += randomIngredientCt;
    }
}
