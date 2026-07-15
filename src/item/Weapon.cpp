#include "item/Weapon.hpp"

void Weapon::loadFromJson(const json& data) {
    // 加载通用字段
    loadCommonFields(data);

    // 设置类型
    m_type = ItemType::Weapon;

    // 加载武器特有字段
    if (data.contains("subtype") && data["subtype"].is_string()) {
        m_subtype = data["subtype"].get<std::string>();
    }

    if (data.contains("stats") && data["stats"].is_object()) {
        const auto& stats = data["stats"];
        if (stats.contains("attack") && stats["attack"].is_number()) {
            m_stats.attack = stats["attack"].get<int>();
        }
        if (stats.contains("durability") && stats["durability"].is_number()) {
            m_stats.durability = stats["durability"].get<int>();
        }
        if (stats.contains("weight") && stats["weight"].is_number()) {
            m_stats.weight = stats["weight"].get<float>();
        }
        if (stats.contains("critRate") && stats["critRate"].is_number()) {
            m_stats.critRate = stats["critRate"].get<float>();
        }
        if (stats.contains("critDamage") && stats["critDamage"].is_number()) {
            m_stats.critDamage = stats["critDamage"].get<float>();
        }
    }

    if (data.contains("requirements") && data["requirements"].is_object()) {
        const auto& req = data["requirements"];
        if (req.contains("level") && req["level"].is_number()) {
            m_requirements.level = req["level"].get<int>();
        }
        if (req.contains("strength") && req["strength"].is_number()) {
            m_requirements.strength = req["strength"].get<int>();
        }
        if (req.contains("dexterity") && req["dexterity"].is_number()) {
            m_requirements.dexterity = req["dexterity"].get<int>();
        }
        if (req.contains("intelligence") && req["intelligence"].is_number()) {
            m_requirements.intelligence = req["intelligence"].get<int>();
        }
    }

    if (data.contains("slots") && data["slots"].is_array()) {
        m_slots.clear();
        for (const auto& slot : data["slots"]) {
            if (slot.is_string()) {
                m_slots.push_back(slot.get<std::string>());
            }
        }
    }

    if (data.contains("range") && data["range"].is_number()) {
        m_range = data["range"].get<int>();
    }
}