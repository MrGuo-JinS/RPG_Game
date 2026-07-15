#include "item/Armor.hpp"

void Armor::loadFromJson(const json& data) {
    loadCommonFields(data);
    m_type = ItemType::Armor;

    if (data.contains("subtype") && data["subtype"].is_string()) {
        m_subtype = data["subtype"].get<std::string>();
    }

    if (data.contains("stats") && data["stats"].is_object()) {
        const auto& stats = data["stats"];
        if (stats.contains("defense") && stats["defense"].is_number()) {
            m_stats.defense = stats["defense"].get<int>();
        }
        if (stats.contains("durability") && stats["durability"].is_number()) {
            m_stats.durability = stats["durability"].get<int>();
        }
        if (stats.contains("weight") && stats["weight"].is_number()) {
            m_stats.weight = stats["weight"].get<float>();
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
    }

    if (data.contains("slots") && data["slots"].is_array()) {
        m_slots.clear();
        for (const auto& slot : data["slots"]) {
            if (slot.is_string()) {
                m_slots.push_back(slot.get<std::string>());
            }
        }
    }
}