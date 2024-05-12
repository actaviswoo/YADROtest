#include <gtest/gtest.h>

#include "../model/Format/Format.h"
#include <sstream>
#include <fstream>

TEST(Format, IsValidTime) {
    EXPECT_TRUE(Format::IsValidTime("00:00"));
    EXPECT_TRUE(Format::IsValidTime("00:01"));
    EXPECT_TRUE(Format::IsValidTime("01:00"));
    EXPECT_TRUE(Format::IsValidTime("01:40"));
    EXPECT_TRUE(Format::IsValidTime("14:15"));
    EXPECT_FALSE(Format::IsValidTime("25:00"));
    EXPECT_FALSE(Format::IsValidTime("00:61"));
    EXPECT_FALSE(Format::IsValidTime("0:0"));
    EXPECT_FALSE(Format::IsValidTime("aa:aa"));
    EXPECT_FALSE(Format::IsValidTime("a"));
}

TEST(Format, CompareTime) {
    EXPECT_FALSE(Format::CompareTime("01:00", "00:00"));
    EXPECT_FALSE(Format::CompareTime("05:11", "05:10"));
    EXPECT_TRUE(Format::CompareTime("00:00", "00:00"));
    EXPECT_TRUE(Format::CompareTime("00:00", "01:00"));
    EXPECT_TRUE(Format::CompareTime("05:10", "05:11"));
}

TEST(Format, IsValidName) {
    EXPECT_TRUE(Format::IsValidName("client1"));
    EXPECT_TRUE(Format::IsValidName("c_lient2-a"));
    EXPECT_FALSE(Format::IsValidName("()"));
    EXPECT_FALSE(Format::IsValidName("{{{}}}"));
    EXPECT_FALSE(Format::IsValidName("фввфвы"));
}

TEST(Format, GetHour) {
    EXPECT_TRUE(Format::GetHour("01:00") == 1);
    EXPECT_TRUE(Format::GetHour("02:00") == 2);
    EXPECT_TRUE(Format::GetHour("03:44") == 3);
    EXPECT_TRUE(Format::GetHour("22:00") == 22);
}

TEST(Format, GetMinute) {
    EXPECT_TRUE(Format::GetMinute("01:01") == 1);
    EXPECT_TRUE(Format::GetMinute("02:02") == 2);
    EXPECT_TRUE(Format::GetMinute("03:44") == 44);
    EXPECT_TRUE(Format::GetMinute("22:00") == 0);
}

TEST(Format, SumTime) {
    EXPECT_TRUE(Format::SumTime("01:00", "02:33") == "03:33");
    EXPECT_TRUE(Format::SumTime("01:59", "02:01") == "04:00");
    EXPECT_TRUE(Format::SumTime("00:30", "00:30") == "01:00");
    EXPECT_TRUE(Format::SumTime("", "00:30") == "");
    EXPECT_TRUE(Format::SumTime("00:30", "") == "");
}

TEST(Format, DiffTime) {
    EXPECT_TRUE(Format::DiffTime("01:30", "00:30") == "01:00");
    EXPECT_TRUE(Format::DiffTime("01:00", "00:30") == "00:30");
    EXPECT_TRUE(Format::DiffTime("00:30", "00:30") == "00:00");
    EXPECT_TRUE(Format::DiffTime("", "00:30") == "");
    EXPECT_TRUE(Format::DiffTime("00:30", "") == "");
}







