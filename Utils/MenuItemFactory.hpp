//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "MenuItem_t.hpp"


namespace MenuItemFactory
{

    static const std::vector<EIngredient>& GetKrabbyPattyIngredients()
    {
        static const std::vector<EIngredient> krabbyPattyIngredients =
        {
            EIngredient::Bun,
            EIngredient::Patty,
            EIngredient::Lettuce,
            EIngredient::Cheese,
            EIngredient::Tomato,
            EIngredient::Onion,
            EIngredient::Pickles,
            EIngredient::Ketchup,
            EIngredient::Mustard
        };
        return krabbyPattyIngredients;
    }

    static const std::vector<size_t>& GetKrabbyPattyIngredientCounts()
    {
        static const std::vector<size_t> ingredientCounts =
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
        return ingredientCounts;
    }

    static const Menu::MenuItem_t& MakeKrabbyPatty()
    {
        static const Menu::MenuItem_t krabbyPatty
        {
            Menu::EMenuItem::KrabbyPatty,
            GetKrabbyPattyIngredients(),
            GetKrabbyPattyIngredientCounts()
        };

        return krabbyPatty;
    }
}