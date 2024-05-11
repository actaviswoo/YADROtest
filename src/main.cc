#include "model/Handler/Handler.h"
#include "model/Parcer/Parcer.h"
#include <iostream>
int main(int argc, char* argv[]) {
    if (argc < 1) return 0;
    std::string filename = argv[1];
    try {
        Parcer parcer(filename);
        Data data = parcer.GetData();
        Handler handler(data);
        std::cout << handler.EventHandle();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}