#include <gtest/gtest.h>

#include "../src/include/models/Balance.hpp"
#include "../src/include/models/BankData.hpp"
#include "../src/include/models/ExchangeRate.hpp"
#include "../src/include/models/UserAccount.hpp"

using namespace bank::models;

// BALANCE CLASS TESTS
TEST(BalanceTest, CreateInstance)
{
        auto name = std::make_unique<std::string>("USD");
        auto amount = std::make_unique<double>(1000.000000);
        auto balance = Balance::createInstance(std::move(name), std::move(amount));
        ASSERT_EQ(balance->toJson(), R"({"name": "USD","amount": 1000.000000})");
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

TEST(ExchangeRateTest, CreateInstance)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        std::unique_ptr<ExchangeRate> exRate = ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate));
        EXPECT_EQ(exRate->getName(), "USD");
        EXPECT_EQ(exRate->getAmount(), 1);
        EXPECT_EQ(exRate->getRate(), 25.0);
}

TEST(ExchangeRateTest, CreateInstanceWithNullName)
{
        std::unique_ptr<std::string> name = nullptr;
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)), std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithNullAmount)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = nullptr;
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)), std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithNullRate)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = nullptr;
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)), std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithEmptyName)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)), std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithZeroAmount)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(0);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)), std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithZeroRate)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)), std::invalid_argument);
}



