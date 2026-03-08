#pragma once

#include "Enchantment.h"

#include "ArrayWithLength.h"

class MendingEnchantment : public Enchantment
{
    public:
        /*
         * Should only be called in the Enchantment class due to the CURRENT MCLCE implementation.
         * @param id The enchantment id regarding other enchantments.
         * @param freq The frequency of apparition of this enchantment in the enchanting table.
         */
        MendingEnchantment(int id, int freq);

        /*
         * Apply the mending enchantment on a randomly selected item from `inventory` to repair it with `xp` amount.
         * @param xp The amount of experience given for repairing.
         * @param inventory The inventory where damaged mending items are present.
         * @return `int` - The amount of experience remaining after applying the Mending enchantment.
             *          If no damaged mending items are found in `inventory`, `xp` is returned.
        */
        int apply(int xp, std::shared_ptr<Inventory> &inventory) const noexcept;

        /*
         * Check if an item can be repaired by the Mending enchantment.
         * @param item The tested item.
         * @return `true` - if `item` is damaged and enchanted with mending else `false` is returned.
             *          If the item is `nullptr`, `false` is returned.
        */
        bool canApply(std::shared_ptr<ItemInstance> &item) const noexcept;

        /*
         * Check if in `inventory` some items can be repaired.
         * @param item The tested inventory.
         * @return `true` - if the hand or one armor slot owns an item damaged and enchanted with
         *         mending, else `false` is returned.
         */
        bool canApply(std::shared_ptr<Inventory> &inventory) const noexcept;

        /*
         * Find items that are repairable with mending and return them.
         * @param item The tested inventory.
         * @return `std::vector<std::shared_ptr<ItemInstance>>` - An array that can contain the hand
         *         or armor slots own an item damaged and enchanted with mending.
         */
        std::vector<std::shared_ptr<ItemInstance>> getMendableItems(std::shared_ptr<Inventory> &inventory) const noexcept;

        /*
        *   
        */
        int getMinCost(int level) override;

        /*
        *
        */
	    int getMaxCost(int level) override;

        /*
        *
        */
	    int getMaxLevel() override;

        /*
        *   Mending is not compatible with infinity.
        */
        bool isCompatibleWith(Enchantment *other) const override;

    protected:
        static constexpr int REPAIR = 2;
};
