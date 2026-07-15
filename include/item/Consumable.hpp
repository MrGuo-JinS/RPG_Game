#pragma once

#include "item/Item.hpp"

struct ConsumableEffects {
    int healHp = 0;
    int healMp = 0;
    int buffAttack = 0;
    int buffDefense = 0;
    int buffSpeed = 0;
    bool curePoison = false;
    bool cureParalysis = false;
};

class Consumable : public Item {
public:
    Consumable() = default;

    void loadFromJson(const json& data) override;
    std::string getTypeName() const override { return "Consumable"; }

    const std::string& getSubtype() const { return m_subtype; }
    const ConsumableEffects& getEffects() const { return m_effects; }
    bool isStackable() const { return m_stackable; }
    int getMaxStack() const { return m_maxStack; }

private:
    std::string m_subtype;
    ConsumableEffects m_effects;
    bool m_stackable = true;
    int m_maxStack = 99;
};