//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "ConcurrentQueue.hpp"
#include "Ingredient.hpp"
#include <functional>

class Freezer
{

public:
    Freezer();
    ~Freezer() = default;

    void RequestIngredients(Ingredient i, size_t count);
    void AddIngredient(Ingredient i, size_t count);

private:
    size_t m_Buns;
    size_t m_Patties;
    size_t m_Lettuce;
    size_t m_Cheeses;
    size_t m_Tomatoes;
    size_t m_Onions;
    size_t m_Pickles;
    size_t m_Ketchup;
    size_t m_Mustard;

    ConcurrentQueue<std::function<void()>> m_IngredientOrderCallbacks;
};