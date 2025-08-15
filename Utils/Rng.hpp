//
// Created by gaugamela on 8/15/25.
//

#pragma once
#include <random>

namespace Rng
{
static std::random_device m_RandomDevice;
static std::mt19937 m_MersenneTwister(m_RandomDevice());

static int RandomInt(int min = 0, int max = 100);
static int RandomInt(const int min, const int max)
{
    std::uniform_int_distribution<int> uid(min, max);
    return uid(m_MersenneTwister);
}

} // namespace Rng
