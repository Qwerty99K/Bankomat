#pragma once
#include <iostream>
#include <string>
#include "../include/StandardAccount.h"


class SeniorAccount : public StandardAccount {
public:
	SeniorAccount(const std::string&, const std::string&,
		const std::string&, const std::string&, const ll&,
		const unsigned int&, const std::string&, const std::string&);
	ll transferFee() const;
		

private:
	static constexpr ll LIMIT{ 300 };
};