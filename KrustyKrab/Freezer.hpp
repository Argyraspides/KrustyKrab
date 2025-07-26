//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "ConcurrentQueue.hpp"
#include "Ingredient.hpp"
#include "Worker.hpp"
#include <functional>

class Freezer : Worker
{

public:
    Freezer(std::condition_variable& ingredientAvailCv);
    ~Freezer() = default;

    void RequestIngredient(IngredientRequest ingredientReq);
    void AddIngredient(Ingredient i, size_t count);

private:
    void CheckRequests();
    void InitDefaultIngredientCount();


private:
    std::vector<size_t> m_Ingredients;

    std::condition_variable& m_IngredientAvailCv;

    std::queue<IngredientRequest> m_IngredientReqs;
    std::mutex m_IngredientsMutex;
};