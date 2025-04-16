#include <chrono>
#include <iostream>
#include <vector>

#include "scheduling/scheduling.hpp"

// Function prototypes
int Fibonacci_Scheduling(scheduling::ThreadPool &thread_pool, const int n);
void Linear_Chain_Scheduling(int n);
void Matrix_Mul_Scheduling(int size);

int main(int argc, char **argv) {
  // Create the ThreadPool and the tasks lists
  scheduling::ThreadPool thread_pool;
  std::vector<scheduling::Task> tasks;

  // Reserves space for 3 tasks
  tasks.reserve(3);

  int fibNum;

  // Task to read in a Fibonacci Number
  auto &get_fibNum = tasks.emplace_back([&] {
    std::cout << "Enter a number: ";
    std::cin >> fibNum;
  });

  // Task to calculate the Fibonacci number
  auto &calc_fib = tasks.emplace_back([&] {
    fibNum = Fibonacci_Scheduling(thread_pool, fibNum);
    std::cout << "Fibonacci number: " << fibNum << std::endl;
  });

  // Task to print the Fibonacci number
  calc_fib.Succeed(&get_fibNum);
  thread_pool.Submit(tasks);
  thread_pool.Wait();

  return 0;
}

/*
  Warning:
    If Wait is called recursively, as shown below, the stack depth can be
    exceeded
*/
// Fibonacci function
int Fibonacci_Scheduling(scheduling::ThreadPool &thread_pool, const int n) {
  if (n < 2) {
    return 1;
  }

  int a, b;
  std::atomic counter{0};

  thread_pool.Submit([&, n] {
    a = Fibonacci_Scheduling(thread_pool, n - 1);
    counter.fetch_add(1);
  });

  thread_pool.Submit([&, n] {
    b = Fibonacci_Scheduling(thread_pool, n - 2);
    counter.fetch_add(1);
  });

  thread_pool.Wait([&] { return counter.load() == 2; });
  return a + b;
}

// Linear chain function
void Linear_Chain_Scheduling(int n) {}

// Matrix multiplication
void Matrix_Mul_Scheduling(int size) {}