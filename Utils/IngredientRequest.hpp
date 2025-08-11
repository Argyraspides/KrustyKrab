//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <array>
#include <string>
#include <condition_variable>
#include "MenuItem_t.hpp"

struct IngredientRequest_t
{
    std::condition_variable& m_IngredientCv;
    bool& m_RequestFulfilled;

    Menu::EIngredient m_Ingredient;
    size_t m_IngredientCount;
};
