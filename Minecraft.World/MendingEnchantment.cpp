#include "MendingEnchantment.h"
#include "stdafx.h"

#include <memory>
#include <random>

#include "Inventory.h"
#include "net.minecraft.world.item.enchantment.h"

MendingEnchantment::MendingEnchantment(int id, int frequency) noexcept
: Enchantment(id, frequency, EnchantmentCategory::all)
{
    setDescriptionId(IDS_ENCHANTMENT_BACKPORT_MENDING);
}

int MendingEnchantment::apply(int amount, std::shared_ptr<Inventory> & inventory) const
{
    auto items = getMendableItems(inventory);
    if (items.empty())
    {
        return amount;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distr(0, items.size() - 1);

    for (int i = 0; i < amount; ++i)
    {
        auto & item = items[distr(gen)];

        // Item is at 1 damage
        if(item->getAuxValue() <= 1)
        {
            item->setAuxValue(0);
            return amount;
        }

        item->setAuxValue(item->getAuxValue() - MendingEnchantment::REPAIR);

        // Item is fully repaired
        if (!item->isDamaged())
        {
            return amount - i;
        }
    }

    return 0;
}

bool MendingEnchantment::canApply(std::shared_ptr<ItemInstance> &item) const
{
    if (item == nullptr)
    {
        return false;
    }

    return EnchantmentHelper::getEnchantmentLevel(id, item) > 0 && item->isDamaged();
}

bool MendingEnchantment::canApply(std::shared_ptr<Inventory> &inventory) const
{
    auto &held = inventory->items[inventory->selected];
    if (canApply(held))
    {
        return true;
    }

    for (unsigned int i = 0u; i < inventory->armor.length; ++i)
    {
        auto &current = inventory->armor[i];
        if (canApply(current))
        {
            return true;
        }
    }

    return false;
}

std::vector<std::shared_ptr<ItemInstance>> MendingEnchantment::getMendableItems(std::shared_ptr<Inventory> & inventory) const
{
    std::vector<std::shared_ptr<ItemInstance>> items;
    auto & current = inventory->items[inventory->selected];
    if (canApply(current))
    {
        items.push_back(current);
    }

    for (unsigned int i = 0u; i < inventory->armor.length; ++i)
    {
        auto &current = inventory->armor[i];
        if (canApply(current))
        {
            items.push_back(current);
        }
    }

    return items;
}

int MendingEnchantment::getMinCost(int level)
{
	return 20;
}

int MendingEnchantment::getMaxCost(int level)
{
	return 50;
}

int MendingEnchantment::getMaxLevel()
{
	return 1;
}

bool MendingEnchantment::isCompatibleWith(Enchantment * other) const
{
	return other->id != arrowInfinite->id;
}
