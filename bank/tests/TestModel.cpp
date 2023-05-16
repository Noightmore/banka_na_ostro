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

// Test case for removing a logged-in user
TEST(BankDataTest, RemoveLoggedInUser) {
        // Create a BankData object
        auto bankData = BankData::createInstance();

        // create a new user account with a password of "password123"
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        // create a new user account with a password of "password123"
        std::unique_ptr<bank::data::models::UserAccount> user2 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(2),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        // create a new user account with a password of "password123"
        std::unique_ptr<bank::data::models::UserAccount> user3 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(3),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        bankData->addLoggedInUser(user1.release());
        bankData->addLoggedInUser(user2.release());
        bankData->addLoggedInUser(user3.release());

        // Remove a logged-in user
        ASSERT_NO_THROW(bankData->removeLoggedInUser(2));

        // Verify that the user is removed from the logged-in users list
        //EXPECT_EQ(bankData.getLoggedInUsersCount(), 2);
        ASSERT_ANY_THROW(bankData->getLoggedInUserAccount_ById(2));
}

// Test case for removing a non-existing logged-in user
TEST(BankDataTest, RemoveNonExistingLoggedInUser) {
        // Create a BankData object
        auto bankData = BankData::createInstance();

        // create a new user account with a password of "password123"
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        bankData->addLoggedInUser(user1.release());

        // Attempt to remove a non-existing logged-in user
        ASSERT_THROW(bankData->removeLoggedInUser(2), std::invalid_argument);

        ASSERT_NO_THROW(bankData->getLoggedInUserAccount_ById(1));
}

// Test case for checking if the user has sufficient funds for a currency
TEST(UserAccountTest, HasSufficientFundsForCurrency) {
        // create a new user account with a password of "password123"
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );

        // Add a currency balance to the user's account
        std::string currencyName = "USD";
        double amount = 100.0;

        auto balance1 = Balance::createInstance(
                std::make_unique<std::string>(currencyName),
                std::make_unique<double>(amount));

        currencyName = "EUR";
        amount = 50.0;
        auto balance2 = Balance::createInstance(
                std::make_unique<std::string>(currencyName),
                std::make_unique<double>(amount));

        currencyName = "CZK";
        amount = 0;
        auto balance3 = Balance::createInstance(
                std::make_unique<std::string>(currencyName),
                std::make_unique<double>(amount));


        user1->addBalance(std::move(balance1));
        user1->addBalance(std::move(balance2));
        user1->addBalance(std::move(balance3));

        currencyName = "USD";
        // Check if the user has sufficient funds for a currency (USD)
        EXPECT_TRUE(user1->doesUserHasSufficientFunds_ForCurrency(currencyName, 75.0));

        currencyName = "EUR";
        // Check if the user has sufficient funds for a currency (EUR)
        EXPECT_TRUE(user1->doesUserHasSufficientFunds_ForCurrency(currencyName, 50.0));

        // Check if the user has sufficient funds for a currency (GBP)
        currencyName = "CZK";
        EXPECT_FALSE(user1->doesUserHasSufficientFunds_ForCurrency(currencyName, 75.0));

        // Verify that the balances are updated accordingly
        //EXPECT_DOUBLE_EQ(balance1->getAmount(), 25.0);
        //EXPECT_DOUBLE_EQ(balance2->getAmount(), 0.0);
        //EXPECT_DOUBLE_EQ(balance3->getAmount(), 0.0);
}

// Test case for adding funds to an existing balance
TEST(UserAccountTest, AddFundsToExistingBalance) {
        // create a new user account with a password of "password123"
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );

        // Add a currency balance to the user's account
        std::string currencyName = "USD";
        double amount = 100.0;

        auto balance1 = Balance::createInstance(
                std::make_unique<std::string>(currencyName),
                std::make_unique<double>(amount));

        // just save raw pointer for quick data verification
        auto balancePTR = balance1.get();
        user1->addBalance(std::move(balance1));

        // Add funds to the existing balance (USD)

        user1->addFunds(currencyName, 50.0);

        // Verify that the balance is updated accordingly
        EXPECT_DOUBLE_EQ(balancePTR->getAmount(), 150.0);
}

// Test case for adding funds to a non-existing balance
//TEST(UserAccountTest, AddFundsToNonExistingBalance) {
//        // Create a UserAccount object
//        UserAccount userAccount;
//
//        // Add a balance to the user's account
//        data::models::Balance* balance = new data::models::Balance("USD", 100.0);
//        userAccount.addBalance(balance);
//
//        // Add funds to a non-existing balance (EUR)
//        userAccount.addFunds("EUR", 50.0);
//
//        // Verify that the balance is not updated
//        EXPECT_DOUBLE_EQ(balance->getAmount(), 100.0);
//}
//
//// Test case for adding funds to an existing balance with insufficient funds
//TEST(UserAccountTest, AddFundsToExistingBalanceWithInsufficientFunds) {
//        // Create a UserAccount object
//        UserAccount userAccount;
//
//        // Add a balance to the user's account
//        data::models::Balance* balance = new data::models::Balance("USD", 100.0);
//        userAccount.addBalance(balance);
//
//        // Add funds to the existing balance (USD) with insufficient funds
//        userAccount.addFunds("USD", 150.0);
//
//        // Verify that the balance is not updated
//        EXPECT_DOUBLE_EQ(balance->getAmount(), 100.0);
//}
//
//// Test case for adding funds to multiple balances
//TEST(UserAccountTest, AddFundsToMultipleBalances) {
//        // Create a UserAccount object
//        UserAccount userAccount;
//
//        // Add multiple balances to the user's account
//        data::models::Balance* balance1 = new data::models::Balance("USD", 100.0);
//        data::models::Balance* balance2 = new data::models::Balance("EUR", 50.0);
//        data::models::Balance* balance3 = new data::models::Balance("GBP", 75.0);
//        userAccount.addBalance(balance1);
//        userAccount.addBalance(balance2);
//        userAccount.addBalance(balance3);
//
//        // Add funds to multiple balances (USD and GBP)
//        userAccount.addFunds("USD", 50.0);
//        userAccount.addFunds("GBP", 25.0);
//
//        // Verify that the balances are updated accordingly
//        EXPECT_DOUBLE_EQ(balance1->getAmount(), 150.0);
//        EXPECT_DOUBLE_EQ(balance2->getAmount(), 50.0);
//        EXPECT_DOUBLE_EQ(balance3->getAmount(), 100.0);
//}

// Test case for deleting logged-in users
TEST(BankDataTest, DeleteLoggedInUsers)
{
        // Create a BankData object
        auto bankData = BankData::createInstance();

        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        std::unique_ptr<bank::data::models::UserAccount> user2 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        bankData->addLoggedInUser(user1.release());
        bankData->addLoggedInUser(user2.release());

        // Delete the logged-in users
        bankData->deleteLoggedInUsers();

        // Verify that the logged-in users list is empty
        auto size = bankData->getLoggedInUsersSize();
        std::cout << "Size: " << size << std::endl;
        EXPECT_TRUE(size == 0);
}

// Test case for deleting current exchange rates
TEST(BankDataTest, DeleteCurrentExchangeRates)
{
        // Create a BankData object
        auto bankData = BankData::createInstance();

        auto exchangeRate1 = ExchangeRate::createInstance(
                std::make_unique<std::string>("USD"),
                std::make_unique<unsigned int>(20.0),
                std::make_unique<double>(0.85)
        );

        auto exchangeRate2 = ExchangeRate::createInstance(
                std::make_unique<std::string>("USD"),
                std::make_unique<unsigned int>(20.0),
                std::make_unique<double>(0.85)
        );

        bankData->addCurrentExchangeRate(std::move(exchangeRate1));
        bankData->addCurrentExchangeRate(std::move(exchangeRate2));

        // Delete the current exchange rates
        bankData->deleteCurrentExchangeRates();

        // Verify that the current exchange rates list is empty
        EXPECT_TRUE(bankData->getExchangeRateSize() == 0);
}

TEST(UserAccountTest, GetFirstName)
{
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        EXPECT_EQ(user1->getFirstName(), "John");
}

TEST(UserAccountTest, GetLastName)
{
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );

        EXPECT_EQ(user1->getLastName(), "Doe");
}

TEST(UserAccountTest, GetBalances)
{
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );

        const std::vector<Balance*>& balances = user1->getBalances();
        EXPECT_TRUE(balances.empty());
}

TEST(UserAccountTest, GetPayments)
{
        std::unique_ptr<bank::data::models::UserAccount> user1 = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );
        const std::vector<Payment*>& payments = user1->getPayments();
        EXPECT_TRUE(payments.empty());
}