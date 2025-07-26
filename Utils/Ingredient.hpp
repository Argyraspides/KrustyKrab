//
// Created by gaugamela on 7/19/25.
//
#pragma once

enum Ingredient {
    Bun,
    Patty,
    Lettuce,
    Cheese,
    Tomato,
    Onion,
    Pickles,
    Ketchup,
    Mustard,
    Oil,
    Coral,
    INGREDIENT_COUNT
};

struct IngredientRequest
{
    std::condition_variable& m_IngredientCv;
    Ingredient m_Ingredient;
    size_t m_IngredientCount;
};
