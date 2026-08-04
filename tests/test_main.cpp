#include <exception>
#include <iostream>
#include <string>

void runInMemoryStoreTests();
void runCommandProcessorTests();

int main()
{
    try
    {
        runInMemoryStoreTests();
        runCommandProcessorTests();

        std::cout << "\nAll tests passed.\n";
        return 0;
    }
    catch (const std::exception &exception)
    {
        std::cerr << "\nTest failed: "
                  << exception.what()
                  << '\n';

        return 1;
    }
}