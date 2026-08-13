#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex lock;
std::atomic<int> sharedJob{0};

int calculateSumValue(const std::vector<int>& numbers)
{
    int sum{};

    for (auto number : numbers)
        sum += number;

    return sum;
}

void calculateSquareValue(int number, std::vector<int>& results)
{
    int result = number * number;

    {
        std::lock_guard guard(lock);

        results.push_back(result);

        std::cout
            << "Thread " << std::this_thread::get_id()
            << " calculated "
            << number << " * " << number
            << " = " << result
            << std::endl;
    }
}

void workerFunction(const std::vector<int>& numbers,
                    std::vector<int>& results)
{
    while (true)
    {
        int index = sharedJob++;

        if (index >= numbers.size())
            break;

        calculateSquareValue(numbers[index], results);
    }
}

int main()
{
    std::vector<std::jthread> jThreads;

    std::vector<int> numbers = {
        5, 8, 12, 20, 3, 7, 11, 15
    };

    std::vector<int> results;

    for (int i = 0; i < 2; i++)
    {
        jThreads.emplace_back(
            workerFunction,
            std::cref(numbers),
            std::ref(results)
        );
    }

    for (auto& jThread : jThreads)
    {
        jThread.join();
    }

    std::cout
        << "Sum = "
        << calculateSumValue(results)
        << std::endl;
}
