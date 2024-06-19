#pragma once
#include <iostream>

enum class AccountType { // typ kont
	STANDARD_ACCOUNT,
	CHILD_ACCOUNT,
	SENIOR_ACCOUNT,
};

enum class StandardStatus {
	ACTIVE = true,
	PENDING = false,
};


enum class AppStates {
	ON = true,
	OFF = false,
};