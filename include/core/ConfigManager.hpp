#pragma once

#include "json.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <filesystem>

using json = nlohmann::json;

class ConfigManager {
public:
    // 单例模式（可选，方便全局访问）
    static ConfigManager& getInstance();

    // 初始化：扫描 config/ 目录，建立 UUID → 文件路径 索引
    // 参数：config 根目录路径（默认 "config/"）
    void initialize(const std::string& rootPath = "config/");

    // 根据 UUID 获取 JSON 数据（懒加载）
    std::optional<json> getByUUID(const std::string& uuid);

    // 根据别名获取 JSON 数据（方便开发时用）
    std::optional<json> getByAlias(const std::string& alias);

    // 获取所有指定类型的配置（比如所有 weapon）
    std::vector<json> getAllByType(const std::string& type);

    // 获取所有 UUID 列表
    std::vector<std::string> getAllUUIDs() const;

    // 热重载：重新加载某个 UUID 的文件
    void reload(const std::string& uuid);

    // 清除所有缓存
    void clearCache();

    // 获取加载状态
    bool isInitialized() const { return m_initialized; }

    // 获取扫描到的文件总数
    size_t getFileCount() const { return m_uuidToPath.size(); }

private:
    // 私有构造函数（单例）
    ConfigManager() = default;
    ~ConfigManager() = default;

    // 禁止拷贝
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    // 内部方法
    void scanDirectory(const std::filesystem::path& directory);
    json loadFromFile(const std::filesystem::path& filePath);
    bool isFileModified(const std::string& uuid) const;
    std::optional<std::filesystem::path> getPathByUUID(const std::string& uuid) const;

    // 缓存结构
    struct CacheEntry {
        json data;
        std::filesystem::file_time_type lastModified;
    };

    // 成员变量
    bool m_initialized = false;
    std::string m_rootPath;

    // UUID → 文件路径映射（索引）
    std::unordered_map<std::string, std::filesystem::path> m_uuidToPath;

    // 别名 → UUID 映射（方便开发）
    std::unordered_map<std::string, std::string> m_aliasToUUID;

    // UUID → 缓存数据（懒加载）
    std::unordered_map<std::string, CacheEntry> m_cache;

    // 日志器（可选）
    // Logger* m_logger = nullptr;
};