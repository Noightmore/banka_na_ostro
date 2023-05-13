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


