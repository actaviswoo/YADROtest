#include <gtest/gtest.h>

#include "../model/Parcer/Parcer.h"

TEST(Parcer, ValidTest) {
    Parcer parcer("resources/text_file.txt");
    EXPECT_NO_THROW(parcer.GetData());
}

TEST(Parcer, NoPermission) {
    EXPECT_THROW(Parcer parcer("resources/invalid/test0.txt"), std::runtime_error);
}

TEST(Parcer, CountInvalid_1) {
    Parcer parcer("resources/invalid/test1.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, CountInvalid_2) {
    Parcer parcer("resources/invalid/test2.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, StartInvalid_1) {
    Parcer parcer("resources/invalid/test3.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, StartInvalid_2) {
    Parcer parcer("resources/invalid/test4.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, EndInvalid_1) {
    Parcer parcer("resources/invalid/test5.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, EndInvalid_2) {
    Parcer parcer("resources/invalid/test6.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, PriceInvalid_1) {
    Parcer parcer("resources/invalid/test7.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, PriceInvalid_2) {
    Parcer parcer("resources/invalid/test8.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_1) {
    Parcer parcer("resources/invalid/test9.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_2) {
    Parcer parcer("resources/invalid/test10.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_3) {
    Parcer parcer("resources/invalid/test11.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error); 
}

TEST(Parcer, LogInvalid_4) {
    Parcer parcer("resources/invalid/test12.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_5) {
    Parcer parcer("resources/invalid/test13.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_6) {
    Parcer parcer("resources/invalid/test14.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_7) {
    Parcer parcer("resources/invalid/test15.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_8) {
    Parcer parcer("resources/invalid/test16.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}

TEST(Parcer, LogInvalid_9) {
    Parcer parcer("resources/invalid/test17.txt");
    EXPECT_THROW(parcer.GetData(), std::runtime_error);
}



