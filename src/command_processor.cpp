#include "command_processor.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <utility>

CommandProcessor::CommandProcessor(InMemoryStore &store) : store_(store)
{
}

std::string CommandProcessor::execute(const std::string &input)
{
    const std::vector<std::string> tokens = tokenize(input);

    if (tokens.empty())
    {
        return "";
    }

    const std::string command = normalizeCommand(tokens.front());

    const std::vector<std::string> arguments(
        tokens.begin() + 1,
        tokens.end());

    if (command == "SET")
    {
        return executeSet(arguments);
    }

    if (command == "GET")
    {
        return executeGet(arguments);
    }

    if (command == "DEL")
    {
        return executeDelete(arguments);
    }

    if (command == "EXISTS")
    {
        return executeExists(arguments);
    }

    if (command == "DBSIZE")
    {
        if (!arguments.empty())
        {
            return "(error) ERR wrong number of arguments for 'dbsize'";
        }

        return std::to_string(store_.size());
    }

    if (command == "FLUSHDB")
    {
        if (!arguments.empty())
        {
            return "(error) ERR wrong number of arguments for 'flushdb'";
        }

        store_.clear();
        return "OK";
    }

    if (command == "PING")
    {
        if (arguments.empty())
        {
            return "PONG";
        }

        if (arguments.size() == 1)
        {
            return arguments.front();
        }

        return "(error) ERR wrong number of arguments for 'ping'";
    }

    return "(error) ERR unknown command '" + tokens.front() + "'";
}

std::vector<std::string> CommandProcessor::tokenize(
    const std::string &input)
{
    std::istringstream stream(input);
    std::vector<std::string> tokens;
    std::string token;

    while (stream >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::string CommandProcessor::normalizeCommand(std::string command)
{
    std::transform(
        command.begin(),
        command.end(),
        command.begin(),
        [](unsigned char character)
        {
            return static_cast<char>(std::toupper(character));
        });

    return command;
}

std::string CommandProcessor::executeSet(
    const std::vector<std::string> &arguments)
{
    if (arguments.size() != 2)
    {
        return "(error) ERR wrong number of arguments for 'set'";
    }

    store_.set(arguments[0], arguments[1]);
    return "OK";
}

std::string CommandProcessor::executeGet(
    const std::vector<std::string> &arguments) const
{
    if (arguments.size() != 1)
    {
        return "(error) ERR wrong number of arguments for 'get'";
    }

    const std::optional<std::string> value =
        store_.get(arguments[0]);

    if (!value)
    {
        return "(nil)";
    }

    return *value;
}

std::string CommandProcessor::executeDelete(
    const std::vector<std::string> &arguments)
{
    if (arguments.empty())
    {
        return "(error) ERR wrong number of arguments for 'del'";
    }

    std::size_t removedCount = 0;

    for (const std::string &key : arguments)
    {
        if (store_.remove(key))
        {
            ++removedCount;
        }
    }

    return std::to_string(removedCount);
}

std::string CommandProcessor::executeExists(
    const std::vector<std::string> &arguments) const
{
    if (arguments.empty())
    {
        return "(error) ERR wrong number of arguments for 'exists'";
    }

    std::size_t existingCount = 0;

    for (const std::string &key : arguments)
    {
        if (store_.contains(key))
        {
            ++existingCount;
        }
    }

    return std::to_string(existingCount);
}