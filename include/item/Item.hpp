#pragma once

#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;

// 物品稀有度
enum class Rarity {
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary
};

// 物品类型
enum class ItemType {
    Weapon,
    Armor,
    Consumable,
    Material,
    Quest
};

// 物品基类
class Item {
public:
    Item() = default;
    virtual ~Item() = default;

    // 从 JSON 加载数据
    virtual void loadFromJson(const json& data);

    // Getter
    std::string getUUID() const { return m_uuid; }
    std::string getName() const { return m_name; }
    std::string getDescription() const { return m_description; }
    ItemType getType() const { return m_type; }
    Rarity getRarity() const { return m_rarity; }
    int getLevel() const { return m_level; }
    int getValue() const { return m_value; }
    const std::vector<std::string>& getAliases() const { return m_aliases; }

    // 虚函数：子类重写
    virtual std::string getTypeName() const = 0;

protected:
    // 从 JSON 读取通用字段
    void loadCommonFields(const json& data);

protected:
    std::string m_uuid;
    std::string m_name;
    std::string m_description;
    ItemType m_type = ItemType::Weapon;
    Rarity m_rarity = Rarity::Common;
    int m_level = 1;
    int m_value = 0;
    std::vector<std::string> m_aliases;
};