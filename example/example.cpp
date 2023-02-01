#include <iostream>
#include <vector>
#include <flow/timer.hpp>

std::vector<int> create_vector(std::size_t size) {
    return std::vector<int>(size);
}

void fill_vector(std::vector<int>& v) {
    std::generate(v.begin(), v.end(), rand);
}

void sort_vector(std::vector<int>& v) {
    std::sort(v.begin(), v.end());
}

int main() {
    flow::timer timer;
    std::vector<int> empty_vector;
    std::cout << "Create empty vector time: " << timer.elapsed() << " sec\n";

    auto [elapsed_time, vector] = flow::timer<>::elapsed_r(create_vector, 100'000'000);
    std::cout << "Create vector with 100'000'000 elements time: " << elapsed_time << " sec\n";

    auto avg_creation_time = flow::timer<>::avg(10, create_vector, 100'000'000);
    std::cout << "Create vector with 100'000'000 elements average time (10 iterations): " << avg_creation_time << " sec\n";

    timer.reset();
    fill_vector(vector);
    std::cout << "Fill vector time: " << timer.elapsed() << " sec\n";

    std::cout << "Sort vector time: " << flow::timer<int, std::milli>::elapsed(sort_vector, vector) << " ms";

    return 0;
}
