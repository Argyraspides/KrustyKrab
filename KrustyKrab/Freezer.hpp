//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "ConcurrentQueue.hpp"
#include "Ingredient.hpp"
#include "Worker.hpp"
#include <functional>

class Freezer : public Worker
{

public:
    Freezer();
    ~Freezer();

    void RequestIngredient(const IngredientRequest& ingredientReq);
    void AddIngredient(Ingredient i, size_t ct);
    void AddIngredients(const std::vector<Ingredient>& is, const std::vector<size_t>& cts);
    std::mutex& IngredientsMutex();
    void WakeUp();
    void WaitUntilReqsEmpty();

protected:
    void Work() override;

private:
    void InitDefaultIngredientCount();


private:
    std::vector<size_t> m_Ingredients;
    std::mutex m_IngredientsMutex;

    std::condition_variable m_IngredientsCv;

    std::queue<IngredientRequest> m_IngredientReqs;
    std::condition_variable m_RequestsCv;

    static constexpr size_t m_MaxIngredients = 100'000'000;
};