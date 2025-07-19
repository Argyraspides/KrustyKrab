//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "MenuItem.hpp"


namespace MenuItemFactory
{
    static MenuItem MakeKrabbyPatty() {
        std::vector< Ingredient > ingredients =
        {
            Ingredient::Bun,
            Ingredient::Patty,
            Ingredient::Lettuce,
            Ingredient::Cheese,
            Ingredient::Tomato,
            Ingredient::Onion,
            Ingredient::Pickles,
            Ingredient::Ketchup,
            Ingredient::Mustard
        };

        std::vector<size_t> ingredientCounts =
        {
            2,
            1,
            1,
            1,
            1,
            1,
            1,
            1
        };

        // TODO: Big copy. Try to avoid.
        return MenuItem { MenuItems::KrabbyPatty, ingredients, ingredientCounts };
    }

}