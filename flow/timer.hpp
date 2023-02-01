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
        using duration_t = std::chrono::duration<rep, period>;
        using clock_t = std::chrono::steady_clock;

        timer() : m_start(clock_t::now()) {}

        /**
         * @brief returns elapsed duration
         */
        [[nodiscard]] std::chrono::duration<rep, period> duration() const {
            return std::chrono::duration_cast<duration_t>(clock_t::now() - m_start);
        }

        /**
         * @brief returns elapsed time
         */
        [[nodiscard]] rep elapsed() const {
            return duration().count();
        }

        /**
         * @brief returns callable's execution duration
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static duration_t duration(Callable&& callable, Args&&... args) {
            flow::timer<rep, period> timer;
            std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
            return timer.duration();
        }

        /**
         * @brief returns pair contains callable's execution duration and callable's invoke result
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static std::pair<duration_t, std::invoke_result_t<Callable, Args...>> duration_r(Callable&& callable, Args&&... args) {
            static_assert(!std::is_void_v<std::invoke_result_t<Callable, Args...>>, "Callable's invoke result must not be void");

            flow::timer<rep, period> timer;
            auto&& result = std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
            auto dur = timer.duration();

            return {std::move(dur), std::forward<decltype(result)>(result)};
        }

        /**
         * @brief returns callable's execution time
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static rep elapsed(Callable&& callable, Args&&... args) {
            return duration(std::forward<Callable>(callable), std::forward<Args>(args)...).count();
        }

        /**
         * @brief returns pair contains callable's execution time and callables' invoke result
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static std::pair<rep, std::invoke_result_t<Callable, Args...>> elapsed_r(Callable&& callable, Args&&... args) {
            auto&& [dur, result] = duration_r(std::forward<Callable>(callable), std::forward<Args>(args)...);
            return {dur.count(), std::forward<decltype(result)>(result)};
        }

        /**
         * @brief executes <b>callable</b> <b>count</b> times and returns the average execution duration
         * @param count count of iterations
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static std::chrono::duration<rep, period> avg_duration(std::size_t count, Callable&& callable, Args&&... args) {
            std::chrono::duration<rep, period> total;
            for (std::size_t i = 0; i < count; ++i) {
                total += duration(std::forward<Callable>(callable), std::forward<Args>(args)...);
            }

            return total / static_cast<rep>(count);
        }

        /**
         * @brief executes <b>callable</b> <b>count</b> times and returns the average execution time
         * @param count count of iterations
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static rep avg(std::size_t count, Callable&& callable, Args&&... args) {
            return avg_duration(count, std::forward<Callable>(callable), std::forward<Args>(args)...).count();
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
        [[nodiscard]] clock_t::time_point started_in() noexcept {
            return m_start;
        }

    private:
        clock_t::time_point m_start;
    };

} // namespace flow
