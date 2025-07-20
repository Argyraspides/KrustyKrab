//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <vector>
#include <cstdint>
#include "Ingredient.hpp"

namespace MenuItems
{
    static const std::string KrabbyPatty = "Krabby Patty";
    static const std::string CoralBits = "Coral Bits";
    static const std::array<std::string, 2> MenuItems =
    {
        KrabbyPatty,
        CoralBits
    };

    static const size_t TotalMenuItems()
    {
        return MenuItems.size();
    }
}

struct MenuItem final {
    std::string m_MenuItemName;
    std::vector<Ingredient> m_Ingredients;
    std::vector<size_t> m_IngredientCounts;
};
