#include "in_memory_store.h"

void InMemoryStore::set(const std::string &key, const std::string &value)
{
    // store key-value pair
    values_[key] = value;
}

std::optional<std::string> InMemoryStore::get(const std::string &key) const
{
    auto iterator = values_.find(key);
    // search for key and return its value
    if (values_.find(key) != values_.end())
    {
        return iterator->second;
    }

    // if key doesn't exist, return std::nullopt
    return std::nullopt;
}

bool InMemoryStore::remove(const std::string &key)
{
    // return true if the key exists
    if (InMemoryStore::contains(key) == true)
    {
        values_.erase(key);
        return true;
    }

    return false;
}

bool InMemoryStore::contains(const std::string &key) const
{
    return values_.find(key) != values_.end();
}

std::size_t InMemoryStore::size() const noexcept
{
    return values_.size();
}
