#pragma once
#include <iostream>
#include "../include/StandardAccount.h"
#include "../include/SeniorAccount.h"
#include "../include/ChildAccount.h"
#include "assert_values.h"
#include <stdexcept>
	

void assertValues() {
    // Test data
    std::string name = "TEST_NAME";
    std::string lastName = "TEST_LNAME";
    std::string id = "TEST_ID";
    std::string address = "TEST_ADDRESS";
    ll balance = 10000;
    unsigned int age = 40;
    std::string login = "TEST_LOGIN";
    std::string password = "TEST_PASSWORD";

    // Create test accounts
    StandardAccount* standardTest = new StandardAccount(name, lastName, id, address, balance, age, login, password);
    SeniorAccount* seniorTest = new SeniorAccount(name, lastName, id, address, balance, age, login, password);
    ChildAccount* childTest = new ChildAccount(name, lastName, id, address, balance, age, login, password);

    // Display pointers
    std::cout << "Standard Account: " << standardTest << std::endl;
    std::cout << "Senior Account: " << seniorTest << std::endl;
    std::cout << "Child Account: " << childTest << std::endl;

    // Test operations for Standard Account
    std::cout << "Standard Account Test:" << std::endl;
    std::cout << "Initial balance: " << standardTest->getBalance() << std::endl;
    std::cout << "Withdraw 50: " << std::endl; standardTest->withdraw(501);
    std::cout << "Withdraw 501: " << std::endl; standardTest->withdraw(412);
    std::cout << "Balance after withdrawals: " << standardTest->getBalance() << std::endl;
    std::cout << "Deposit 281: " << standardTest->deposit(281) << std::endl;
    std::cout << "Balance after deposit: " << standardTest->getBalance() << std::endl;
    std::cout << "Transfer fee: " << standardTest->transferFee() << std::endl;

    // Test operations for Senior Account
    std::cout << "Senior Account Test:" << std::endl;
    std::cout << "Initial balance: " << seniorTest->getBalance() << std::endl;
    std::cout << "Withdraw 51: " << seniorTest->withdraw(51) << std::endl;
    std::cout << "Withdraw 301: " << seniorTest->withdraw(301) << std::endl;
    std::cout << "Balance after withdrawals: " << seniorTest->getBalance() << std::endl;
    std::cout << "Deposit 144: " << seniorTest->deposit(144) << std::endl;
    std::cout << "Balance after deposit: " << seniorTest->getBalance() << std::endl;
    std::cout << "Transfer fee: " << seniorTest->transferFee() << std::endl;

    // Test operations for Child Account
    std::cout << "Child Account Test:" << std::endl;
    std::cout << "Initial balance: " << childTest->getBalance() << std::endl;
    std::cout << "Withdraw 51: " << childTest->withdraw(51) << std::endl;
    std::cout << "Withdraw 1: " << childTest->withdraw(1) << std::endl;
    std::cout << "Withdraw 49: " << childTest->withdraw(49) << std::endl;
    std::cout << "Balance after withdrawals: " << childTest->getBalance() << std::endl;
    std::cout << "Deposit 144: " << childTest->deposit(144) << std::endl;
    std::cout << "Balance after deposit: " << childTest->getBalance() << std::endl;
    std::cout << "Transfer fee: " << childTest->transferFee() << std::endl;

    // Clean up
    delete standardTest;
    delete seniorTest;
    delete childTest;
    standardTest = nullptr;
    seniorTest = nullptr;
    childTest = nullptr;
}
