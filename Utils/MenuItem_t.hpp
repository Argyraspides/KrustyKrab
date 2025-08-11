//
// Created by gaugamela on 7/19/25.
//
#pragma once
#include <vector>
#include <cstdint>
#include <array>
#include <string>

namespace Menu
{
    enum class EMenuItem
    {
        KrabbyPatty,
        DoubleKrabbyPatty,
        TripleKrabbyPattySupreme,
        KrabbyPattyDeluxe,
        BarnacleBurger,
        KelpShake,
        SeaweedSalad,
        BarnacleRings,
        KrustyCrab,
        PlanktonsBurger,
        ChumBucket,
        GoldenSpatula,
        MonsterKrabbyPatty,
        KrabbyPattyPizza,
        VolcanoSauce,
        JellyfishJelly,
        GaryTreat,
        Sundae,
        IceCream,
        ChumFritters,
        KelpJerky,
        ChumOnAStick,
        TarTarSauce,
        MENU_ITEM_COUNT
    };

    static const std::array<std::string, static_cast<size_t>(EMenuItem::MENU_ITEM_COUNT)> MenuItemNames =
    {
        "Krabby Patty",
        "Double Krabby Patty",
        "Triple Krabby Patty Supreme",
        "Krabby Patty Deluxe",
        "Barnacle Burger",
        "Kelp Shake",
        "Seaweed Salad",
        "Barnacle Rings",
        "Krusty Crab",
        "Plankton's Burger",
        "Chum Bucket",
        "Golden Spatula",
        "Monster Krabby Patty",
        "Krabby Patty Pizza",
        "Volcano Sauce",
        "Jellyfish Jelly",
        "Gary Treat",
        "Sundae",
        "Ice Cream",
        "Chum Fritters",
        "Kelp Jerky",
        "Chum on a Stick",
        "Tar Tar Sauce"
    };

    enum class EIngredient
    {
        Bun,
        Patty,
        Lettuce,
        Cheese,
        Tomato,
        Onion,
        Pickles,
        Ketchup,
        Mustard,
        Kelp,
        Seaweed,
        BarnacleRings,
        Chum,
        JellyfishJelly,
        VolcanoSauce,
        TarTarSauce,
        IceCream,
        Sprinkles,
        Cherry,
        Chocolate,
        Vanilla,
        SnailTreats,
        SecretFormula,
        GoldenCrumbs,
        Salt,
        Pepper,
        Mayo,
        Relish,
        INGREDIENT_COUNT
    };

    static const std::array<std::string, static_cast<size_t>(EIngredient::INGREDIENT_COUNT)> IngredientNames =
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
        "Kelp",
        "Seaweed",
        "Barnacle Rings",
        "Chum",
        "Jellyfish Jelly",
        "Volcano Sauce",
        "Tar Tar Sauce",
        "Ice Cream",
        "Sprinkles",
        "Cherry",
        "Chocolate",
        "Vanilla",
        "Snail Treats",
        "Secret Formula",
        "Golden Crumbs",
        "Salt",
        "Pepper",
        "Mayo",
        "Relish"
    };

    struct MenuItem_t final
    {
        Menu::EMenuItem m_MenuItemName;
        std::vector<Menu::EIngredient> m_Ingredients;
        std::vector<size_t> m_IngredientCounts;
    };
}