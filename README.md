# Overview

This is header-only timer to get code's execution time

# Usage

1. Initialization

    Use default duration (seconds)
    ```c++
    flow::timer timer;
    ```

    Specify the duration
    ```c++
    flow::timer<std::chrono::milliseconds> timer;
    ```
   
2. Get elapsed time
    ```c++
    flow::timer timer;
    // Your code here
    auto elapsed_time = timer.elapsed();
    ```
   or
    ```c++
    auto elapsed_time = flow::timer<>::duration(
    // Any callable object (for example function),
    // Callable object arguments...        
    );
    ```
3. Reset the timer
    ```c++
    flow::timer timer;
    // Some work here
    timer.reset();
    ```

# Requirements

C++17