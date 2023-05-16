#include <gtest/gtest.h>

#include "../bank/include/data/models/Balance.hpp"
#include "../bank/include/data/models/BankData.hpp"

using namespace bank::data::models;

// BALANCE CLASS TESTS
//TEST(BalanceTest, CreateInstance)
//{
//        auto name = std::make_unique<std::string>("USD");
//        auto amount = std::make_unique<double>(1000.000000);
//        auto balance = Balance::createInstance(std::move(name), std::move(amount));
//        ASSERT_EQ(balance->toJson(), R"({"name": "USD","amount": 1000.000000})");
//}

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

// EXCHANGE RATE TESTS
TEST(ExchangeRateTest, CreateInstance)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        std::unique_ptr<ExchangeRate> exRate = ExchangeRate::createInstance(std::move(name),
                                                                            std::move(amount),
                                                                            std::move(rate));
        EXPECT_EQ(exRate->getName(), "USD");
        EXPECT_EQ(exRate->getAmount(), 1);
        EXPECT_EQ(exRate->getRate(), 25.0);
}

TEST(ExchangeRateTest, CreateInstanceWithNullName)
{
        std::unique_ptr<std::string> name = nullptr;
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)),
                     std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithNullAmount)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = nullptr;
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)),
                     std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithNullRate)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = nullptr;
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)),
                     std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithEmptyName)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)),
                     std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithZeroAmount)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(0);
        std::unique_ptr<double> rate = std::make_unique<double>(25.0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)),
                     std::invalid_argument);
}

TEST(ExchangeRateTest, CreateInstanceWithZeroRate)
{
        std::unique_ptr<std::string> name = std::make_unique<std::string>("USD");
        std::unique_ptr<unsigned int> amount = std::make_unique<unsigned int>(1);
        std::unique_ptr<double> rate = std::make_unique<double>(0);
        EXPECT_THROW(ExchangeRate::createInstance(std::move(name), std::move(amount), std::move(rate)),
                     std::invalid_argument);
}

// USER ACCOUNT TESTS

// Test case for correct password
TEST(UserAccountTest, CorrectPassword)
{
        // create a new user account with a password of "password123"
        std::unique_ptr<UserAccount> user = UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );

        std::string password = "password123";
        // check if the password matches
        EXPECT_TRUE(user->doPasswordsMatch(password));
}

// Test case for incorrect password
TEST(UserAccountTest, IncorrectPassword)
{
        // create a new user account with a password of "password123"
        std::unique_ptr<UserAccount> user = UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );

        std::string password = "wrongpassword";
        // check if the password matches
        EXPECT_FALSE(user->doPasswordsMatch(password));
}


// Test case for existing currency account
TEST(UserAccountTest, DoesUserOwnAccount_ForExistingCurrency)
{
        // Create a UserAccount object
        auto user = UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("mail@example.com"),
                std::make_unique<std::string>("password123"));

        // Add a currency balance to the user's account
        std::string currencyName = "USD";
        double amount = 100.0;

        auto balance = Balance::createInstance(
                std::make_unique<std::string>(currencyName),
                std::make_unique<double>(amount));

        user->addBalance(std::move(balance));

        // Call the function under test
        bool result = user->doesUserOwnAccount_ForCurrency(currencyName);

        // Assert that the user owns the currency account
        EXPECT_TRUE(result);
}

// Test case for non-existing currency account
TEST(UserAccountTest, DoesUserOwnAccount_ForNonExistingCurrency)
{
        // Create a UserAccount object
        auto user = UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("mail@example.com"),
                std::make_unique<std::string>("password123"));

        // Add a currency balance to the user's account
        std::string currencyName = "USD";
        double amount = 100.0;

        auto balance = Balance::createInstance(
                std::make_unique<std::string>(currencyName),
                std::make_unique<double>(amount));

        user->addBalance(std::move(balance));

        // Call the function under test with a different currency name
        std::string faulty_silly_currency = "EUR";
        bool result = user->doesUserOwnAccount_ForCurrency(faulty_silly_currency);

        // Assert that the user does not own the currency account
        EXPECT_FALSE(result);
}

// Test case for an empty account
TEST(UserAccountTest, DoesUserOwnAccount_ForEmptyAccount)
{
        // Create a UserAccount object
        auto user = UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("mail@example.com"),
                std::make_unique<std::string>("password123"));

        // Call the function under test

        std::string faulty_silly_currency = "EUR";
        bool result = user->doesUserOwnAccount_ForCurrency(faulty_silly_currency);

        // Assert that the user does not own the currency account
        EXPECT_FALSE(result);
}
