# Concept of Operations Document for Simple Banking System

## Introduction

The purpose of this document is to describe the concept of operations for the Simple Banking System (SBS). 
This document outlines the goals, objectives, and requirements for the system,
as well as its basic functionality and user interface. 
The SBS is a web-based system that allows users to access their account information and perform basic transactions,
such as making payments and checking their balance.

## System Overview

The SBS is a web-based application that allows users to access their banking information through a secure login process.
The system requires users to enter their account ID and password to access their account information. Once logged in,
the user will be presented with a dashboard that displays their account information,
including their account ID, name, and balance.


The system allows users to have multiple balances in their account, each of which represents a certain type of currency.
The balances contain information about the amount of the currency in the account.
Users can view their transaction history by clicking on the "History" button on the dashboard.
The history will display all incoming and outgoing payments,
including the account ID of the sender/receiver,
date (in UNIX timestamp format), currency type, and amount.

The SBS also provides a "Random Payment" feature, which allows users to
generate a random payment record to simulate a payment.


As for any security measures, nothing specific will be implemented as this is a school project.

## System Requirements

The SBS must meet the following requirements:

- User authentication: users must be authenticated with their account ID and password before accessing their account information
- User verification: an email will be sent to the user's email address to verify the login, and the user must confirm the login before being granted access to their account
- Account information: users must be able to view their account information, including their account ID, name, and balance
- Multiple balances: users must be able to have multiple balances in their account, each representing a certain type of currency
- Transaction history: users must be able to view their transaction history, including all incoming and outgoing payments, the account ID of the sender/receiver, date, currency type, and amount
- Random payment generator:
  the system must provide a feature to generate a random payment record to simulate a real payment. 
    The random payment generator must generate a random account ID, date, currency type, amount, and payment type
  (incoming or outgoing)
- When processing the payment and the user does not possess enough funds of the required currency, the system offers 
an option to convert the currency to another currency that the user has in their account.
  The exchange rates are downloaded from
an external data source — czech national bank.
  With the source being:
  https://www.cnb.cz/cs/financni-trhy/devizovy-trh/kurzy-devizoveho-trhu/kurzy-devizoveho-trhu/denni_kurz.txt?date=12.05.2023
  The exchange rates are updated every day between 12:00 PM to 2:00 PM.

## User Interface

The SBS user interface will be a web-based application accessible via a web browser.
The user interface will consist of the following components:

- Login screen: a screen where users will enter their account ID and password to access their account information
- Dashboard: a screen that displays the user's account information, including their account ID, name, and balance, as well as buttons to access the transaction history and generate a random payment
- Error page: a screen that displays an error message when an error occurs

## Technology Stack

The following technologies are being used to develop the system:

- Programming Language: C++23 (gcc 11.1.0) with CMake 3.20.5.
- Web Framework: There are several options available, including cppcms, fastcgi + Apache, fastcgi + Nginx, and crow. 
  The chosen framework will be updated and supported, and not overly complex to implement.
  Based on these criteria, the chosen framework is most likely cppcms.
  In the worst-case scenario, simple CGI will be used.
- Libraries: The system will use several libraries to provide additional functionality,
including libxml for XML parsing and gtest for unit testing.
- Dependency Management: Whenever possible, the system's dependencies will be managed by the package manager of
  the operating system. 
  If a specific version of a dependency is not available, vcpkg will be used to install it.
- Database: A simple XML file hierarchy will be used as a database implementation.
- Architecture: The system supports x86, x86_64, and ARM architectures, 
  mainly due to limitations of the chosen framework and external libraries.
- Operating System: The system is being developed and tested on Linux,
  and there are no plans to implement installation on Windows.
  However, the Docker container in WSL should work.
- Deployment: The application will be deployed inside a Docker container, based on the official Ubuntu image.
- Client Requirements: The client-side of the application only requires a modern and up-to-date web browser 
such as Firefox or Chrome.

# Potential Errors and Possible Exceptions

The following errors and exceptions may occur during the operation of the system:
- Invalid account ID: if the user enters an invalid account ID or password, an error message will be displayed when trying to log in.
- invalid email address: if there's an error with the user's email address, an error message gets displayed and also logged into a file.
- In case there's a problem with downloading the file or the file integrity, exception will be thrown and logged into a file.
- the user has insufficient funds -> the transaction will not complete, and a message will be displayed for the user.

## Conclusion

The Simple Banking System (SBS) is a web-based application that provides users with access to their account information 
and basic transactional features. The system requires users to enter their account ID 
and password to access their account information, and users will receive an email to verify their login.
The SBS allows users to have multiple balances in their account, each representing a certain type of currency,
and provides a transaction history feature that displays all incoming and outgoing payments.
Additionally, the SBS provides a random payment generator for testing purposes. The Time it takes to implement the system is estimated to be 20 hours.
