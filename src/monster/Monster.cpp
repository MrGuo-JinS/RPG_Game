#include "monster/Monster.hpp"
#include <stdexcept>

void Monster::loadFromJson(const json& data) {
    // 基础信息
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

    if (data.contains("race") && data["race"].is_string()) {
        m_race = data["race"].get<std::string>();
    }

    if (data.contains("aliases") && data["aliases"].is_array()) {
        m_aliases.clear();
        for (const auto& alias : data["aliases"]) {
            if (alias.is_string()) {
                m_aliases.push_back(alias.get<std::string>());
            }
        }
    }

    // 阵营
    if (data.contains("faction") && data["faction"].is_string()) {
        m_faction = parseFaction(data["faction"].get<std::string>());
    }

    // 属性
    if (data.contains("stats") && data["stats"].is_object()) {
        const auto& stats = data["stats"];
        if (stats.contains("hp") && stats["hp"].is_number()) {
            m_stats.hp = stats["hp"].get<int>();
            m_stats.maxHp = stats["hp"].get<int>();
        }
        if (stats.contains("max_hp") && stats["max_hp"].is_number()) {
            m_stats.maxHp = stats["max_hp"].get<int>();
        }
        if (stats.contains("mp") && stats["mp"].is_number()) {
            m_stats.mp = stats["mp"].get<int>();
            m_stats.maxMp = stats["mp"].get<int>();
        }
        if (stats.contains("max_mp") && stats["max_mp"].is_number()) {
            m_stats.maxMp = stats["max_mp"].get<int>();
        }
        if (stats.contains("attack") && stats["attack"].is_number()) {
            m_stats.attack = stats["attack"].get<int>();
        }
        if (stats.contains("defense") && stats["defense"].is_number()) {
            m_stats.defense = stats["defense"].get<int>();
        }
        if (stats.contains("speed") && stats["speed"].is_number()) {
            m_stats.speed = stats["speed"].get<int>();
        }
        if (stats.contains("exp_reward") && stats["exp_reward"].is_number()) {
            m_stats.expReward = stats["exp_reward"].get<int>();
        }
    }

    // 初始化当前血量
    m_currentHp = m_stats.maxHp;

    // 抗性
    if (data.contains("resistances") && data["resistances"].is_object()) {
        const auto& res = data["resistances"];
        if (res.contains("physical") && res["physical"].is_number()) {
            m_resistances.physical = res["physical"].get<float>();
        }
        if (res.contains("fire") && res["fire"].is_number()) {
            m_resistances.fire = res["fire"].get<float>();
        }
        if (res.contains("ice") && res["ice"].is_number()) {
            m_resistances.ice = res["ice"].get<float>();
        }
        if (res.contains("lightning") && res["lightning"].is_number()) {
            m_resistances.lightning = res["lightning"].get<float>();
        }
        if (res.contains("poison") && res["poison"].is_number()) {
            m_resistances.poison = res["poison"].get<float>();
        }
        if (res.contains("holy") && res["holy"].is_number()) {
            m_resistances.holy = res["holy"].get<float>();
        }
        if (res.contains("dark") && res["dark"].is_number()) {
            m_resistances.dark = res["dark"].get<float>();
        }
    }

    // 掉落表
    if (data.contains("loot_table") && data["loot_table"].is_array()) {
        m_lootTable.clear();
        for (const auto& entry : data["loot_table"]) {
            LootEntry loot;
            if (entry.contains("uuid") && entry["uuid"].is_string()) {
                loot.itemUUID = entry["uuid"].get<std::string>();
            }
            if (entry.contains("probability") && entry["probability"].is_number()) {
                loot.probability = entry["probability"].get<float>();
            }
            if (entry.contains("min_quantity") && entry["min_quantity"].is_number()) {
                loot.minQuantity = entry["min_quantity"].get<int>();
            }
            if (entry.contains("max_quantity") && entry["max_quantity"].is_number()) {
                loot.maxQuantity = entry["max_quantity"].get<int>();
            }
            m_lootTable.push_back(loot);
        }
    }

    // AI
    if (data.contains("ai") && data["ai"].is_object()) {
        const auto& ai = data["ai"];
        if (ai.contains("behavior") && ai["behavior"].is_string()) {
            m_ai.behavior = parseAIBehavior(ai["behavior"].get<std::string>());
        }
        if (ai.contains("aggro_range") && ai["aggro_range"].is_number()) {
            m_ai.aggroRange = ai["aggro_range"].get<int>();
        }
        if (ai.contains("attack_range") && ai["attack_range"].is_number()) {
            m_ai.attackRange = ai["attack_range"].get<int>();
        }
        if (ai.contains("flee_threshold") && ai["flee_threshold"].is_number()) {
            m_ai.fleeThreshold = ai["flee_threshold"].get<float>();
        }
        if (ai.contains("patrol_speed") && ai["patrol_speed"].is_number()) {
            m_ai.patrolSpeed = ai["patrol_speed"].get<int>();
        }
    }

    // 技能
    if (data.contains("skills") && data["skills"].is_array()) {
        m_skills.clear();
        for (const auto& skill : data["skills"]) {
            if (skill.is_string()) {
                m_skills.push_back(skill.get<std::string>());
            }
        }
    }
}

Faction Monster::parseFaction(const std::string& str) const {
    if (str == "neutral") return Faction::Neutral;
    if (str == "hostile") return Faction::Hostile;
    if (str == "friendly") return Faction::Friendly;
    return Faction::Neutral;
}

AIBehavior Monster::parseAIBehavior(const std::string& str) const {
    if (str == "passive") return AIBehavior::Passive;
    if (str == "neutral") return AIBehavior::Neutral;
    if (str == "aggressive") return AIBehavior::Aggressive;
    return AIBehavior::Passive;
}

void Monster::takeDamage(int damage) {
    if (damage < 0) damage = 0;
    m_currentHp -= damage;
    if (m_currentHp < 0) m_currentHp = 0;
}

void Monster::heal(int amount) {
    if (amount < 0) return;
    m_currentHp += amount;
    if (m_currentHp > m_stats.maxHp) {
        m_currentHp = m_stats.maxHp;
    }
}

void Monster::resetHp() {
    m_currentHp = m_stats.maxHp;
}