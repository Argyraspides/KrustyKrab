//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <array>
#include <string>
#include <condition_variable>

enum EIngredient {
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

static const std::array<std::string, EIngredient::INGREDIENT_COUNT> IngredientNames =
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

struct IngredientRequest_t
{
    std::condition_variable& m_IngredientCv;
    bool& m_RequestFulfilled;

    EIngredient m_Ingredient;
    size_t m_IngredientCount;
};
