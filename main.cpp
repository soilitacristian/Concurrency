#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

static std::atomic<int> counterValue = 0;

void updateCounterValue() {
  std::cout << "counterValue: " << counterValue << std::endl;
}

int main() {

  auto lambda = [](int x) {
    std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
    std::cout << "Argument passed in : " << x << std::endl;
  };
  std::vector<std::jthread> jThreads;
  for (int i = 0; i < 10; i++) {
    jThreads.emplace_back(updateCounterValue);
  }
  for (auto &jThread : jThreads) {
    jThread.join();
  }
  std::cout << "Hello from main thread" << std::endl;
  return 0;
}
