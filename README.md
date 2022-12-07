# Overview

This is header-only library that provide std::chrono based timer

Features:

1. Initialization

    Use default rep (double) and period (std::ratio<1>, which means seconds)
    ```c++
    flow::timer timer;
    ```

    Specify rep and period
    ```c++
    flow::timer<int, std::milli> timer;
    ```
   
2. Get elapsed time of code fragment
    ```c++
    flow::timer timer;
    // Some work here
    auto elapsed_time = timer.elapsed();
    ```
   
3. Get elapsed time of any callable object
   ```c++
    auto elapsed_time = flow::timer<>::duration(
        // Any callable object (like function or lambda),
        // Callable object arguments...        
    );
    ```
   
4. Get elapsed time and return result of any callable object
   ```c++
   // unpack std::pair
   auto [time, result] = flow::timer<>::duration_r(
       // Any callable object (like function or lambda),
       // Callable object arguments...
   );
   ```
5. Reset the timer
    ```c++
    flow::timer timer;
    // Some work here
    timer.reset();
    ```
   
6. Get the moment, when the timer was started (or was reset)
   ```c++
   timer.started_in();
   ```
   
# Usage

Put the `flow` directory in your project. Nothing to build

# Requirements

C++17