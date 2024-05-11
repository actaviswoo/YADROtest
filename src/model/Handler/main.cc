#include "Handler.h"
#include "../Parcer/Parcer.h"
int main() {
    Parcer Parcer("/home/argoniaz/YADROtest/src/resources/text_file.txt");
    Data data;
    try {
    data = Parcer.GetData();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    Handler Handler(data);
    Handler.EventHandle();
}