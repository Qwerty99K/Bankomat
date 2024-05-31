#pragma once
#include <iostream>
#include "../include/StandardAccount.h"
#include "../include/SeniorAccount.h"
#include "assert_values.h"


void assertValues() {
	// test czy dziala poprawnie
	std::string name = "TEST_NAME";
	std::string lName = "TEST_LNAME";
	std::string id = "TEST_ID";
	std::string addr = "TEST_ADDRESS";
	ll balance = 100;
	unsigned int age = 40;

	std::string log = "TEST_LOGIN";
	std::string pass = "TEST_PASSWORD";

	StandardAccount* STANDARD_TEST = new StandardAccount(name, lName, id, addr, balance, age, log, pass);
	SeniorAccount* SENIOR_TEST = new SeniorAccount(name, lName, id, addr, balance, age, log, pass);
	std::cout << STANDARD_TEST << std::endl;
	std::cout << SENIOR_TEST << std::endl;
	std::cout << STANDARD_TEST->getBalance() << std::endl;
	std::cout << STANDARD_TEST->withdraw(50) << std::endl;
	std::cout << STANDARD_TEST->getBalance() << std::endl;
	std::cout << STANDARD_TEST->deposit(281) << std::endl;
	std::cout << STANDARD_TEST->getBalance() << std::endl;

	std::cout << SENIOR_TEST->getBalance() << std::endl;
	std::cout << SENIOR_TEST->withdraw(51) << std::endl;
	std::cout << SENIOR_TEST->getBalance() << std::endl;
	std::cout << SENIOR_TEST->deposit(144) << std::endl;
	std::cout << SENIOR_TEST->getBalance() << std::endl;
	delete STANDARD_TEST; delete SENIOR_TEST;
	STANDARD_TEST = nullptr; SENIOR_TEST = nullptr;
}