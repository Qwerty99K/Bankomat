#include "../include/StandardAccount.h"
#include "../include/Status.h"
StandardAccount::StandardAccount(
	const std::string& name, const std::string& lName,
	const std::string& id, const std::string& addr, const ll& bal,
	const unsigned int& age, const std::string& log, const std::string& pass) : 
	name(name), lastName(lName), id(id), address(addr), balance(bal), age(age), 
	login(log), password(pass) {
	//constructor zapisze te wszystkie dane? ewentualnie lepszy sposob
}

ll StandardAccount::getBalance() const {
	return this->balance;
}

ll StandardAccount::deposit(const ll& amount) const {
	if (0 < amount) {
		this->balance += amount;
		return amount;
	}
	else {
		std::cout << "Ujemna kwota. " << std::endl;
	}
}

ll StandardAccount::withdraw(const ll& amount) const {
	if (amount > 0 && amount < LIMIT && this->balance > amount) {
		this->balance -= amount;
		return amount;
	}
	else {
		std::cout << "Za duzo chcesz wyplacic. " << std::endl;
	}
}

/*
	reszta tu
*/

ll StandardAccount::transferFee() const {
	return 1.5;
}