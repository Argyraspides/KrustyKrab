//
// Created by gaugamela on 7/26/25.
//
#pragma once
#include "Worker.hpp"
#include "Freezer.hpp"
#include <condition_variable>
#include <random>

class DeliveryTruck : public Worker
{
public:
    DeliveryTruck(std::weak_ptr<Freezer> freezer);
    ~DeliveryTruck();

    void Work() override;

private:

    std::weak_ptr<Freezer> m_Freezer;

    std::condition_variable m_IngredientCv;
    std::chrono::milliseconds m_NextDeliveryTime;

    std::random_device m_RandomDevice;
    std::mt19937 m_MerseneTwister;
    const size_t m_MinRandomIngredients;
    const size_t m_MaxRandomIngredients;
    std::uniform_int_distribution<size_t> m_IngredientCtDist;
    std::uniform_int_distribution<size_t> m_IngredientTypeDist;

    std::array<size_t, Ingredient::INGREDIENT_COUNT> m_DeliveredIngredients;

};