//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include "MenuItem_t.hpp"

namespace MenuItemFactory
{
// Original Krabby Patty
static const std::vector<Menu::EIngredient>& GetKrabbyPattyIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Bun,     Menu::EIngredient::Patty,   Menu::EIngredient::Lettuce,
        Menu::EIngredient::Cheese,  Menu::EIngredient::Tomato,  Menu::EIngredient::Onion,
        Menu::EIngredient::Pickles, Menu::EIngredient::Ketchup, Menu::EIngredient::Mustard};
    return ingredients;
}

static const std::vector<size_t>& GetKrabbyPattyIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 1, 1, 1, 1, 1, 1, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeKrabbyPatty()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::KrabbyPatty, GetKrabbyPattyIngredients(),
                                       GetKrabbyPattyIngredientCounts()};
    return item;
}

// Double Krabby Patty
static const std::vector<Menu::EIngredient>& GetDoubleKrabbyPattyIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Bun,     Menu::EIngredient::Patty,   Menu::EIngredient::Lettuce,
        Menu::EIngredient::Cheese,  Menu::EIngredient::Tomato,  Menu::EIngredient::Onion,
        Menu::EIngredient::Pickles, Menu::EIngredient::Ketchup, Menu::EIngredient::Mustard};
    return ingredients;
}

static const std::vector<size_t>& GetDoubleKrabbyPattyIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 2, 2, 2, 1, 1, 2, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeDoubleKrabbyPatty()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::DoubleKrabbyPatty, GetDoubleKrabbyPattyIngredients(),
                                       GetDoubleKrabbyPattyIngredientCounts()};
    return item;
}

// Triple Krabby Patty Supreme
static const std::vector<Menu::EIngredient>& GetTripleKrabbyPattySupremeIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Bun,     Menu::EIngredient::Patty,        Menu::EIngredient::Lettuce,
        Menu::EIngredient::Cheese,  Menu::EIngredient::Tomato,       Menu::EIngredient::Onion,
        Menu::EIngredient::Pickles, Menu::EIngredient::Ketchup,      Menu::EIngredient::Mustard,
        Menu::EIngredient::Mayo,    Menu::EIngredient::SecretFormula};
    return ingredients;
}

static const std::vector<size_t>& GetTripleKrabbyPattySupremeIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 3, 3, 3, 2, 2, 3, 2, 1, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeTripleKrabbyPattySupreme()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::TripleKrabbyPattySupreme,
                                       GetTripleKrabbyPattySupremeIngredients(),
                                       GetTripleKrabbyPattySupremeIngredientCounts()};
    return item;
}

// Krabby Patty Deluxe
static const std::vector<Menu::EIngredient>& GetKrabbyPattyDeluxeIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Bun,     Menu::EIngredient::Patty, Menu::EIngredient::Lettuce, Menu::EIngredient::Cheese,
        Menu::EIngredient::Tomato,  Menu::EIngredient::Onion, Menu::EIngredient::Pickles, Menu::EIngredient::Ketchup,
        Menu::EIngredient::Mustard, Menu::EIngredient::Mayo,  Menu::EIngredient::Relish};
    return ingredients;
}

static const std::vector<size_t>& GetKrabbyPattyDeluxeIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeKrabbyPattyDeluxe()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::KrabbyPattyDeluxe, GetKrabbyPattyDeluxeIngredients(),
                                       GetKrabbyPattyDeluxeIngredientCounts()};
    return item;
}

// Barnacle Burger
static const std::vector<Menu::EIngredient>& GetBarnacleBurgerIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Bun, Menu::EIngredient::BarnacleRings,
                                                               Menu::EIngredient::Lettuce,
                                                               Menu::EIngredient::TarTarSauce, Menu::EIngredient::Salt};
    return ingredients;
}

static const std::vector<size_t>& GetBarnacleBurgerIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 3, 1, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeBarnacleBurger()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::BarnacleBurger, GetBarnacleBurgerIngredients(),
                                       GetBarnacleBurgerIngredientCounts()};
    return item;
}

// Kelp Shake
static const std::vector<Menu::EIngredient>& GetKelpShakeIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Kelp, Menu::EIngredient::IceCream,
                                                               Menu::EIngredient::Vanilla};
    return ingredients;
}

static const std::vector<size_t>& GetKelpShakeIngredientCounts()
{
    static const std::vector<size_t> counts = {3, 2, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeKelpShake()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::KelpShake, GetKelpShakeIngredients(),
                                       GetKelpShakeIngredientCounts()};
    return item;
}

// Seaweed Salad
static const std::vector<Menu::EIngredient>& GetSeaweedSaladIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Seaweed, Menu::EIngredient::Kelp,
                                                               Menu::EIngredient::Tomato,  Menu::EIngredient::Onion,
                                                               Menu::EIngredient::Salt,    Menu::EIngredient::Pepper};
    return ingredients;
}

static const std::vector<size_t>& GetSeaweedSaladIngredientCounts()
{
    static const std::vector<size_t> counts = {3, 2, 1, 1, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeSeaweedSalad()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::SeaweedSalad, GetSeaweedSaladIngredients(),
                                       GetSeaweedSaladIngredientCounts()};
    return item;
}

// Barnacle Rings
static const std::vector<Menu::EIngredient>& GetBarnacleRingsIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::BarnacleRings,
                                                               Menu::EIngredient::Salt, Menu::EIngredient::TarTarSauce};
    return ingredients;
}

static const std::vector<size_t>& GetBarnacleRingsIngredientCounts()
{
    static const std::vector<size_t> counts = {6, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeBarnacleRings()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::BarnacleRings, GetBarnacleRingsIngredients(),
                                       GetBarnacleRingsIngredientCounts()};
    return item;
}

// Krusty Crab
static const std::vector<Menu::EIngredient>& GetKrustyCrabIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Kelp, Menu::EIngredient::Salt, Menu::EIngredient::Pepper, Menu::EIngredient::GoldenCrumbs};
    return ingredients;
}

static const std::vector<size_t>& GetKrustyCrabIngredientCounts()
{
    static const std::vector<size_t> counts = {1, 1, 1, 2};
    return counts;
}

static const Menu::MenuItem_t& MakeKrustyCrab()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::KrustyCrab, GetKrustyCrabIngredients(),
                                       GetKrustyCrabIngredientCounts()};
    return item;
}

// Plankton's Burger
static const std::vector<Menu::EIngredient>& GetPlanktonsBurgerIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Bun, Menu::EIngredient::Chum,
                                                               Menu::EIngredient::Ketchup};
    return ingredients;
}

static const std::vector<size_t>& GetPlanktonsBurgerIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakePlanktonsBurger()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::PlanktonsBurger, GetPlanktonsBurgerIngredients(),
                                       GetPlanktonsBurgerIngredientCounts()};
    return item;
}

// Chum Bucket
static const std::vector<Menu::EIngredient>& GetChumBucketIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Chum, Menu::EIngredient::Bun};
    return ingredients;
}

static const std::vector<size_t>& GetChumBucketIngredientCounts()
{
    static const std::vector<size_t> counts = {1, 2};
    return counts;
}

static const Menu::MenuItem_t& MakeChumBucket()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::ChumBucket, GetChumBucketIngredients(),
                                       GetChumBucketIngredientCounts()};
    return item;
}

// Golden Spatula
static const std::vector<Menu::EIngredient>& GetGoldenSpatulaIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Bun, Menu::EIngredient::Patty, Menu::EIngredient::GoldenCrumbs,
        Menu::EIngredient::SecretFormula, Menu::EIngredient::Cheese};
    return ingredients;
}

static const std::vector<size_t>& GetGoldenSpatulaIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 1, 3, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeGoldenSpatula()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::GoldenSpatula, GetGoldenSpatulaIngredients(),
                                       GetGoldenSpatulaIngredientCounts()};
    return item;
}

// Monster Krabby Patty
static const std::vector<Menu::EIngredient>& GetMonsterKrabbyPattyIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Bun,     Menu::EIngredient::Patty,   Menu::EIngredient::Lettuce,
        Menu::EIngredient::Cheese,  Menu::EIngredient::Tomato,  Menu::EIngredient::Onion,
        Menu::EIngredient::Pickles, Menu::EIngredient::Ketchup, Menu::EIngredient::Mustard,
        Menu::EIngredient::Mayo,    Menu::EIngredient::Relish,  Menu::EIngredient::SecretFormula};
    return ingredients;
}

static const std::vector<size_t>& GetMonsterKrabbyPattyIngredientCounts()
{
    static const std::vector<size_t> counts = {4, 6, 8, 8, 4, 4, 6, 3, 2, 2, 2, 2};
    return counts;
}

static const Menu::MenuItem_t& MakeMonsterKrabbyPatty()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::MonsterKrabbyPatty, GetMonsterKrabbyPattyIngredients(),
                                       GetMonsterKrabbyPattyIngredientCounts()};
    return item;
}

// Krabby Patty Pizza
static const std::vector<Menu::EIngredient>& GetKrabbyPattyPizzaIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {
        Menu::EIngredient::Bun, // Flattened as pizza base
        Menu::EIngredient::Patty,   Menu::EIngredient::Cheese,  Menu::EIngredient::Tomato,
        Menu::EIngredient::Ketchup, Menu::EIngredient::Pickles, Menu::EIngredient::SecretFormula};
    return ingredients;
}

static const std::vector<size_t>& GetKrabbyPattyPizzaIngredientCounts()
{
    static const std::vector<size_t> counts = {1, 1, 2, 2, 1, 3, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeKrabbyPattyPizza()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::KrabbyPattyPizza, GetKrabbyPattyPizzaIngredients(),
                                       GetKrabbyPattyPizzaIngredientCounts()};
    return item;
}

// Volcano Sauce
static const std::vector<Menu::EIngredient>& GetVolcanoSauceIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::VolcanoSauce};
    return ingredients;
}

static const std::vector<size_t>& GetVolcanoSauceIngredientCounts()
{
    static const std::vector<size_t> counts = {1};
    return counts;
}

static const Menu::MenuItem_t& MakeVolcanoSauce()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::VolcanoSauce, GetVolcanoSauceIngredients(),
                                       GetVolcanoSauceIngredientCounts()};
    return item;
}

// Jellyfish Jelly Sandwich
static const std::vector<Menu::EIngredient>& GetJellyfishJellyIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Bun,
                                                               Menu::EIngredient::JellyfishJelly};
    return ingredients;
}

static const std::vector<size_t>& GetJellyfishJellyIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 3};
    return counts;
}

static const Menu::MenuItem_t& MakeJellyfishJelly()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::JellyfishJelly, GetJellyfishJellyIngredients(),
                                       GetJellyfishJellyIngredientCounts()};
    return item;
}

// Gary Treat
static const std::vector<Menu::EIngredient>& GetGaryTreatIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::SnailTreats};
    return ingredients;
}

static const std::vector<size_t>& GetGaryTreatIngredientCounts()
{
    static const std::vector<size_t> counts = {5};
    return counts;
}

static const Menu::MenuItem_t& MakeGaryTreat()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::GaryTreat, GetGaryTreatIngredients(),
                                       GetGaryTreatIngredientCounts()};
    return item;
}

// Ice Cream Sundae
static const std::vector<Menu::EIngredient>& GetSundaeIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::IceCream,
                                                               Menu::EIngredient::Chocolate, Menu::EIngredient::Cherry,
                                                               Menu::EIngredient::Sprinkles};
    return ingredients;
}

static const std::vector<size_t>& GetSundaeIngredientCounts()
{
    static const std::vector<size_t> counts = {3, 1, 1, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeSundae()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::Sundae, GetSundaeIngredients(), GetSundaeIngredientCounts()};
    return item;
}

// Ice Cream
static const std::vector<Menu::EIngredient>& GetIceCreamIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::IceCream, Menu::EIngredient::Vanilla};
    return ingredients;
}

static const std::vector<size_t>& GetIceCreamIngredientCounts()
{
    static const std::vector<size_t> counts = {2, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeIceCream()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::IceCream, GetIceCreamIngredients(),
                                       GetIceCreamIngredientCounts()};
    return item;
}

// Chum Fritters
static const std::vector<Menu::EIngredient>& GetChumFrittersIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Chum, Menu::EIngredient::Salt};
    return ingredients;
}

static const std::vector<size_t>& GetChumFrittersIngredientCounts()
{
    static const std::vector<size_t> counts = {4, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeChumFritters()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::ChumFritters, GetChumFrittersIngredients(),
                                       GetChumFrittersIngredientCounts()};
    return item;
}

// Kelp Jerky
static const std::vector<Menu::EIngredient>& GetKelpJerkyIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Kelp, Menu::EIngredient::Salt,
                                                               Menu::EIngredient::Pepper};
    return ingredients;
}

static const std::vector<size_t>& GetKelpJerkyIngredientCounts()
{
    static const std::vector<size_t> counts = {5, 2, 1};
    return counts;
}

static const Menu::MenuItem_t& MakeKelpJerky()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::KelpJerky, GetKelpJerkyIngredients(),
                                       GetKelpJerkyIngredientCounts()};
    return item;
}

// Chum on a Stick
static const std::vector<Menu::EIngredient>& GetChumOnAStickIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::Chum};
    return ingredients;
}

static const std::vector<size_t>& GetChumOnAStickIngredientCounts()
{
    static const std::vector<size_t> counts = {1};
    return counts;
}

static const Menu::MenuItem_t& MakeChumOnAStick()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::ChumOnAStick, GetChumOnAStickIngredients(),
                                       GetChumOnAStickIngredientCounts()};
    return item;
}

// Tar Tar Sauce
static const std::vector<Menu::EIngredient>& GetTarTarSauceIngredients()
{
    static const std::vector<Menu::EIngredient> ingredients = {Menu::EIngredient::TarTarSauce};
    return ingredients;
}

static const std::vector<size_t>& GetTarTarSauceIngredientCounts()
{
    static const std::vector<size_t> counts = {1};
    return counts;
}

static const Menu::MenuItem_t& MakeTarTarSauce()
{
    static const Menu::MenuItem_t item{Menu::EMenuItem::TarTarSauce, GetTarTarSauceIngredients(),
                                       GetTarTarSauceIngredientCounts()};
    return item;
}

static const Menu::MenuItem_t& CreateMenuItem(Menu::EMenuItem itemType)
{
    switch (itemType)
    {
    case Menu::EMenuItem::KrabbyPatty:
        return MakeKrabbyPatty();
    case Menu::EMenuItem::DoubleKrabbyPatty:
        return MakeDoubleKrabbyPatty();
    case Menu::EMenuItem::TripleKrabbyPattySupreme:
        return MakeTripleKrabbyPattySupreme();
    case Menu::EMenuItem::KrabbyPattyDeluxe:
        return MakeKrabbyPattyDeluxe();
    case Menu::EMenuItem::BarnacleBurger:
        return MakeBarnacleBurger();
    case Menu::EMenuItem::KelpShake:
        return MakeKelpShake();
    case Menu::EMenuItem::SeaweedSalad:
        return MakeSeaweedSalad();
    case Menu::EMenuItem::BarnacleRings:
        return MakeBarnacleRings();
    case Menu::EMenuItem::KrustyCrab:
        return MakeKrustyCrab();
    case Menu::EMenuItem::PlanktonsBurger:
        return MakePlanktonsBurger();
    case Menu::EMenuItem::ChumBucket:
        return MakeChumBucket();
    case Menu::EMenuItem::GoldenSpatula:
        return MakeGoldenSpatula();
    case Menu::EMenuItem::MonsterKrabbyPatty:
        return MakeMonsterKrabbyPatty();
    case Menu::EMenuItem::KrabbyPattyPizza:
        return MakeKrabbyPattyPizza();
    case Menu::EMenuItem::VolcanoSauce:
        return MakeVolcanoSauce();
    case Menu::EMenuItem::JellyfishJelly:
        return MakeJellyfishJelly();
    case Menu::EMenuItem::GaryTreat:
        return MakeGaryTreat();
    case Menu::EMenuItem::Sundae:
        return MakeSundae();
    case Menu::EMenuItem::IceCream:
        return MakeIceCream();
    case Menu::EMenuItem::ChumFritters:
        return MakeChumFritters();
    case Menu::EMenuItem::KelpJerky:
        return MakeKelpJerky();
    case Menu::EMenuItem::ChumOnAStick:
        return MakeChumOnAStick();
    case Menu::EMenuItem::TarTarSauce:
        return MakeTarTarSauce();
    default:
        return MakeKrabbyPatty();
    }
}
} // namespace MenuItemFactory