//
// Created by gaugamela on 7/18/25.
//

#include "SpongeBob.hpp"
#include "MenuItemFactory.hpp"

const std::string YELLOW_ANSI_SEQ = "\033[93m";
const std::string PINK_ANSI_SEQ = "\033[0;95m";
const std::string RESET_ANSI_SEQ = "\033[0m";

SpongeBob::SpongeBob(
    std::weak_ptr<std::queue<Ticket>> ticketLine,
    std::mutex& ticketLineMutex,
    std::condition_variable& ticketCv,
    std::weak_ptr<Freezer> freezer,
    bool IsActuallyPatrick) :
    m_TicketLine(std::move(ticketLine)),
    m_TicketLineMutex(ticketLineMutex),
    m_TicketCv(ticketCv),
    m_RestTimeMs(std::chrono::milliseconds(500)),
    m_Freezer(std::move(freezer)),
    m_IngredientsCv(std::condition_variable()),
    m_IsActuallyPatrick(IsActuallyPatrick),
    m_FrycookStats(FrycookStats_t())
{
   PrintLn(WhoAmI() + "()");
}

SpongeBob::~SpongeBob()
{
   PrintLn("~" + WhoAmI() + "()");
}

void SpongeBob::PrintLn(const std::string &str) const
{
    std::cout << ((m_IsActuallyPatrick ? PINK_ANSI_SEQ : YELLOW_ANSI_SEQ) + str + "\n" + RESET_ANSI_SEQ);
}

void SpongeBob::WakeUp()
{
    m_TicketCv.notify_all();
    m_IngredientsCv.notify_all();
}

const FrycookStats_t& SpongeBob::WorkerStats() const
{
    return m_FrycookStats;
}

void SpongeBob::Work()
{
    while (m_Running)
    {
        std::this_thread::sleep_for(m_RestTimeMs);
        Ticket nextTicket = TryGetTicket();

        if (nextTicket.m_MenuItems.empty())
        {
            continue;
        }

        PrepareOrder(nextTicket);
    }
}

void SpongeBob::PrepareOrder(const Ticket& ticket)
{
    for (const auto& menuItem : ticket.m_MenuItems)
    {
        switch (menuItem.m_MenuItemName)
        {
            case Menu::EMenuItem::KrabbyPatty:
                MakeKrabbyPatty();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::KrabbyPatty]++;
                break;
            case Menu::EMenuItem::DoubleKrabbyPatty:
                MakeDoubleKrabbyPatty();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::DoubleKrabbyPatty]++;
                break;
            case Menu::EMenuItem::TripleKrabbyPattySupreme:
                MakeTripleKrabbyPattySupreme();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::TripleKrabbyPattySupreme]++;
                break;
            case Menu::EMenuItem::KrabbyPattyDeluxe:
                MakeKrabbyPattyDeluxe();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::KrabbyPattyDeluxe]++;
                break;
            case Menu::EMenuItem::BarnacleBurger:
                MakeBarnacleBurger();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::BarnacleBurger]++;
                break;
            case Menu::EMenuItem::KelpShake:
                MakeKelpShake();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::KelpShake]++;
                break;
            case Menu::EMenuItem::SeaweedSalad:
                MakeSeaweedSalad();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::SeaweedSalad]++;
                break;
            case Menu::EMenuItem::BarnacleRings:
                MakeBarnacleRings();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::BarnacleRings]++;
                break;
            case Menu::EMenuItem::KrustyCrab:
                MakeKrustyCrab();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::KrustyCrab]++;
                break;
            case Menu::EMenuItem::PlanktonsBurger:
                MakePlanktonsBurger();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::PlanktonsBurger]++;
                break;
            case Menu::EMenuItem::ChumBucket:
                MakeChumBucket();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::ChumBucket]++;
                break;
            case Menu::EMenuItem::GoldenSpatula:
                MakeGoldenSpatula();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::GoldenSpatula]++;
                break;
            case Menu::EMenuItem::MonsterKrabbyPatty:
                MakeMonsterKrabbyPatty();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::MonsterKrabbyPatty]++;
                break;
            case Menu::EMenuItem::KrabbyPattyPizza:
                MakeKrabbyPattyPizza();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::KrabbyPattyPizza]++;
                break;
            case Menu::EMenuItem::VolcanoSauce:
                MakeVolcanoSauce();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::VolcanoSauce]++;
                break;
            case Menu::EMenuItem::JellyfishJelly:
                MakeJellyfishJelly();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::JellyfishJelly]++;
                break;
            case Menu::EMenuItem::GaryTreat:
                MakeGaryTreat();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::GaryTreat]++;
                break;
            case Menu::EMenuItem::Sundae:
                MakeSundae();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::Sundae]++;
                break;
            case Menu::EMenuItem::IceCream:
                MakeIceCream();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::IceCream]++;
                break;
            case Menu::EMenuItem::ChumFritters:
                MakeChumFritters();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::ChumFritters]++;
                break;
            case Menu::EMenuItem::KelpJerky:
                MakeKelpJerky();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::KelpJerky]++;
                break;
            case Menu::EMenuItem::ChumOnAStick:
                MakeChumOnAStick();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::ChumOnAStick]++;
                break;
            case Menu::EMenuItem::TarTarSauce:
                MakeTarTarSauce();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::TarTarSauce]++;
                break;
            default:
                // Handle unknown menu items - maybe log an error or fall back to Krabby Patty
                MakeKrabbyPatty();
                m_FrycookStats.m_CompletedMenuItems[Menu::EMenuItem::KrabbyPatty]++;
                break;
        }
    }
    m_FrycookStats.m_TicketsCompleted++;
}

void SpongeBob::MakeKrabbyPatty()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetKrabbyPattyIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetKrabbyPattyIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false; // Written to by the Freezer

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeDoubleKrabbyPatty()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetDoubleKrabbyPattyIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetDoubleKrabbyPattyIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeTripleKrabbyPattySupreme()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetTripleKrabbyPattySupremeIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetTripleKrabbyPattySupremeIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeKrabbyPattyDeluxe()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetKrabbyPattyDeluxeIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetKrabbyPattyDeluxeIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeBarnacleBurger()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetBarnacleBurgerIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetBarnacleBurgerIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeKelpShake()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetKelpShakeIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetKelpShakeIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeSeaweedSalad()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetSeaweedSaladIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetSeaweedSaladIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeBarnacleRings()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetBarnacleRingsIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetBarnacleRingsIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeKrustyCrab()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetKrustyCrabIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetKrustyCrabIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakePlanktonsBurger()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetPlanktonsBurgerIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetPlanktonsBurgerIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeChumBucket()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetChumBucketIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetChumBucketIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeGoldenSpatula()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetGoldenSpatulaIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetGoldenSpatulaIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeMonsterKrabbyPatty()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetMonsterKrabbyPattyIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetMonsterKrabbyPattyIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeKrabbyPattyPizza()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetKrabbyPattyPizzaIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetKrabbyPattyPizzaIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeVolcanoSauce()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetVolcanoSauceIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetVolcanoSauceIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeJellyfishJelly()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetJellyfishJellyIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetJellyfishJellyIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeGaryTreat()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetGaryTreatIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetGaryTreatIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeSundae()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetSundaeIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetSundaeIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeIceCream()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetIceCreamIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetIceCreamIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeChumFritters()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetChumFrittersIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetChumFrittersIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeKelpJerky()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetKelpJerkyIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetKelpJerkyIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeChumOnAStick()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetChumOnAStickIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetChumOnAStickIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

void SpongeBob::MakeTarTarSauce()
{
    const std::vector<Menu::EIngredient>& ingredients = MenuItemFactory::GetTarTarSauceIngredients();
    const std::vector<size_t>& ingredientCount = MenuItemFactory::GetTarTarSauceIngredientCounts();

    for (int i = 0; i < ingredients.size(); i++)
    {
        std::shared_ptr<Freezer> freezer = m_Freezer.lock();

        if (!freezer) return;

        bool requestFulfilled = false;

        IngredientRequest_t ir { m_IngredientsCv, requestFulfilled, ingredients[i], ingredientCount[i] };
        freezer->RequestIngredient(ir);

        std::unique_lock<std::mutex> lock(freezer->IngredientsMutex());
        m_IngredientsCv.wait(lock, [&](){ return requestFulfilled || !m_Running; });
    }
}

Ticket SpongeBob::TryGetTicket() const
{
    Ticket finalTicket = {};

    std::shared_ptr<std::queue<Ticket>> ticketLine = m_TicketLine.lock();
    if (!ticketLine)
    {
        return finalTicket;
    }

    bool nowEmpty = false;
    {
        std::unique_lock<std::mutex> lock(m_TicketLineMutex);
        m_TicketCv.wait(lock, [&](){ return !ticketLine->empty() || !m_Running; });

        if (!ticketLine->empty())
        {
            finalTicket = ticketLine->front();
            ticketLine->pop();
            nowEmpty = ticketLine->empty();
        }
    }

    // To notify the krusty krab that the tickets are now empty.
    // Idk why but I don't like this. Why should spongebob give a shit about notifying the krusty krab?
    if (nowEmpty) m_TicketCv.notify_all();

    return finalTicket;

}

std::string SpongeBob::WhoAmI() const
{
    return m_IsActuallyPatrick ? "Patrick" : "Spongebob";
}

