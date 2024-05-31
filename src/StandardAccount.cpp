#include "../include/StandardAccount.h"

StandardAccount::StandardAccount(
	const std::string& name, const std::string& lName,
	const std::string& id, const std::string& addr, const ll& bal,
	const unsigned int& age, const std::string& log, const std::string& pass) : 
	name(name), lastName(lName), id(id), address(addr), balance(bal), age(age), 
	login(log), password(pass) {}

ll StandardAccount::getBalance() const {
	return this->balance;
}

ll StandardAccount::deposit(const ll& amount) const {
	this->balance += amount;
	return amount;
}

ll StandardAccount::withdraw(const ll& amount) const {
	if (this->balance < amount) {
		std::cout << "Blad" << std::endl;
	}
	this->balance -= amount;
	return amount;
}

/*
	reszta tu
*/

ll StandardAccount::transferFee() const {
	return 1.5;
}