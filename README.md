# Overview

This is header-only library that provide `std::chrono` based timers. No external dependencies. All timers are in `flow::timer` namespace.

### Basic timer

Represented by the `flow::timer::timer` class.

Features:

1. Initialization

    Use default rep (`double`) and period (`std::ratio<1>`, which means seconds)
    ```c++
    flow::timer::timer timer;
    ```

    Specify rep and period
    ```c++
    flow::timer::timer<int, std::milli> timer;
    ```
   
2. Get elapsed duration of code fragment
   ```c++
    flow::timer::timer timer;
    // Some work here
    auto dur = timer.duration();
    ```
   
3. Get elapsed duration and return result of any callable object
   ```c++
   // unpack std::pair
   auto [elapsed, result] = flow::timer::timer<>::duration_r(
       // any callable object (like function or lambda),
       // callable object arguments...
   );
    ```
   
4. Get elapsed time of code fragment
    ```c++
    flow::timer::timer timer;
    // Some work here
    auto elapsed_time = timer.elapsed();
    ```
   
5. Get elapsed time of any callable object
   ```c++
   // unpack std::pair
   auto [elapsed, result] = flow::timer::timer<>::elapsed_r(
       // any callable object (like function or lambda),
       // callable object arguments...
   );
    ```
   
6. Get elapsed time and return result of any callable object
   ```c++
   // unpack std::pair
   auto [elapsed, result] = flow::timer::timer<>::elapsed_r(
       // any callable object (like function or lambda),
       // callable object arguments...
   );
   ```
   
7. Get average execution time
   ```c++
   auto avg = flow::timer::timer<>::avg(
       // count of iterations,
       // any callable object (like function or lambda),
       // callable object arguments...        
   );
   ```

8. Get average execution duration
   ```c++
   auto avg_dur = flow::timer::timer<>::avg_duration(
       // count of iterations,
       // any callable object (like function or lambda),
       // callable object arguments...   
   );
   ```

9. Reset the timer
    ```c++
    flow::timer::timer timer;
    // Some work here
    timer.reset();
    ```

10. Get the moment, when the timer was started (or was reset)
   ```c++
   timer.started_in();
   ```

### Auto timers

This type of timers are automatically output elapsed time in their destructors **with time units**. They have all the features of `flow::timer::timer`.

Presented by 3 classes:

* `flow::timer::basic_auto_timer` - base class for all auto timers
* `flow::timer::auto_timer` - auto timer for a stream of `char`
* `flow::timer::wauto_timer` - auto timer for a stream of `wchar_t`

Features:

1. Initialization

   ```c++
   std::ofstream ouput("output");   

   flow::timer::auto_timer auto_timer1; // use default - std::cout and empty prefix message
   flow::timer::auto_timer auto_timer2(output); // write elapsed time to output with empty prefix message
   flow::timer::auto_timer auto_timer3(std::cout, "Elapsed time is ") // write elapsed time to output with given prefix message; 
   ```
   
2. Writing time units:
   
   **Time units will be always written**.

   ```c++
   flow::timer::auto_timer<std::uintmax_t, std::milli>(std::cout, "Elapsed time is ");
   // some code here...
   ```
   
   Possible output:
   ```
   Elapsed time is 120ms
   ```
   
# Usage

Put the `flow` directory in your project and include `flow/timer.hpp`. Nothing to build.

# Requirements

C++17