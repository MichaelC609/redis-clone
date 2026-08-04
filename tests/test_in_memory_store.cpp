#include "in_memory_store.h"

#include <stdexcept>
#include <string>

namespace
{
    void expectTrue(bool condition, const std::string &message)
    {
        if (!condition)
        {
            throw std::runtime_error(message);
        }
    }

    void testSetAndGet()
    {
        InMemoryStore store;

        store.set("name", "Michael");

        const std::optional<std::string> value =
            store.get("name");

        expectTrue(
            value.has_value(),
            "SET followed by GET should return a value");

        expectTrue(
            value.value() == "Michael",
            "GET returned the wrong value");
    }

    void testGetMissingKey()
    {
        InMemoryStore store;

        const std::optional<std::string> value =
            store.get("missing");

        expectTrue(
            !value.has_value(),
            "GET on a missing key should return std::nullopt");
    }

    void testSetOverwritesExistingValue()
    {
        InMemoryStore store;

        store.set("language", "C++");
        store.set("language", "Rust");

        const std::optional<std::string> value =
            store.get("language");

        expectTrue(
            value.has_value() && value.value() == "Rust",
            "SET should overwrite an existing value");
    }

    void testRemoveExistingKey()
    {
        InMemoryStore store;

        store.set("key", "value");

        const bool removed = store.remove("key");

        expectTrue(
            removed,
            "Removing an existing key should return true");

        expectTrue(
            !store.contains("key"),
            "Removed key should no longer exist");
    }

    void testRemoveMissingKey()
    {
        InMemoryStore store;

        const bool removed = store.remove("missing");

        expectTrue(
            !removed,
            "Removing a missing key should return false");
    }
}

void runInMemoryStoreTests()
{
    testSetAndGet();
    testGetMissingKey();
    testSetOverwritesExistingValue();
    testRemoveExistingKey();
    testRemoveMissingKey();
}