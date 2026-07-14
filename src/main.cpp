#include "core/ConfigManager.hpp"
#include "utils/Logger.hpp"
#include <iostream>

int main() {

    Logger logger(LogLevel::Info);

    auto& config = ConfigManager::getInstance();
    config.initialize("../config/");  // ← 改成这个

    // 测试：通过 UUID 读取铁剑
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

    // 测试：通过别名读取
    auto swordData2 = config.getByAlias("iron_sword");
    if (swordData2.has_value()) {
        std::string name = (*swordData2)["name"].get<std::string>();
        logger.Info("✅ 通过别名加载成功！");
        logger.Info("   名称: " + name);
    }

    // 获取所有武器
    auto weapons = config.getAllByType("weapon");
    logger.Info("✅ 共找到 " + std::to_string(weapons.size()) + " 个武器配置");

    logger.Info("测试完成！");
    return 0;
}