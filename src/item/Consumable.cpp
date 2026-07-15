#include "item/Consumable.hpp"

void Consumable::loadFromJson(const json& data) {
    loadCommonFields(data);
    m_type = ItemType::Consumable;

    if (data.contains("subtype") && data["subtype"].is_string()) {
        m_subtype = data["subtype"].get<std::string>();
    }

    if (data.contains("effects") && data["effects"].is_object()) {
        const auto& effects = data["effects"];
        if (effects.contains("heal_hp") && effects["heal_hp"].is_number()) {
            m_effects.healHp = effects["heal_hp"].get<int>();
        }
        if (effects.contains("heal_mp") && effects["heal_mp"].is_number()) {
            m_effects.healMp = effects["heal_mp"].get<int>();
        }
        if (effects.contains("buff_attack") && effects["buff_attack"].is_number()) {
            m_effects.buffAttack = effects["buff_attack"].get<int>();
        }
        if (effects.contains("buff_defense") && effects["buff_defense"].is_number()) {
            m_effects.buffDefense = effects["buff_defense"].get<int>();
        }
        if (effects.contains("buff_speed") && effects["buff_speed"].is_number()) {
            m_effects.buffSpeed = effects["buff_speed"].get<int>();
        }
        if (effects.contains("cure_poison") && effects["cure_poison"].is_boolean()) {
            m_effects.curePoison = effects["cure_poison"].get<bool>();
        }
        if (effects.contains("cure_paralysis") && effects["cure_paralysis"].is_boolean()) {
            m_effects.cureParalysis = effects["cure_paralysis"].get<bool>();
        }
    }

    if (data.contains("stackable") && data["stackable"].is_boolean()) {
        m_stackable = data["stackable"].get<bool>();
    }

    if (data.contains("max_stack") && data["max_stack"].is_number()) {
        m_maxStack = data["max_stack"].get<int>();
    }
};