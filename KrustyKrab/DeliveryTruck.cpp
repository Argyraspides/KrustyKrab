//
// Created by gaugamela on 7/26/25.
//
#include "DeliveryTruck.hpp"

DeliveryTruck::DeliveryTruck() :
m_IngredientCv(std::condition_variable()),
m_NextDeliveryTime(std::chrono::milliseconds(250))
{
}

DeliveryTruck::~DeliveryTruck() {
}

void DeliveryTruck::Work()
{
    while (m_Running)
    {
        std::this_thread::sleep_for(m_NextDeliveryTime);

    }
}
