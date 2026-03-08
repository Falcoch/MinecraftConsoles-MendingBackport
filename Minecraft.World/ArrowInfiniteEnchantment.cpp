#include "stdafx.h"
#include "ArrowInfiniteEnchantment.h"

ArrowInfiniteEnchantment::ArrowInfiniteEnchantment(int id, int frequency) : Enchantment(id, frequency, EnchantmentCategory::bow)
{
	setDescriptionId(IDS_ENCHANTMENT_ARROW_INFINITE);
}

int ArrowInfiniteEnchantment::getMinCost(int level)
{
	return 20;
}

int ArrowInfiniteEnchantment::getMaxCost(int level)
{
	return 50;
}

int ArrowInfiniteEnchantment::getMaxLevel()
{
	return 1;
}

bool ArrowInfiniteEnchantment::isCompatibleWith(Enchantment *other) const
{
	return other->id != Enchantment::mendingBonus->id;
}