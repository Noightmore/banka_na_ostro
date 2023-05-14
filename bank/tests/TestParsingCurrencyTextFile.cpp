#include <gtest/gtest.h>
#include "include/data/ApplicationDbContext.hpp"


TEST(ApplicationDbContextTest, LoadExchangeRatesFromCacheFile_Success)
{
        bank::data::ApplicationDbContext db;
        // Arrange
        std::string filename = "../tests/test_denni_kurz.txt";

        // Act
        ASSERT_NO_THROW(db.loadExchangeRatesFromCacheFile(filename));

        // Assert
        // Check that the exchange rates were loaded correctly
        auto exchangeRateSize = db.bankData->getExchangeRateSize();
        ASSERT_EQ(exchangeRateSize, 31);

        std::string type = "AUD";
        auto rate = db.bankData->getCurrentExchangeRate_ByName(type);
        EXPECT_EQ(rate.getName(), "AUD");
        EXPECT_EQ(rate.getAmount(), 1);
        EXPECT_DOUBLE_EQ(rate.getRate(), 14.481);

        type = "BRL";
        rate = db.bankData->getCurrentExchangeRate_ByName(type);
        EXPECT_EQ(rate.getName(), "BRL");
        EXPECT_EQ(rate.getAmount(), 1);
        EXPECT_DOUBLE_EQ(rate.getRate(), 4.3789999999999996);

        // ... continue with the rest of the exchange rates
}

TEST(ApplicationDbContextTest, LoadExchangeRatesFromCacheFile_FileNotFound)
{
        bank::data::ApplicationDbContext db;
        // Arrange
        std::string filename = "non_existent_file.txt";

        // Act & Assert
        EXPECT_THROW(db.loadExchangeRatesFromCacheFile(filename), std::runtime_error);
}

TEST(ApplicationDbContextTest, LoadExchangeRatesFromCacheFile_InvalidData)
{
        bank::data::ApplicationDbContext db;
        // Arrange
        std::string filename = "invalid_exchange_rates.txt";

        // Act & Assert
        EXPECT_THROW(db.loadExchangeRatesFromCacheFile(filename), std::runtime_error);
}
