#pragma once

#include <chrono>
#include <functional>

namespace flow::timer {

    /**
     * @brief std::chrono based timer
     * @tparam Rep - an arithmetic type representing the number of ticks
     * @tparam Period - <b>std::ratio</b> representing the tick period
     */
    template <typename Rep = double, typename Period = std::ratio<1>>
    class timer {
    public:
        using rep_type = Rep;
        using period_type = Period;
        using duration_type = std::chrono::duration<rep_type, period_type>;
        using clock_type = std::chrono::steady_clock;

        timer() : m_start(clock_type::now()) {}

        /**
         * @brief returns elapsed duration
         */
        [[nodiscard]] std::chrono::duration<rep_type, period_type> duration() const {
            return std::chrono::duration_cast<duration_type>(clock_type::now() - m_start);
        }

        /**
         * @brief returns elapsed time
         */
        [[nodiscard]] rep_type elapsed() const {
            return duration().count();
        }

        /**
         * @brief returns callable's execution duration
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static duration_type duration(Callable&& callable, Args&&... args) {
            flow::timer::timer<rep_type, period_type> timer;
            std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
            return timer.duration();
        }

        /**
         * @brief returns pair contains callable's execution duration and callable's invoke result
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static std::pair<duration_type, std::invoke_result_t<Callable, Args...>> duration_r(Callable&& callable, Args&&... args) {
            static_assert(!std::is_void_v<std::invoke_result_t<Callable, Args...>>, "Callable's invoke result must not be void");

            flow::timer::timer<rep_type, period_type> timer;
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
        static rep_type elapsed(Callable&& callable, Args&&... args) {
            return duration(std::forward<Callable>(callable), std::forward<Args>(args)...).count();
        }

        /**
         * @brief returns pair contains callable's execution time and callables' invoke result
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static std::pair<rep_type, std::invoke_result_t<Callable, Args...>> elapsed_r(Callable&& callable, Args&&... args) {
            auto&& [dur, result] = duration_r(std::forward<Callable>(callable), std::forward<Args>(args)...);
            return {dur.count(), std::forward<decltype(result)>(result)};
        }

        /**
         * @brief executes <b>callable</b> object <b>count</b> times and returns the average execution duration
         * @param count count of iterations
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static duration_type avg_duration(std::size_t count, Callable&& callable, Args&&... args) {
            duration_type total{};
            for (std::size_t i = 0; i < count; ++i) {
                total += duration(std::forward<Callable>(callable), std::forward<Args>(args)...);
            }

            return total / static_cast<rep_type>(count);
        }

        /**
         * @brief executes <b>callable</b> <b>count</b> times and returns the average execution time
         * @param count count of iterations
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static rep_type avg_elapsed(std::size_t count, Callable&& callable, Args&&... args) {
            return avg_duration(count, std::forward<Callable>(callable), std::forward<Args>(args)...).count();
        }

        /**
         * @brief resets the timer
         */
        void reset() noexcept {
            m_start = clock_type::now();
        }

        /**
         * @brief returns the time point, from which the timer started counting
         */
        [[nodiscard]] clock_type::time_point started_in() noexcept {
            return m_start;
        }

    private:
        clock_type::time_point m_start;
    };

} // namespace flow::timer
