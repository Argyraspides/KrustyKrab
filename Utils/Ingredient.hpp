//
// Created by gaugamela on 7/19/25.
//
#pragma once

enum Ingredient {
    Bun = 0,
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

static const std::array<std::string, Ingredient::INGREDIENT_COUNT> IngredientNames =
{
    "Bun",
    "Patty",
    "Lettuce",
    "Cheese",
    "Tomato",
    "Onion",
    "Pickles",
    "Ketchup",
    "Mustard",
    "Oil",
    "Coral"
};

struct IngredientRequest
{
    std::condition_variable& m_IngredientCv;
    bool& m_RequestFulfilled;

    Ingredient m_Ingredient;
    size_t m_IngredientCount;
};
