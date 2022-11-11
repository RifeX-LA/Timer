#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <functional>

namespace flow {

    template <typename Duration = std::chrono::seconds>
    class timer {
    public:
        using clock_t = std::chrono::steady_clock;
        using dur = Duration;

        timer() : m_start(clock_t::now()) {}

        /**
         * @brief returns elapsed time (default in seconds)
         */
        [[nodiscard]] double elapsed() const {
            using basic_dur = std::chrono::nanoseconds;

            auto basic_elapsed = std::chrono::duration<double, basic_dur::period>(clock_t::now() - m_start).count();
            return basic_elapsed * basic_dur::period::num * dur::period::den / basic_dur::period::den / dur::period::num;
        }

        /**
         * @brief returns callable's execution time
         * @param callable any object, that can be invoked with <b>args</b>
         * @param args arguments to pass to <b>callable</b>
         */
        template <typename Callable, typename... Args>
        static double duration(Callable&& callable, Args&&... args) {
            flow::timer<dur> t;
            std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
            return t.elapsed();
        }

        /**
         * @brief resets the timer
         */
        void reset() noexcept {
            m_start = clock_t::now();
        }

    private:
        clock_t::time_point m_start;
    };

}

#endif //TIMER_HPP
