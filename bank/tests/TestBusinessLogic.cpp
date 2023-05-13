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

