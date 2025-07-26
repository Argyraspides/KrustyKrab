//
// Created by gaugamela on 7/26/25.
//
#pragma once
#include "Worker.hpp"
#include <condition_variable>

class DeliveryTruck : Worker
{
public:
    DeliveryTruck();
    ~DeliveryTruck();

    void Work() override;

private:
    std::condition_variable m_IngredientCv;
    std::chrono::milliseconds m_NextDeliveryTime;

};