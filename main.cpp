#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> queue;

void push(){
    for (int i = 0; i < 10000; ++i){
        std::unique_lock<std::mutex> lock(mtx);
        queue.push(i);
        std::cout<<"Pushed : "<<i<<std::endl;
        cv.notify_one();
    }
}
void pop(){
    while (true){
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] {return !queue.empty();});
        int val = queue.front();
        queue.pop();
        std::cout<<"Popped : "<<val<<std::endl;
    }
}
int main(){
    std::jthread t1(push);
    std::jthread t2(pop);
    
    return 0;
}