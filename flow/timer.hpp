#pragma once

#include <chrono>
#include <functional>

namespace flow {

    /**
     * @brief std::chrono based timer
     * @tparam Rep - an arithmetic type representing the number of ticks
     * @tparam Period - <b>std::ratio</b> representing the tick period
     */
    template <typename Rep = double, typename Period = std::ratio<1>>
    class timer {
    public:
        using rep = Rep;
        using period = Period;
        using clock_t = std::chrono::steady_clock;

        timer() : m_start(clock_t::now()) {}

        /**
         * @brief returns elapsed time
         */
        [[nodiscard]] rep elapsed() const {
            using to_dur = std::chrono::duration<rep, period>;

            return std::chrono::duration_cast<to_dur>(clock_t::now() - m_start).count();
        }

        /**
         * @brief returns callable's execution time
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static rep duration(Callable&& callable, Args&&... args) {
            flow::timer<rep, period> timer;
            std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
            return timer.elapsed();
        }

        /**
         * @brief returns pair contains callable's execution time and callables' invoke result
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static std::pair<rep, std::invoke_result_t<Callable, Args...>> duration_r(Callable&& callable, Args&&... args) {
            static_assert(!std::is_void_v<std::invoke_result_t<Callable, Args...>>, "Callable's invoke result must not be void");

            flow::timer<rep, period> timer;
            auto&& result = std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
            auto elapsed_time = timer.elapsed();

            return {elapsed_time, std::forward<decltype(result)>(result)};
        }

        /**
         * @brief resets the timer
         */
        void reset() noexcept {
            m_start = clock_t::now();
        }

        /**
         * @brief returns the time point, from which the timer started counting
         */
        clock_t::time_point started_in() noexcept {
            return m_start;
        }

    private:
        clock_t::time_point m_start;
    };

} //namespace flow
