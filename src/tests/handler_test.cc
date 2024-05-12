#include <gtest/gtest.h>

#include "../model/Parcer/Parcer.h"
#include "../model/Handler/Handler.h"
#include <sstream>
#include <fstream>

bool EventHandle(const std::string& input, const std::string& output) {
    Parcer parcer(input);
    Data data = parcer.GetData();
    Handler handler(data);
    std::string handler_out = handler.EventHandle();
    std::ifstream file(output);
    std::stringstream ss;
    ss << file.rdbuf();
    std::string expected_out = ss.str();
    file.close();
    return !handler_out.compare(expected_out);
}

TEST(Handler, EventHandle_0) {
    EXPECT_TRUE(EventHandle("resources/valid/test0_input.txt", "resources/valid/test0_output.txt"));
}

TEST(Handler, EventHandle_1) {
    EXPECT_TRUE(EventHandle("resources/valid/test1_input.txt", "resources/valid/test1_output.txt"));
}

TEST(Handler, EventHandle_2) {
    EXPECT_TRUE(EventHandle("resources/valid/test2_input.txt", "resources/valid/test2_output.txt"));
}

TEST(Handler, EventHandle_3) {
    EXPECT_TRUE(EventHandle("resources/valid/test3_input.txt", "resources/valid/test3_output.txt"));
}

TEST(Handler, EventHandle_4) {
    EXPECT_TRUE(EventHandle("resources/valid/test4_input.txt", "resources/valid/test4_output.txt"));
}

TEST(Handler, EventHandle_5) {
    EXPECT_TRUE(EventHandle("resources/valid/test5_input.txt", "resources/valid/test5_output.txt"));
}

TEST(Handler, EventHandle_6) {
    EXPECT_TRUE(EventHandle("resources/valid/test6_input.txt", "resources/valid/test6_output.txt"));
}


