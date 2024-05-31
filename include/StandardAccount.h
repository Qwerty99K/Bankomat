#pragma once
#include <iostream>
#include <string>
using ll = long long;


class StandardAccount {
public:
	StandardAccount(const std::string&, const std::string&, 
		const std::string&, const std::string&, const ll&, 
		const unsigned int&, const std::string&, const std::string&);	// bedziemy chcieli aby podali wszystko, jeden konstruktor wystarczy
		ll getBalance() const;
		virtual ll deposit(const ll&) const; // nie wiem czy bedziemy robic wirtualne, definicja bo kazda taka sama bedzie?
		virtual ll withdraw(const ll&) const;

		//template<class T>
		//ll transfer(T* ) const; // get account's 
		//void getReport() const; // nie wiem jaki typ bedzie koncowo (jak bedziemy czytac)
		//void getTransactionHistory() const; // nie wiem jak bedziemy czytac, krotsza nazwa
		virtual ll transferFee() const; // platnosc za transfer kaski


private:
	std::string name;
	std::string lastName;
	std::string id;
	std::string address;
	mutable ll balance;
	unsigned int age;

	mutable std::string login;
	mutable std::string password;

	// numer konta
	// zhashowac potem te dane
	// powiadomienia - zobaczy sie potem, jak bedziemy czytac dane (kazdy przelew daje ping?)
};