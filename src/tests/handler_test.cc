#include <gtest/gtest.h>

#include "../model/Parcer/Parcer.h"
#include "../model/Handler/Handler.h"
#include <sstream>
#include <fstream>

TEST(Handler, EventHandle_1) {
    Parcer parcer("resources/valid/test0_input.txt");
    Data data = parcer.GetData();
    Handler handler(data);
    std::string handler_out = handler.EventHandle();
    std::ifstream file("resources/valid/test0_output.txt");
    std::stringstream ss;
    ss << file.rdbuf();
    std::string expected_out = ss.str();
    EXPECT_TRUE(handler_out.compare(expected_out));
}

