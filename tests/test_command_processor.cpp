#include "command_processor.h"
#include "in_memory_store.h"

#include <stdexcept>
#include <string>

namespace
{
    void expectEqual(
        const std::string &actual,
        const std::string &expected,
        const std::string &message)
    {
        if (actual != expected)
        {
            throw std::runtime_error(
                message +
                " | expected: \"" + expected +
                "\", actual: \"" + actual + "\"");
        }
    }

    void testSetAndGetCommands()
    {
        InMemoryStore store;
        CommandProcessor processor(store);

        expectEqual(
            processor.execute("SET name Michael"),
            "OK",
            "SET command failed");

        expectEqual(
            processor.execute("GET name"),
            "Michael",
            "GET command returned the wrong value");
    }

    void testCommandsAreCaseInsensitive()
    {
        InMemoryStore store;
        CommandProcessor processor(store);

        expectEqual(
            processor.execute("set language cpp"),
            "OK",
            "Lowercase SET command failed");

        expectEqual(
            processor.execute("get language"),
            "cpp",
            "Lowercase GET command failed");
    }

    void testGetMissingKey()
    {
        InMemoryStore store;
        CommandProcessor processor(store);

        expectEqual(
            processor.execute("GET missing"),
            "(nil)",
            "GET missing key should return nil");
    }

    void testDeleteCommand()
    {
        InMemoryStore store;
        CommandProcessor processor(store);

        processor.execute("SET first one");
        processor.execute("SET second two");

        expectEqual(
            processor.execute("DEL first second missing"),
            "2",
            "DEL should return the number of removed keys");
    }

    void testExistsCommand()
    {
        InMemoryStore store;
        CommandProcessor processor(store);

        processor.execute("SET first one");
        processor.execute("SET second two");

        expectEqual(
            processor.execute("EXISTS first missing second"),
            "2",
            "EXISTS should return the number of existing keys");
    }

    void testPingCommand()
    {
        InMemoryStore store;
        CommandProcessor processor(store);

        expectEqual(
            processor.execute("PING"),
            "PONG",
            "PING should return PONG");

        expectEqual(
            processor.execute("PING hello"),
            "hello",
            "PING with one argument should echo the argument");
    }

    void testUnknownCommand()
    {
        InMemoryStore store;
        CommandProcessor processor(store);

        expectEqual(
            processor.execute("INVALID"),
            "(error) ERR unknown command 'INVALID'",
            "Unknown command returned the wrong error");
    }
}

void runCommandProcessorTests()
{
    testSetAndGetCommands();
    testCommandsAreCaseInsensitive();
    testGetMissingKey();
    testDeleteCommand();
    testExistsCommand();
    testPingCommand();
    testUnknownCommand();
}