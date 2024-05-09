#include "Parcer.h"
int main() {
    Parcer parcer("/home/argoniaz/YADROtest/src/resources/text_file.txt");
    try {
    Data data = parcer.GetData();
    std::cout << data.count_tables << std::endl;
    std::cout << data.start << " " << data.end << std::endl;
    std::cout << data.price_per_hour << std::endl;
    for (auto i : data.logs) {
        std::cout << i.time << " " << i.id << " " << i.body << " " << i.table << std::endl;
    }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}