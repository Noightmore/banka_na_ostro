#include "include/services/BusinessLogic.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(BusinessLogicTest, GetParsedUrlReturnsCorrectValue)
{
        // Arrange
        bank::services::BusinessLogic bl;
        std::string query = "param=123";

        // Act
        int result = bl.getParsedUrl(query);

        // Assert
        EXPECT_EQ(result, 123);
}

TEST(BusinessLogicTest, GetParsedUrlThrowsExceptionIfDelimiterIsMissing)
{
        // Arrange
        bank::services::BusinessLogic bl;
        std::string query = "param123";

        // Act and Assert
        EXPECT_THROW(bl.getParsedUrl(query), std::invalid_argument);
}

TEST(BusinessLogicTest, GetParsedUrlThrowsExceptionIfDelimiterIsAtBeginningOfString)
{
        // Arrange
        bank::services::BusinessLogic bl;
        std::string query = "=123param";

        // Act and Assert
        EXPECT_THROW(bl.getParsedUrl(query), std::invalid_argument);
}

TEST(BusinessLogicTest, GetParsedUrlThrowsExceptionIfDelimiterIsAtEndOfString)
{
        // Arrange
        bank::services::BusinessLogic bl;
        std::string query = "param123=";

        // Act and Assert
        EXPECT_THROW(bl.getParsedUrl(query), std::invalid_argument);
}

TEST(BusinessLogicTest, GetParsedUrlThrowsExceptionIfTokenIsNotANumber)
{
        // Arrange
        bank::services::BusinessLogic bl;
        std::string query = "param=abc";

        // Act and Assert
        EXPECT_THROW(bl.getParsedUrl(query), std::invalid_argument);
}

// Test case for fetching host IP address successfully
TEST(BusinessLogicTest, FetchHostIpAddress_Success)
{
        bank::services::BusinessLogic businessLogic;
        // Mock the necessary dependencies if required
        // Call the fetchHostIpAddress method
        ASSERT_NO_THROW({
                                businessLogic.fetchHostIpAddress();
                        });
        // Add assertions to check if the expected host IP address is set
        // ASSERT_... statements to check the expected behavior
}

// CANNOT MOCK SYSTEM FUNCTION TO PROVIDE WRONG DATA
// Test case for failing to find a non-loopback address
//TEST(BusinessLogicTest, FetchHostIpAddress_Fail)
//{
//        bank::services::BusinessLogic businessLogic;
//        // Mock the necessary dependencies to simulate failure
//        // Call the fetchHostIpAddress method
//        ASSERT_THROW({
//                             businessLogic.fetchHostIpAddress();
//                     }, std::runtime_error);
//        // Add assertions to check if the expected exception is thrown
//        // ASSERT_... statements to check the expected behavior
//}

// Test case for generating a random incoming payment
TEST(BusinessLogicTest, GenerateRandomPayment_ForIncomingPayment)
{
        // Create a BusinessLogic object
        bank::services::BusinessLogic logic;

        // create a new user account with a password of "password123"
        std::unique_ptr<bank::data::models::UserAccount> user = bank::data::models::UserAccount::createInstance(
                std::make_unique<unsigned int>(1),
                std::make_unique<std::string>("John"),
                std::make_unique<std::string>("Doe"),
                std::make_unique<std::string>("johndoe@example.com"),
                std::make_unique<std::string>("password123")
        );

        bank::data::models::UserAccount* account = user.release();

        // Add a currency balance to the user's account
        std::string currencyName = "CZK";

        // having sufficient funds
        double amount = 100000.0;

        auto balance = bank::data::models::Balance::createInstance(
                std::make_unique<std::string>(currencyName),
                std::make_unique<double>(amount));

        account->addBalance(std::move(balance));

        // Generate a random payment
        std::unique_ptr<bank::data::models::Payment> payment = logic.generateRandomPayment_ForAccount(*account);

        // Assert that the payment is not null
        ASSERT_TRUE(payment);

        // Assert that the payment type is "INCOMING"
        //EXPECT_EQ(*payment->getPaymentType(), "INCOMING");

        // Assert that the payment account ID is not zero
        EXPECT_NE(*payment->getAccountId(), 0);

        // Assert that the payment balance is not null
        ASSERT_TRUE(payment->getBalance());

        // Assert that the payment balance currency is valid
        EXPECT_FALSE(payment->getBalance()->getName().empty());

        // Assert that the payment balance amount is greater than zero
        EXPECT_GT(payment->getBalance()->getAmount(), 0.0);
}

// Test case for generating a random outgoing payment
//TEST(BusinessLogicTest, GenerateRandomPayment_ForOutgoingPayment) {
//        // Create a BusinessLogic object
//        BusinessLogic logic;
//
//        // Create a UserAccount object
//        data::models::UserAccount account;
//
//        // Add a currency balance to the user's account
//        account.addCurrencyBalance("USD", 1000.0);
//
//        // Generate a random payment
//        std::unique_ptr<data::models::Payment> payment = logic.generateRandomPayment_ForAccount(account);
//
//        // Assert that the payment is not null
//        ASSERT_TRUE(payment);
//
//        // Assert that the payment type is "OUTGOING"
//        EXPECT_EQ(*payment->getPaymentType(), "OUTGOING");
//
//        // Assert that the payment account ID is not zero
//        EXPECT_NE(*payment->getAccountId(), 0);
//
//        // Assert that the payment balance is not null
//        ASSERT_TRUE(payment->getBalance());
//
//        // Assert that the payment balance currency is valid
//        EXPECT_FALSE(payment->getBalance()->getName()->empty());
//
//        // Assert that the payment balance amount is greater than zero
//        EXPECT_GT(*payment->getBalance()->getAmount(), 0.0);
//}
//
// Test case for generating a random payment with insufficient fund
//TEST(BusinessLogicTest, GenerateRandomPayment_WithInsufficientFunds)
//{
//        // Create a BusinessLogic object
//        bank::services::BusinessLogic logic;
//
//        // create a new user account with a password of "password123"
//        std::unique_ptr<bank::data::models::UserAccount> user = bank::data::models::UserAccount::createInstance(
//                std::make_unique<unsigned int>(1),
//                std::make_unique<std::string>("John"),
//                std::make_unique<std::string>("Doe"),
//                std::make_unique<std::string>("johndoe@example.com"),
//                std::make_unique<std::string>("password123")
//        );
//
//        bank::data::models::UserAccount* account = user.release();
//
//        // Add a currency balance to the user's account
//        std::string currencyName = "CZK";
//
//        // having sufficient funds
//        double amount = 0;
//
//        auto balance = bank::data::models::Balance::createInstance(
//                std::make_unique<std::string>(currencyName),
//                std::make_unique<double>(amount));
//
//        account->addBalance(std::move(balance));
//
//        // Generate a random payment
//        std::unique_ptr<bank::data::models::Payment> payment = logic.generateRandomPayment_ForAccount(*account);
//
//        // Assert that the payment is not null
//        ASSERT_TRUE(payment);
//
//        // Assert that the payment type is "INCOMING"
//        //EXPECT_EQ(*payment->getPaymentType(), "INCOMING");
//
//        // Assert that the payment account ID is not zero
//        EXPECT_NE(*payment->getAccountId(), 0);
//
//        // Assert that the payment balance is not null
//        ASSERT_TRUE(payment->getBalance());
//
//        // Assert that the payment balance currency is valid
//        EXPECT_FALSE(payment->getBalance()->getName().empty());
//
//        // Assert that the payment balance amount is greater than zero
//        EXPECT_GT(payment->getBalance()->getAmount(), 0.0);
//}

// Test case for applying incoming payment
//TEST(BusinessLogicTest, AttemptToApplyPayment_ForIncomingPayment)
//{
//        // Create a BusinessLogic object
//        bank::services::BusinessLogic logic;
//
//        // Create a UserAccount object
//        auto account = bank::data::models::UserAccount::createInstance(
//                std::make_unique<unsigned int>(1),
//                std::make_unique<std::string>("John"),
//                std::make_unique<std::string>("Doe"),
//                std::make_unique<std::string>("mail@example.com"),
//                std::make_unique<std::string>("password123"));
//
//        int timestamp = 0;
//        bool isIncoming = true;
//        int random_account_id = 1;
//
//        // Add a currency balance to the user's account
//        std::string currencyName = "USD";
//        double amount = 100.0;
//
//        auto balance = bank::data::models::Balance::createInstance(
//                std::make_unique<std::string>(currencyName),
//                std::make_unique<double>(amount));
//
//        auto payment = bank::data::models::Payment::createInstance(
//                std::make_unique<time_t>(timestamp),
//                std::make_unique<std::string> (isIncoming ? "INCOMING" : "OUTGOING"),
//                std::make_unique<unsigned int>(random_account_id = 1),
//                std::move(balance)
//        );
//
//        // Call the function under test
//        bool result = logic.attemptToApplyPayment_ForAccount(account, payment);
//
//        // Assert that the payment was successfully applied
//        EXPECT_TRUE(result);
//        EXPECT_EQ(account.getBalance("USD"), 100.0);
//}
//
//// Test case for applying outgoing payment with sufficient funds
//TEST(BusinessLogicTest, AttemptToApplyPayment_ForOutgoingPaymentWithSufficientFunds) {
//        // Create a BusinessLogic object
//        BusinessLogic logic;
//
//        // Create a UserAccount object
//        data::models::UserAccount account;
//
//        // Add a currency balance to the user's account
//        account.addCurrencyBalance("USD", 200.0);
//
//        // Create an outgoing payment
//        data::models::Payment payment("OUTGOING");
//        payment.setBalance(std::make_unique<data::models::CurrencyBalance>("USD", 100.0));
//
//        // Call the function under test
//        bool result = logic.attemptToApplyPayment_ForAccount(account, payment);
//
//        // Assert that the payment was successfully applied
//        EXPECT_TRUE(result);
//        EXPECT_EQ(account.getBalance("USD"), 100.0);
//}
//
//// Test case for applying outgoing payment with insufficient funds
//TEST(BusinessLogicTest, AttemptToApplyPayment_ForOutgoingPaymentWithInsufficientFunds) {
//        // Create a BusinessLogic object
//        BusinessLogic logic;
//
//        // Create a UserAccount object
//        data::models::UserAccount account;
//
//        // Add a currency balance to the user's account
//        account.addCurrencyBalance("USD", 50.0);
//
//        // Create an outgoing payment with a higher amount than the available balance
//        data::models::Payment payment("OUTGOING");
//        payment.setBalance(std::make_unique<data::models::CurrencyBalance>("USD", 100.0));
//
//        // Call the function under test
//        bool result = logic.attemptToApplyPayment_ForAccount(account, payment);
//
//        // Assert that the payment was not applied due to insufficient funds
//        EXPECT_FALSE(result);
//        EXPECT_EQ(account.getBalance("USD"), 50.0);
//}