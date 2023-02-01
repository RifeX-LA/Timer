# Overview

This is header-only library that provide std::chrono based timer. No external dependencies.

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
   
2. Get elapsed duration of code fragment
   ```c++
    flow::timer timer;
    // Some work here
    auto dur = timer.duration();
    ```
   
3. Get elapsed duration and return result of any callable object
   ```c++
    // unpack std::pair
   auto [elapsed, result] = flow::timer<>::duration_r(
       // Any callable object (like function or lambda),
       // Callable object arguments...
   );
    ```
   
4. Get elapsed time of code fragment
    ```c++
    flow::timer timer;
    // Some work here
    auto elapsed_time = timer.elapsed();
    ```
   
5. Get elapsed time of any callable object
   ```c++
    // unpack std::pair
   auto [elapsed, result] = flow::timer<>::elapsed_r(
       // Any callable object (like function or lambda),
       // Callable object arguments...
   );
    ```
   
6. Get elapsed time and return result of any callable object
   ```c++
   // unpack std::pair
   auto [elapsed, result] = flow::timer<>::elapsed_r(
       // Any callable object (like function or lambda),
       // Callable object arguments...
   );
   ```
   
7. Get average execution time
   ```c++
   auto avg = flow::timer<>::avg(
       // count of iterations,
       // callable object,
       // args...        
   );
   ```

8. Get average execution duration
   ```c++
   auto avg_dur = flow::timer<>::avg_duration(
       // count of iterations,
       // callable object,
       // args...        
   );
   ```

9. Reset the timer
    ```c++
    flow::timer timer;
    // Some work here
    timer.reset();
    ```

10. Get the moment, when the timer was started (or was reset)
   ```c++
   timer.started_in();
   ```
   
# Usage

Put the `flow` directory in your project and include `flow/timer.hpp`. Nothing to build.

# Requirements

C++17