#include "../include/ChildAccount.h"
#include <iostream>


ChildAccount::ChildAccount(
	const std::string& name, const std::string& lName,
	const std::string& id, const std::string& addr, const ll& bal,
	const unsigned int& age, const std::string& log, const std::string& pass) :
	StandardAccount(name, lName, id, addr, bal, age, log, pass) {}

ll ChildAccount::transferFee() const {
	return 0.0;
}