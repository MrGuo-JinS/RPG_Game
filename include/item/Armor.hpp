#pragma once

#include "item/Item.hpp"

struct ArmorStats {
    int defense = 0;
    int durability = 0;
    float weight = 0.0f;
};

struct ArmorRequirements {
    int level = 1;
    int strength = 0;
};

class Armor : public Item {
public:
    Armor() = default;

    void loadFromJson(const json& data) override;
    std::string getTypeName() const override { return "Armor"; }

    const std::string& getSubtype() const { return m_subtype; }
    const ArmorStats& getStats() const { return m_stats; }
    const ArmorRequirements& getRequirements() const { return m_requirements; }
    const std::vector<std::string>& getSlots() const { return m_slots; }

private:
    std::string m_subtype;
    ArmorStats m_stats;
    ArmorRequirements m_requirements;
    std::vector<std::string> m_slots;
};