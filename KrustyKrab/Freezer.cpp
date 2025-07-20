//
// Created by gaugamela on 7/20/25.
//
#include "Freezer.hpp"

Freezer::Freezer() :
    m_Buns(0),
    m_Patties(0),
    m_Lettuce(0),
    m_Cheeses(0),
    m_Tomatoes(0),
    m_Onions(0),
    m_Pickles(0),
    m_Ketchup(0),
    m_Mustard(0),
    m_IngredientOrderCallbacks(ConcurrentQueue<std::function<void()>>())
{
}

void Freezer::RequestIngredients(Ingredient i, size_t count)
{

}

void Freezer::AddIngredient(Ingredient i, size_t count)
{

}