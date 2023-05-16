#include <gtest/gtest.h>
#include "include/data/ApplicationDbContext.hpp"

// Tests parsing a balance from an XML node with valid values
TEST(ApplicationDbContextTest, ParseBalanceFromXML_ValidBalance)
{
        std::string xml = "<balance>"
                          "<balance_type>checking</balance_type>"
                          "<amount>100.50</amount>"
                          "</balance>";

        xmlDocPtr doc = xmlParseDoc((xmlChar*)xml.c_str());
        xmlNodePtr rootNode = xmlDocGetRootElement(doc);

        bank::data::ApplicationDbContext db;

        std::unique_ptr<bank::data::models::Balance> result = db.parseBalanceFromXML(rootNode);

        EXPECT_NE(result, nullptr);
        EXPECT_EQ(result->getName(), "checking");
        EXPECT_EQ(result->getAmount(), 100.50);

        xmlFreeDoc(doc);
}

// Tests parsing a balance from an XML node with missing balance_type
TEST(ApplicationDbContextTest, ParseBalanceFromXML_MissingBalanceType)
{
        std::string xml = "<balance>"
                          "<amount>100.50</amount>"
                          "</balance>";

        xmlDocPtr doc = xmlParseDoc((xmlChar*)xml.c_str());
        xmlNodePtr rootNode = xmlDocGetRootElement(doc);

        bank::data::ApplicationDbContext db;

        std::unique_ptr<bank::data::models::Balance> result = db.parseBalanceFromXML(rootNode);

        EXPECT_EQ(result, nullptr);

        xmlFreeDoc(doc);
}

// Tests parsing a balance from an XML node with missing amount
TEST(ApplicationDbContextTest, ParseBalanceFromXML_MissingAmount)
{
        std::string xml = "<balance>"
                          "<balance_type>checking</balance_type>"
                          "</balance>";

        xmlDocPtr doc = xmlParseDoc((xmlChar*)xml.c_str());
        xmlNodePtr rootNode = xmlDocGetRootElement(doc);

        bank::data::ApplicationDbContext db;

        std::unique_ptr<bank::data::models::Balance> result = db.parseBalanceFromXML(rootNode);

        EXPECT_EQ(result, nullptr);

        xmlFreeDoc(doc);
}

// Tests parsing a balance from an XML node with invalid amount
TEST(ApplicationDbContextTest, ParseBalanceFromXML_InvalidAmount)
{
        std::string xml = "<balance>"
                          "<balance_type>checking</balance_type>"
                          "<amount>invalid</amount>"
                          "</balance>";

        xmlDocPtr doc = xmlParseDoc((xmlChar*)xml.c_str());
        xmlNodePtr rootNode = xmlDocGetRootElement(doc);

        bank::data::ApplicationDbContext db;

        std::unique_ptr<bank::data::models::Balance> result = db.parseBalanceFromXML(rootNode);

        EXPECT_EQ(result, nullptr);

        xmlFreeDoc(doc);
}

TEST(ApplicationDbContextTest, ParsePaymentFromXMLValid)
{
        const char* xml =
                "<payment>"
                "<payment_date>1656576000</payment_date>"
                "<payment_type>credit_card</payment_type>"
                "<payment_receiver_sender_id>12345</payment_receiver_sender_id>"
                "<payment_currency>USD</payment_currency>"
                "<payment_amount>500.00</payment_amount>"
                "</payment>";

        xmlDocPtr doc = xmlParseMemory(xml, strlen(xml));
        xmlNodePtr root = xmlDocGetRootElement(doc);

        bank::data::ApplicationDbContext db;

        auto payment = db.parsePaymentFromXML(root);

        ASSERT_NE(payment, nullptr);
        EXPECT_EQ(*payment->getDate(), 1656576000);
        EXPECT_EQ(*payment->getPaymentType(), "credit_card");
        EXPECT_EQ(*payment->getAccountId(), 12345u);
        EXPECT_EQ(payment->getBalance()->getName(), "USD");
        EXPECT_DOUBLE_EQ(payment->getBalance()->getAmount(), 500.00);

        xmlFreeDoc(doc);
}

TEST(ApplicationDbContextTest, ParsePaymentFromXMLInvalid)
{
        const char* xml =
                "<payment>"
                "<payment_date>1656576000</payment_date>"
                "<payment_type>credit_card</payment_type>"
                "<payment_currency>USD</payment_currency>"
                "<payment_amount>500.00</payment_amount>"
                "</payment>";

        xmlDocPtr doc = xmlParseMemory(xml, strlen(xml));
        xmlNodePtr root = xmlDocGetRootElement(doc);

        bank::data::ApplicationDbContext db;

        auto payment = db.parsePaymentFromXML(root);

        EXPECT_EQ(payment, nullptr);

        xmlFreeDoc(doc);
}

// Test case for an existing user
TEST(ApplicationDbContextTest, GetUserAccountById_ExistingUser)
{

        bank::data::ApplicationDbContext db;
        unsigned int id = 1; // Specify an existing user ID

        bank::data::models::UserAccount user = db.getUserAccountById(id);

        // Perform assertions to verify the expected results
        // For example:
        EXPECT_EQ(user.getId(), id);
        // Add more assertions based on your specific UserAccount class
}

// Test case for a non-existing user
TEST(ApplicationDbContextTest, GetUserAccountById_NonExistingUser)
{

        bank::data::ApplicationDbContext db;
        unsigned int id = 5315; // Specify a non-existing user ID

        // Perform assertions to verify that an exception is thrown
        EXPECT_THROW(db.getUserAccountById(id), std::invalid_argument);
        // You can also check the error message of the exception if necessary
}


// Test case for loading exchange rates when the cache file exists and is up to date
TEST(ApplicationDbContextTest, LoadExchangeRates_CacheFileUpToDate)
{
        bank::data::ApplicationDbContext db;

        // Create the cache file with recent content
        std::ofstream cacheFile("denni_kurz.txt");
        // Add relevant content to the cache file
        cacheFile << "Example content";
        cacheFile.close();

        // Assume the cache file is up-to-date (less than one day old)
        // Set the current date to yesterday
        std::time_t t = std::time(nullptr) - (24 * 60 * 60);
        std::tm tm = *std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%d.%m.%Y");

        // Load the exchange rates
        db.loadExchangeRates();

        // Add assertions to check if the exchange rates are properly loaded,
        // and the cache file is not updated
        // ASSERT_... Statements to check the expected behavior
}

// Test case for loading exchange rates when the cache file exists but is outdated
TEST(ApplicationDbContextTest, LoadExchangeRates_CacheFileOutdated)
{
        bank::data::ApplicationDbContext db;

        // Create the cache file with outdated content
        std::ofstream cacheFile("denni_kurz.txt");
        // Add outdated content to the cache file
        cacheFile << "Outdated content";
        cacheFile.close();

        // Assume the cache file is outdated (more than one day old)
        // Set the current date to two days ago
        std::time_t t = std::time(nullptr) - (2 * 24 * 60 * 60);
        std::tm tm = *std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%d.%m.%Y");

        // Load the exchange rates
        db.loadExchangeRates();

        // Add assertions to check if the exchange rates are properly loaded,
        // and the cache file is updated with new data
        // ASSERT_... statements to check the expected behavior

        // DELETE THE CACHE FILE AFTER THE TEST IS FINISHED
        // Otherwise, the next test will fail
        std::remove("denni_kurz.txt");
}

// Test case for loading exchange rates when the cache file does not exist
TEST(ApplicationDbContextTest, LoadExchangeRates_CacheFileDoesNotExist)
{

        bank::data::ApplicationDbContext db;
        // Assume the cache file does not exist
        // Set the current date to yesterday
        std::time_t t = std::time(nullptr) - (24 * 60 * 60);
        std::tm tm = *std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%d.%m.%Y");

        // Load the exchange rates
        db.loadExchangeRates();

        // Add assertions to check if the exchange rates are properly loaded,
        // and the cache file is created with new data
        // ASSERT_... statements to check the expected behavior
}

// Test case for a file modified less than one day ago
//TEST(ApplicationDbContextTest, IsFileOlderThanOneDay_LessThanOneDay)
//{
//        bank::data::ApplicationDbContext db;
//        const char* filename = "testfile.txt"; // Replace with an existing file that was modified recently
//        EXPECT_FALSE(db.isFileOlderThanOneDay(filename));
//}
//
//// Test case for a file modified more than one day ago
//TEST(ApplicationDbContextTest, IsFileOlderThanOneDay_MoreThanOneDay)
//{
//        bank::data::ApplicationDbContext db;
//        const char* filename = "oldfile.txt"; // Replace with an existing file that was modified more than one day ago
//        EXPECT_TRUE(db.isFileOlderThanOneDay(filename));
//}
//
//// Test case for a non-existing file
//TEST(ApplicationDbContextTest, IsFileOlderThanOneDay_NonExistingFile)
//{
//        bank::data::ApplicationDbContext db;
//        const char* filename = "nonexistingfile.txt";
//        EXPECT_FALSE(db.isFileOlderThanOneDay(filename));
//}


// Test case for loading user data from a corrupted file
//TEST(ApplicationDbContextTest, LoadBasicUserData_CorruptedFile)
//{
//        bank::data::ApplicationDbContext db;
//        xmlNodePtr cur = nullptr; // Create a dummy xmlNodePtr object
//        xmlChar* content = nullptr; // Create a dummy xmlChar* object
//        unsigned int id;
//        std::string firstName;
//        std::string lastName;
//        std::string email;
//        std::string password;
//
//        // Add your specific corrupted file content here
//        // For example, if the "firstname" element is missing or corrupted
//        // cur = <account_id>123</account_id><lastname>Doe</lastname><email>john.doe@example.com</email><password>password</password>
//
//        // Perform the loading operation and expect an exception to be thrown
//        EXPECT_THROW(db.loadBasicUserData(cur, content, &id, &firstName, &lastName, &email, &password), std::invalid_argument);
//        // You can also check the error message of the exception if necessary
//}