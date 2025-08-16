//
// Created by gaugamela on 7/26/25.
//
#pragma once
#include "Freezer.hpp"
#include "Worker.hpp"
#include <condition_variable>
#include <random>

class DeliveryTruck : public Worker
{
  public:
    DeliveryTruck(Freezer& freezer);
    ~DeliveryTruck() override;

    void Work() override;

  private:
    Freezer& m_Freezer;

    std::condition_variable m_IngredientCv;
    std::chrono::milliseconds m_NextDeliveryTime;

    std::random_device m_RandomDevice;
    std::mt19937 m_MerseneTwister;
    const size_t m_MinRandomIngredients;
    const size_t m_MaxRandomIngredients;
    std::uniform_int_distribution<size_t> m_IngredientCtDist;
    std::uniform_int_distribution<size_t> m_IngredientTypeDist;

    std::array<size_t, static_cast<size_t>(Menu::EIngredient::INGREDIENT_COUNT)> m_DeliveredIngredients;
};