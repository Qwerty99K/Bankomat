#pragma once
#include <iostream>
#include <string>
#include "../include/StandardAccount.h"


class SeniorAccount : public StandardAccount {
public:
	SeniorAccount(const std::string&, const std::string&,
		const std::string&, const std::string&, const ll&,
		const unsigned int&, const std::string&, const std::string&);	// bedziemy chcieli aby podali wszystko, jeden konstruktor wystarczy
	ll transferFee() const; // platnosc za transfer kaski	
		

private:
	static constexpr ll LIMIT{ 300 };
	// numer konta
	// zhashowac potem te dane
	// powiadomienia - zobaczy sie potem, jak bedziemy czytac dane (kazdy przelew daje ping?)
};