#pragma once

#include <iostream>
#include <flow/timer/timer.hpp>
#include <flow/timer/time_unit.hpp>

namespace flow::timer {

    /***
     * @brief std::chrono based auto timer for ostreams of <b>CharT</b> with traits <b>Traits</b>
     * @tparam Rep - an arithmetic type representing the number of ticks
     * @tparam Period - <b>std::ratio</b> representing the tick period
     */
    template <typename Rep, typename Period, typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_auto_timer : public timer<Rep, Period> {
    protected:
        std::basic_ostream<CharT, Traits>& m_os;
        const std::basic_string_view<CharT, Traits> m_prefix;

    public:
        basic_auto_timer(std::basic_ostream<CharT, Traits>& os, std::basic_string_view<CharT, Traits> prefix)
        noexcept: m_os(os), m_prefix(prefix) {};

        ~basic_auto_timer() {
            static constexpr auto time_unit = get_time_unit<Period, CharT>();
            const auto elapsed_time = this->elapsed();
            this->m_os << this->m_prefix << elapsed_time << time_unit;
        }
    };

    /***
     * @brief std::chrono based auto timer for ostreams of <b>char</b>
     * @tparam Rep - an arithmetic type representing the number of ticks
     * @tparam Period - <b>std::ratio</b> representing the tick period
     */
    template <typename Rep = double, typename Period = std::ratio<1>>
    class auto_timer : public basic_auto_timer<Rep, Period, char> {
        using base_t = basic_auto_timer<Rep, Period, char>;

    public:
        explicit auto_timer(std::ostream& os = std::cout, std::string_view prefix = "") noexcept : base_t(os, prefix) {}
    };

    /***
     * @brief std::chrono based auto timer for ostreams of <b>wchar_t</b>
     * @tparam Rep - an arithmetic type representing the number of ticks
     * @tparam Period - <b>std::ratio</b> representing the tick period
     */
    template <typename Rep = double, typename Period = std::ratio<1>>
    class wauto_timer : public basic_auto_timer<Rep, Period, wchar_t> {
        using base_t = basic_auto_timer<Rep, Period, wchar_t>;

    public:
        explicit wauto_timer(std::wostream& os = std::wcout, std::wstring_view prefix = L"") noexcept : base_t(os, prefix) {}
    };

} // namespace flow::timer
