#include <iostream>
#include <vector>
#include <flow/timer.hpp>

void fill_vector(std::vector<int>& v) {
    std::generate(v.begin(), v.end(), rand);
}

void sort_vector(std::vector<int>& v) {
    std::sort(v.begin(), v.end());
}

int main() {
    flow::timer timer;
    std::vector<int> v(100'000'000);
    std::cout << "Create vector time: " << timer.elapsed() << " sec\n";

    timer.reset();
    fill_vector(v);
    std::cout << "Fill vector time: " << timer.elapsed() << " sec\n";

    std::cout << "Sort vector time: " << flow::timer<std::chrono::milliseconds>::duration(sort_vector, v) << " ms";

    return 0;
}
