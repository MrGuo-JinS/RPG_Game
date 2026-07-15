#include "item/Item.hpp"
#include <stdexcept>

void Item::loadCommonFields(const json& data) {
    if (data.contains("uuid") && data["uuid"].is_string()) {
        m_uuid = data["uuid"].get<std::string>();
    }

    if (data.contains("name") && data["name"].is_string()) {
        m_name = data["name"].get<std::string>();
    }

    if (data.contains("description") && data["description"].is_string()) {
        m_description = data["description"].get<std::string>();
    }

    if (data.contains("level") && data["level"].is_number()) {
        m_level = data["level"].get<int>();
    }

    if (data.contains("value") && data["value"].is_number()) {
        m_value = data["value"].get<int>();
    }

    if (data.contains("aliases") && data["aliases"].is_array()) {
        m_aliases.clear();
        for (const auto& alias : data["aliases"]) {
            if (alias.is_string()) {
                m_aliases.push_back(alias.get<std::string>());
            }
        }
    }

    // 解析稀有度
    if (data.contains("rarity") && data["rarity"].is_string()) {
        std::string rarityStr = data["rarity"].get<std::string>();
        if (rarityStr == "common") m_rarity = Rarity::Common;
        else if (rarityStr == "uncommon") m_rarity = Rarity::Uncommon;
        else if (rarityStr == "rare") m_rarity = Rarity::Rare;
        else if (rarityStr == "epic") m_rarity = Rarity::Epic;
        else if (rarityStr == "legendary") m_rarity = Rarity::Legendary;
    }
}

void Item::loadFromJson(const json& data) {
    loadCommonFields(data);
}