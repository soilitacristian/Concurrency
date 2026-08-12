#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex lock;
static int counterValue = 100;
void updateCounterValue() {
  lock.lock();
    counterValue += 1;
    std::cout << "counterValue: " << counterValue << std::endl;
  lock.unlock();
}

int main() {
  
auto lambda =[](int x) {
  std::cout<<"Hello from thread "<<std::this_thread::get_id()<<std::endl;
  std::cout<<"Argument passed in : "<<x<<std::endl;
};
  std::vector<std::jthread> jThreads;
  for (int i = 0; i < 10; i++) {
    jThreads.emplace_back(updateCounterValue);
  }
  for (auto& jThread : jThreads) {
    jThread.join();
  }
  std::cout<<"Hello from main thread"<<std::endl;
  return 0;
}
