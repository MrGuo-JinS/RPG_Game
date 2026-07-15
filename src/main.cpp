#include "core/ConfigManager.hpp"
#include "utils/Logger.hpp"
#include "item/Weapon.hpp"
#include "item/Armor.hpp"
#include "item/Consumable.hpp"
#include <iostream>
#include <windows.h>

void testWeapon(Logger& logger, ConfigManager& config, const std::string& alias) {
    auto data = config.getByAlias(alias);
    if (data.has_value()) {
        Weapon item;
        item.loadFromJson(data.value());
        logger.Info("  ✅ " + item.getName() + " (攻击: " + std::to_string(item.getStats().attack) + ")");
    } else {
        logger.Warning("  ⚠️ " + alias + " 未找到");
    }
}

void testArmor(Logger& logger, ConfigManager& config, const std::string& alias) {
    auto data = config.getByAlias(alias);
    if (data.has_value()) {
        Armor item;
        item.loadFromJson(data.value());
        logger.Info("  ✅ " + item.getName() + " (防御: " + std::to_string(item.getStats().defense) + ")");
    } else {
        logger.Warning("  ⚠️ " + alias + " 未找到");
    }
}

void testConsumable(Logger& logger, ConfigManager& config, const std::string& alias) {
    auto data = config.getByAlias(alias);
    if (data.has_value()) {
        Consumable item;
        item.loadFromJson(data.value());
        logger.Info("  ✅ " + item.getName() + " (恢复 HP: " + std::to_string(item.getEffects().healHp) + ", MP: " + std::to_string(item.getEffects().healMp) + ")");
    } else {
        logger.Warning("  ⚠️ " + alias + " 未找到");
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Logger logger(LogLevel::Info);

    auto& config = ConfigManager::getInstance();
    config.initialize("../config/");

    logger.Info("📦 武器列表:");
    testWeapon(logger, config, "iron_sword");
    testWeapon(logger, config, "steel_sword");
    testWeapon(logger, config, "dagger");
    testWeapon(logger, config, "longbow");
    testWeapon(logger, config, "flame_brand");

    logger.Info("");

    logger.Info("🛡️ 防具列表:");
    testArmor(logger, config, "leather_chest");
    testArmor(logger, config, "iron_helmet");
    testArmor(logger, config, "iron_boots");

    logger.Info("");

    logger.Info("🧪 消耗品列表:");
    testConsumable(logger, config, "health_potion");
    testConsumable(logger, config, "mana_potion");
    testConsumable(logger, config, "antidote");

    logger.Info("");

    logger.Info("👹 怪物列表:");
    auto slime = config.getByAlias("slime");
    if (slime.has_value()) {
        std::string name = (*slime)["name"].get<std::string>();
        int hp = (*slime)["stats"]["hp"].get<int>();
        logger.Info("  ✅ " + name + " (HP: " + std::to_string(hp) + ")");
    }

    auto goblin = config.getByAlias("goblin_warrior");
    if (goblin.has_value()) {
        std::string name = (*goblin)["name"].get<std::string>();
        int hp = (*goblin)["stats"]["hp"].get<int>();
        logger.Info("  ✅ " + name + " (HP: " + std::to_string(hp) + ")");
    }

    auto skeleton = config.getByAlias("skeleton");
    if (skeleton.has_value()) {
        std::string name = (*skeleton)["name"].get<std::string>();
        int hp = (*skeleton)["stats"]["hp"].get<int>();
        logger.Info("  ✅ " + name + " (HP: " + std::to_string(hp) + ")");
    }

    logger.Info("");

    logger.Info("📊 总配置文件数: " + std::to_string(config.getFileCount()));
    logger.Info("✅ 测试完成！");

    std::cout << "\n按 Enter 退出...";
    std::cin.get();
    return 0;
}