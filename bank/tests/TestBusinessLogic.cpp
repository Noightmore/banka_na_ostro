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

