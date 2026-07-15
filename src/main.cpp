#include "core/ConfigManager.hpp"
#include "utils/Logger.hpp"
#include "item/Weapon.hpp"
#include "item/Armor.hpp"
#include "item/Consumable.hpp"
#include <iostream>
#include <memory>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Logger logger(LogLevel::Info);

    auto& config = ConfigManager::getInstance();
    config.initialize("../config/");

    // 测试：加载铁剑并转为 Weapon 对象
    auto swordData = config.getByAlias("iron_sword");
    if (swordData.has_value()) {
        Weapon sword;
        sword.loadFromJson(swordData.value());

        logger.Info("✅ 武器加载成功！");
        logger.Info("   名称: " + sword.getName());
        logger.Info("   类型: " + sword.getTypeName());
        logger.Info("   攻击: " + std::to_string(sword.getStats().attack));
        logger.Info("   重量: " + std::to_string(sword.getStats().weight));
        logger.Info("   要求等级: " + std::to_string(sword.getRequirements().level));
    }

    // 测试：加载钢剑
    auto steelData = config.getByAlias("steel_sword");
    if (steelData.has_value()) {
        Weapon steelSword;
        steelSword.loadFromJson(steelData.value());

        logger.Info("✅ 钢剑加载成功！");
        logger.Info("   名称: " + steelSword.getName());
        logger.Info("   攻击: " + std::to_string(steelSword.getStats().attack));
    }

    // 测试：加载皮甲
    auto armorData = config.getByAlias("leather_chest");
    if (armorData.has_value()) {
        Armor armor;
        armor.loadFromJson(armorData.value());

        logger.Info("✅ 皮甲加载成功！");
        logger.Info("   名称: " + armor.getName());
        logger.Info("   防御: " + std::to_string(armor.getStats().defense));
    }

    // 测试：加载生命药水
    auto potionData = config.getByAlias("health_potion");
    if (potionData.has_value()) {
        Consumable potion;
        potion.loadFromJson(potionData.value());

        logger.Info("✅ 生命药水加载成功！");
        logger.Info("   名称: " + potion.getName());
        logger.Info("   恢复 HP: " + std::to_string(potion.getEffects().healHp));
        logger.Info("   可堆叠: " + std::string(potion.isStackable() ? "是" : "否"));
        logger.Info("   最大堆叠: " + std::to_string(potion.getMaxStack()));
    }

    logger.Info("📊 总配置文件数: " + std::to_string(config.getFileCount()));
    logger.Info("测试完成！");

    std::cout << "\n按 Enter 退出...";
    std::cin.get();
    return 0;
}