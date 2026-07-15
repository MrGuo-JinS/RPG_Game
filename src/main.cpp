#include "core/ConfigManager.hpp"
#include "utils/Logger.hpp"
#include <iostream>
#include <windows.h>

int main() {
    // 修复中文乱码
    SetConsoleOutputCP(CP_UTF8);

    Logger logger(LogLevel::Info);

    auto& config = ConfigManager::getInstance();
    config.initialize("../config/");

    // 测试 1：通过 UUID 读取铁剑
    std::string testUUID = "7d2c0ee7-607d-4bbd-baf7-f731304c379d";
    auto swordData = config.getByUUID(testUUID);

    if (swordData.has_value()) {
        std::string name = (*swordData)["name"].get<std::string>();
        int attack = (*swordData)["stats"]["attack"].get<int>();
        logger.Info("✅ 通过 UUID 加载成功！");
        logger.Info("   名称: " + name);
        logger.Info("   攻击: " + std::to_string(attack));
    } else {
        logger.Error("❌ 通过 UUID 加载失败");
    }

    // 测试 2：通过别名读取
    auto swordData2 = config.getByAlias("iron_sword");
    if (swordData2.has_value()) {
        std::string name = (*swordData2)["name"].get<std::string>();
        logger.Info("✅ 通过别名加载成功！");
        logger.Info("   名称: " + name);
    }

    // 测试 3：获取所有武器
    auto weapons = config.getAllByType("weapon");
    logger.Info("✅ 共找到 " + std::to_string(weapons.size()) + " 个武器配置");

    // 测试 4：读取钢剑
    auto steelSword = config.getByAlias("steel_sword");
    if (steelSword.has_value()) {
        std::string name = (*steelSword)["name"].get<std::string>();
        int attack = (*steelSword)["stats"]["attack"].get<int>();
        logger.Info("✅ 钢剑加载成功！");
        logger.Info("   名称: " + name);
        logger.Info("   攻击: " + std::to_string(attack));
    }

    // 测试 5：读取生命药水
    auto potion = config.getByAlias("health_potion");
    if (potion.has_value()) {
        std::string name = (*potion)["name"].get<std::string>();
        int heal = (*potion)["effects"]["heal_hp"].get<int>();
        logger.Info("✅ 生命药水加载成功！");
        logger.Info("   名称: " + name);
        logger.Info("   恢复 HP: " + std::to_string(heal));
    }

    // 测试 6：读取史莱姆
    auto slime = config.getByAlias("slime");
    if (slime.has_value()) {
        std::string name = (*slime)["name"].get<std::string>();
        int hp = (*slime)["stats"]["hp"].get<int>();
        logger.Info("✅ 史莱姆加载成功！");
        logger.Info("   名称: " + name);
        logger.Info("   HP: " + std::to_string(hp));
    }

    logger.Info("📊 总配置文件数: " + std::to_string(config.getFileCount()));
    logger.Info("测试完成！");

    std::cout << "\n按 Enter 退出...";
    std::cin.get();
    return 0;
}