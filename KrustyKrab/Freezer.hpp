//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "ConcurrentStack.hpp"
#include "Ingredient.hpp"

class Freezer
{

public:
    Freezer() = default;
    ~Freezer() = default;

public:
    ConcurrentStack<Ingredient> m_Buns;
    ConcurrentStack<Ingredient> m_Patties;
    ConcurrentStack<Ingredient> m_Lettuce;
    ConcurrentStack<Ingredient> m_Cheeses;
    ConcurrentStack<Ingredient> m_Tomatoes;
    ConcurrentStack<Ingredient> m_Onions;
    ConcurrentStack<Ingredient> m_Pickles;
    ConcurrentStack<Ingredient> m_Ketchup;
    ConcurrentStack<Ingredient> m_Mustard;

};