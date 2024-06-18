#include "../include/SeniorAccount.h"

SeniorAccount::SeniorAccount(
	const std::string& name, const std::string& lName,
	const std::string& id, const std::string& addr, const ll& bal,
	const unsigned int& age, const std::string& log, const std::string& pass) :
	StandardAccount(name, lName, id, addr, bal, age, log, pass) {}


ll SeniorAccount::transferFee() const {
	return 0.50;
}