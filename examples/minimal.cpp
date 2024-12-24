#include <uva/drawing.hpp>

#include <chrono>
#include <iostream>

int main() {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    uva::drawing::memory_surface surface(4000, 4000);
    uva::drawing::software_renderer renderer(surface);

    renderer.clear(uva::color(0, 255, 0));

    std::filesystem::path path = std::filesystem::current_path();
    surface.write_to_file(path, "output");

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << "Duration: " << duration.count() << " seconds" << std::endl;

    return 0;
}