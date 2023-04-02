# Securities Portfolio Management System

This project was implemented as a final project for the course "Object-Oriented Programming in C++" at the University of West Attica in 2018. The purpose of the project is to develop a software system for recording a portfolio of securities, including stocks and bonds. The system will be used by employees of a brokerage company to record the different types of securities held by its clients and to calculate the charges that the company imposes on them.

## Overview

The Securities Portfolio Management System is a command-line program that allows users to manage their portfolios and securities accounts. The program stores portfolio data in separate files, which are specified using a global variable (portfolio_counter). The first line of each file contains the client's data, followed by information on their securities.

In the event that a file cannot be opened or read, the getInfo() function provides the user with instructions on how to check the file's format. If no portfolios exist, the user can create a new portfolio and continue using the system.

All customer data is stored in a common vector, as well as their securities. Changes to portfolios and securities accounts are saved simultaneously to the client's file.

If a portfolio is marked as invalid, it is displayed with a message indicating that it is cancelled. However, the total cost of its securities is still factored into calculations.

## Information Model

A client's portfolio consists of a set of securities, which can be either stocks or bonds. Each portfolio contains the following information:

    Full name of client
    Address of residence
    Contact telephone
    VAT number
    A list of securities contained in the portfolio

The securities in the portfolio have common features such as the name of the issuing company, face value, and quantity held by the customer. Bonds have additional features such as the maturity year and interest rate.

The annual fees that clients have to pay for maintaining their portfolios are calculated differently for stocks and bonds.

## User Interface

The system provides a user-friendly command-line interface with the following functions:

    Add a new portfolio
    Modify an existing portfolio
    Cancel a portfolio
    Display information:
        Number of portfolios with a total debt of more than X euros
        Number of portfolios with an individual debt instrument with a charge of more than X euros
        Top 10 portfolios with the highest fees

When adding a portfolio to the system, charges can be entered directly from a text file. Each line of the file follows a specific format for stocks and bonds.

## File Format

Each line of the file will have the following format:

Stocks
  > M | company | nominal value | quantity | year of acquisition | purchase price

Bonds
  > O | company | face value | quantity | year of acquisition | year of maturity | interest rate

## Application Structure

The portfolios and securities are stored and manipulated using vectors. Polymorphism is used to allow for uniform manipulation of portfolios and securities.

## Getting Started

To get started with the Securities Portfolio Management System, simply download or clone the repository and run the executable file.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
