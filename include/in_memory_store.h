#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <unordered_map>

class InMemoryStore
{
public:
    void set(const std::string &key, const std::string &value);

    [[nodiscard]]
    std::optional<std::string> get(const std::string &key) const;

    [[nodiscard]]
    bool remove(const std::string &key);

    [[nodiscard]]
    bool contains(const std::string &key) const;

    [[nodiscard]]
    std::size_t size() const noexcept;

    void clear() noexcept;

private:
    std::unordered_map<std::string, std::string> values_;
};