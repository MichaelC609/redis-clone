#pragma once

#include "in_memory_store.h"

#include <string>
#include <vector>

class CommandProcessor
{
public:
    explicit CommandProcessor(InMemoryStore &store);

    [[nodiscard]]
    std::string execute(const std::string &input);

private:
    [[nodiscard]]
    static std::vector<std::string> tokenize(const std::string &input);

    [[nodiscard]]
    static std::string normalizeCommand(std::string command);

    [[nodiscard]]
    std::string executeSet(const std::vector<std::string> &arguments);

    [[nodiscard]]
    std::string executeGet(const std::vector<std::string> &arguments) const;

    [[nodiscard]]
    std::string executeDelete(const std::vector<std::string> &arguments);

    [[nodiscard]]
    std::string executeExists(const std::vector<std::string> &arguments) const;

    InMemoryStore &store_;
};