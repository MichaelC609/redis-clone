#include <command_processor.h>
#include <in_memory_store.h>

#include <iostream>
#include <string>

int main()
{
    InMemoryStore store;
    CommandProcessor commandProcessor(store);

    std::cout << "Redis CLI\n";
    std::cout << "Type EXIT to stop the server.\n\n";

    std::string input;

    while (true)
    {
        std::cout << "<Redis> ";

        if (!std::getline(std::cin, input))
        {
            break;
        }

        if (input == "EXIT" || input == "exit")
        {
            break;
        }

        const std::string response = commandProcessor.execute(input);

        if (!response.empty())
        {
            std::cout << response << '\n';
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}