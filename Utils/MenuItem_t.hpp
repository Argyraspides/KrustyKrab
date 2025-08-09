//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <vector>
#include <cstdint>
#include "EIngredient.hpp"

namespace Menu
{
    enum EMenuItem
    {
        KrabbyPatty,
        MENU_ITEM_COUNT
    };

    static const std::array<std::string, EMenuItem::MENU_ITEM_COUNT> MenuItemNames =
    {
        "Krabby Patty"
    };

    struct MenuItem_t final
    {
        Menu::EMenuItem m_MenuItemName;
        std::vector<EIngredient> m_Ingredients;
        std::vector<size_t> m_IngredientCounts;
    };
}


