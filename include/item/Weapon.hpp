#pragma once

#include "item/Item.hpp"
#include <vector>

struct WeaponStats {
    int attack = 0;
    int durability = 0;
    float weight = 0.0f;
    float critRate = 0.0f;
    float critDamage = 0.0f;
};

struct WeaponRequirements {
    int level = 1;
    int strength = 0;
    int dexterity = 0;
    int intelligence = 0;
};

class Weapon : public Item {
public:
    Weapon() = default;

    void loadFromJson(const json& data) override;
    std::string getTypeName() const override { return "Weapon"; }

    const std::string& getSubtype() const { return m_subtype; }
    const WeaponStats& getStats() const { return m_stats; }
    const WeaponRequirements& getRequirements() const { return m_requirements; }
    const std::vector<std::string>& getSlots() const { return m_slots; }
    int getRange() const { return m_range; }

private:
    std::string m_subtype;
    WeaponStats m_stats;
    WeaponRequirements m_requirements;
    std::vector<std::string> m_slots;
    int m_range = 1;
};