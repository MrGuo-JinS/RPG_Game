#include "core/ConfigManager.hpp"
#include <fstream>
#include <iostream>
#include <chrono>

// 单例实例
ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

void ConfigManager::initialize(const std::string& rootPath) {
    if (m_initialized) {
        std::cout << "[ConfigManager] 已经初始化，跳过重复初始化\n";
        return;
    }

    m_rootPath = rootPath;
    m_uuidToPath.clear();
    m_aliasToUUID.clear();
    m_cache.clear();

    // 检查目录是否存在
    if (!std::filesystem::exists(m_rootPath)) {
        std::cerr << "[ConfigManager] 错误：目录不存在 " << m_rootPath << "\n";
        return;
    }

    std::cout << "[ConfigManager] 开始扫描目录: " << m_rootPath << "\n";
    scanDirectory(m_rootPath);
    
    m_initialized = true;
    std::cout << "[ConfigManager] 扫描完成，共找到 " << m_uuidToPath.size() << " 个配置文件\n";
    std::cout << "[ConfigManager] 别名映射 " << m_aliasToUUID.size() << " 条\n";
}

void ConfigManager::scanDirectory(const std::filesystem::path& directory) {
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                try {
                    // 读取文件并提取 uuid
                    json data = loadFromFile(entry.path());
                    
                    if (data.contains("uuid") && data["uuid"].is_string()) {
                        std::string uuid = data["uuid"].get<std::string>();
                        
                        // 检查 UUID 是否重复
                        if (m_uuidToPath.find(uuid) != m_uuidToPath.end()) {
                            std::cerr << "[ConfigManager] 警告：重复 UUID " << uuid 
                                      << " 在文件 " << entry.path().string() << "\n";
                            continue;
                        }
                        
                        m_uuidToPath[uuid] = entry.path();
                        
                        // 建立别名映射
                        if (data.contains("aliases") && data["aliases"].is_array()) {
                            for (const auto& alias : data["aliases"]) {
                                if (alias.is_string()) {
                                    std::string aliasStr = alias.get<std::string>();
                                    m_aliasToUUID[aliasStr] = uuid;
                                }
                            }
                        }
                        
                        // 用文件名作为默认别名（不含扩展名）
                        std::string filename = entry.path().stem().string();
                        if (m_aliasToUUID.find(filename) == m_aliasToUUID.end()) {
                            m_aliasToUUID[filename] = uuid;
                        }
                        
                    } else {
                        std::cerr << "[ConfigManager] 警告：文件缺少 uuid 字段 " 
                                  << entry.path().string() << "\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "[ConfigManager] 错误：读取文件失败 " 
                              << entry.path().string() << " - " << e.what() << "\n";
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[ConfigManager] 扫描目录异常: " << e.what() << "\n";
    }
}

json ConfigManager::loadFromFile(const std::filesystem::path& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filePath.string());
    }
    
    json data;
    file >> data;
    return data;
}

std::optional<json> ConfigManager::getByUUID(const std::string& uuid) {
    if (!m_initialized) {
        std::cerr << "[ConfigManager] 错误：未初始化，请先调用 initialize()\n";
        return std::nullopt;
    }

    // 1. 检查缓存
    auto cacheIt = m_cache.find(uuid);
    if (cacheIt != m_cache.end()) {
        // 检查文件是否被修改（热重载支持）
        if (!isFileModified(uuid)) {
            return cacheIt->second.data;
        }
        // 文件已修改，重新加载
        std::cout << "[ConfigManager] 热重载: " << uuid << "\n";
        m_cache.erase(cacheIt);
    }

    // 2. 查找 UUID 对应的路径
    auto pathIt = m_uuidToPath.find(uuid);
    if (pathIt == m_uuidToPath.end()) {
        std::cerr << "[ConfigManager] 找不到 UUID: " << uuid << "\n";
        return std::nullopt;
    }

    // 3. 从文件加载
    try {
        json data = loadFromFile(pathIt->second);
        auto lastModified = std::filesystem::last_write_time(pathIt->second);
        m_cache[uuid] = {data, lastModified};
        return data;
    } catch (const std::exception& e) {
        std::cerr << "[ConfigManager] 加载失败 " << uuid << ": " << e.what() << "\n";
        return std::nullopt;
    }
}

std::optional<json> ConfigManager::getByAlias(const std::string& alias) {
    auto it = m_aliasToUUID.find(alias);
    if (it == m_aliasToUUID.end()) {
        std::cerr << "[ConfigManager] 找不到别名: " << alias << "\n";
        return std::nullopt;
    }
    return getByUUID(it->second);
}

std::vector<json> ConfigManager::getAllByType(const std::string& type) {
    std::vector<json> result;
    
    // 遍历所有已加载的配置
    for (const auto& [uuid, path] : m_uuidToPath) {
        auto data = getByUUID(uuid);
        if (data.has_value() && data->contains("type") && (*data)["type"].is_string()) {
            std::string dataType = (*data)["type"].get<std::string>();
            if (dataType == type) {
                result.push_back(data.value());
            }
        }
    }
    
    return result;
}

std::vector<std::string> ConfigManager::getAllUUIDs() const {
    std::vector<std::string> uuids;
    uuids.reserve(m_uuidToPath.size());
    for (const auto& [uuid, _] : m_uuidToPath) {
        uuids.push_back(uuid);
    }
    return uuids;
}

void ConfigManager::reload(const std::string& uuid) {
    m_cache.erase(uuid);
    getByUUID(uuid);
}

void ConfigManager::clearCache() {
    m_cache.clear();
    std::cout << "[ConfigManager] 缓存已清除\n";
}

bool ConfigManager::isFileModified(const std::string& uuid) const {
    auto pathIt = m_uuidToPath.find(uuid);
    if (pathIt == m_uuidToPath.end()) {
        return true;
    }
    
    auto cacheIt = m_cache.find(uuid);
    if (cacheIt == m_cache.end()) {
        return true;
    }
    
    try {
        auto currentTime = std::filesystem::last_write_time(pathIt->second);
        return currentTime != cacheIt->second.lastModified;
    } catch (...) {
        return true;
    }
}

std::optional<std::filesystem::path> ConfigManager::getPathByUUID(const std::string& uuid) const {
    auto it = m_uuidToPath.find(uuid);
    if (it == m_uuidToPath.end()) {
        return std::nullopt;
    }
    return it->second;
}