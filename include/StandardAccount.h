#pragma once
#include <iostream>
#include <string>
#include "../include/Status.h"
using ll = long long;


class StandardAccount {
public:
	StandardAccount(const std::string&, const std::string&, 
		const std::string&, const std::string&, const ll&, 
		const unsigned int&, const std::string&, const std::string&);	// bedziemy chcieli aby podali wszystko, jeden konstruktor wystarczy
	ll getBalance() const;
	virtual ll deposit(const ll&) const; // nie wiem czy bedziemy robic wirtualne, definicja bo kazda taka sama bedzie?
	virtual ll withdraw(const ll&) const;
	virtual ll transferFee() const; // platnosc za transfer kaski

private:
	std::string name;
	std::string lastName;
	std::string id;
	std::string address;
	mutable ll balance;
	mutable unsigned int age;
	static constexpr ll LIMIT{500};

	mutable std::string login;
	mutable std::string password;

	// numer konta
	// zhashowac potem te dane
	// powiadomienia - zobaczy sie potem, jak bedziemy czytac dane (kazdy przelew daje ping?)
};