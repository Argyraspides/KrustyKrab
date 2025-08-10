//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "ConcurrentQueue.hpp"
#include "EIngredient.hpp"
#include "Worker.hpp"
#include <functional>

struct FreezerStats_t
{
    std::vector<size_t> m_InitialIngredientCts      {};
    std::vector<size_t> m_AddedIngredientCts        {};
    std::vector<size_t> m_TakenIngredientCts        {};
    std::vector<size_t> m_RemainingIngredientCts    {};
};

class Freezer : public Worker
{

public:
    Freezer();
    ~Freezer();

    void RequestIngredient(const IngredientRequest_t& ingredientReq);
    void AddIngredient(EIngredient i, size_t ct);
    std::mutex& IngredientsMutex();
    void WakeUp();
    const FreezerStats_t& FreezerStats();

protected:
    void Work() override;

private:
    void InitDefaultIngredientCount();


private:
    std::vector<size_t> m_Ingredients;
    std::mutex m_IngredientsMutex;

    std::condition_variable m_IngredientsCv;

    std::queue<IngredientRequest_t> m_IngredientReqs;
    std::condition_variable m_RequestsCv;

    static constexpr size_t m_MaxIngredients = 100'000'000;

    FreezerStats_t m_FreezerStats;
};