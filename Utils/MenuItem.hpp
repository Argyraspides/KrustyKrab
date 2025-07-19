//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <vector>
#include <cstdint>
#include "Ingredient.hpp"

namespace MenuItemName
{
    static const std::string KrabbyPatty = "Krabby Patty";
}

struct MenuItem final {
    std::string m_MenuItemName;
    std::vector< Ingredient > m_Ingredients;
    std::vector< uint32_t > m_IngredientCounts;
};
