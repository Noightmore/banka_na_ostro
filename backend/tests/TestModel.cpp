#include <gtest/gtest.h>

#include "../src/include/models/Balance.hpp"

using namespace bank::models;

TEST(BalanceTest, CreateInstance)
{
        auto name = std::make_unique<std::string>("USD");
        auto amount = std::make_unique<double>(1000);
        auto balance = Balance::createInstance(std::move(name), std::move(amount));
        ASSERT_EQ(balance->toJson(), R"({"name": "USD","amount": 1000})");
}

TEST(BalanceTest, CreateInstanceWithEmptyName)
{
        auto name = std::make_unique<std::string>("");
        auto amount = std::make_unique<double>(1000);
        ASSERT_THROW(Balance::createInstance(std::move(name), std::move(amount)), std::invalid_argument);
}

TEST(BalanceTest, CreateInstanceWithNegativeAmount)
{
        auto name = std::make_unique<std::string>("USD");
        auto amount = std::make_unique<double>(-1000);
        ASSERT_THROW(Balance::createInstance(std::move(name), std::move(amount)), std::invalid_argument);
}

