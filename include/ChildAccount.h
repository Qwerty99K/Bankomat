#pragma once
#include <iostream>
#include "../include/StandardAccount.h"
#include "../include/Status.h"
class ChildAccount : public StandardAccount {
public:
	ChildAccount(const std::string&, const std::string&,
		const std::string&, const std::string&, const ll&,
		const unsigned int&, const std::string&, const std::string&);	// bedziemy chcieli aby podali wszystko, jeden konst
	ll transferFee() const;
	// ll withdraw(const ll&) const;

private:
	static constexpr ll LIMIT{ 50 };
};

