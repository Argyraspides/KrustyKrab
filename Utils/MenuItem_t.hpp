//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <vector>
#include <cstdint>
#include "Ingredient.hpp"

namespace Menu
{
    enum class EMenuItem
    {
        KrabbyPatty,
    };

    static const std::array<EMenuItem, 1> MenuItems =
    {
        EMenuItem::KrabbyPatty,
    };

    static const size_t TotalMenuItems()
    {
        return MenuItems.size();
    }

    struct MenuItem_t final {

        Menu::EMenuItem m_MenuItemName;
        std::vector<Ingredient> m_Ingredients;
        std::vector<size_t> m_IngredientCounts;
    };
}


