//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "MenuItem.hpp"


namespace MenuItemFactory
{

    static const std::vector<Ingredient>& GetKrabbyPattyIngredients()
    {
        static const std::vector<Ingredient> krabbyPattyIngredients =
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

    static const MenuItem& MakeKrabbyPatty()
    {
        static const MenuItem krabbyPatty
        {
            MenuItems::KrabbyPatty,
            GetKrabbyPattyIngredients(),
            GetKrabbyPattyIngredientCounts()
        };

        return krabbyPatty;
    }

    static MenuItem MakeCoralBits()
    {
        std::vector<Ingredient> ingredients =
        {
            Ingredient::Coral,
            Ingredient::Oil
        };

        std::vector<size_t> ingredientCounts =
        {
            1,
            1
        };

        // TODO: Big copy. Try to avoid.
        return MenuItem { MenuItems::CoralBits, ingredients, ingredientCounts };
    }

}