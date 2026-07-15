#pragma once

#include "json.hpp"
#include <string>
#include <vector>
#include <unordered_map>

using json = nlohmann::json;

// 怪物阵营
enum class Faction {
    Neutral,    // 中立（不会主动攻击）
    Hostile,    // 敌对（主动攻击）
    Friendly    // 友好（不会攻击，可交互）
};

// 怪物 AI 行为
enum class AIBehavior {
    Passive,    // 被动（不攻击，逃跑）
    Neutral,    // 中立（受到攻击才反击）
    Aggressive  // 主动（看到玩家就攻击）
};

// 怪物掉落物品
struct LootEntry {
    std::string itemUUID;
    float probability = 0.0f;
    int minQuantity = 1;
    int maxQuantity = 1;
};

// 怪物属性
struct MonsterStats {
    int hp = 0;
    int maxHp = 0;
    int mp = 0;
    int maxMp = 0;
    int attack = 0;
    int defense = 0;
    int speed = 0;
    int expReward = 0;
};

// 怪物抗性
struct MonsterResistances {
    float physical = 0.0f;
    float fire = 0.0f;
    float ice = 0.0f;
    float lightning = 0.0f;
    float poison = 0.0f;
    float holy = 0.0f;
    float dark = 0.0f;
};

// AI 配置
struct MonsterAI {
    AIBehavior behavior = AIBehavior::Passive;
    int aggroRange = 3;         // 警戒范围
    int attackRange = 1;        // 攻击范围
    float fleeThreshold = 0.2f; // 逃跑血量阈值（20%）
    int patrolSpeed = 1;        // 巡逻速度
};

// 怪物类
class Monster {
public:
    Monster() = default;

    // 从 JSON 加载
    void loadFromJson(const json& data);

    // Getter
    std::string getUUID() const { return m_uuid; }
    std::string getName() const { return m_name; }
    std::string getDescription() const { return m_description; }
    int getLevel() const { return m_level; }
    std::string getRace() const { return m_race; }
    Faction getFaction() const { return m_faction; }

    const MonsterStats& getStats() const { return m_stats; }
    const MonsterResistances& getResistances() const { return m_resistances; }
    const std::vector<LootEntry>& getLootTable() const { return m_lootTable; }
    const MonsterAI& getAI() const { return m_ai; }
    const std::vector<std::string>& getSkills() const { return m_skills; }
    const std::vector<std::string>& getAliases() const { return m_aliases; }

    // 战斗相关
    bool isAlive() const { return m_currentHp > 0; }
    void takeDamage(int damage);
    void heal(int amount);
    int getCurrentHp() const { return m_currentHp; }
    void resetHp();  // 重置到满血

private:
    // 解析辅助函数
    Faction parseFaction(const std::string& str) const;
    AIBehavior parseAIBehavior(const std::string& str) const;

private:
    // 基础信息
    std::string m_uuid;
    std::string m_name;
    std::string m_description;
    std::vector<std::string> m_aliases;
    int m_level = 1;
    std::string m_race;
    Faction m_faction = Faction::Neutral;

    // 属性
    MonsterStats m_stats;
    int m_currentHp = 0;

    // 抗性
    MonsterResistances m_resistances;

    // 掉落
    std::vector<LootEntry> m_lootTable;

    // AI
    MonsterAI m_ai;

    // 技能
    std::vector<std::string> m_skills;
};