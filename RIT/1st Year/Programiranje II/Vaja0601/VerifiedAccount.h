#pragma once
#include "Account.h"

enum VerificationType
{
	phone = 0,
	email = 1,
	id_number = 2
};

class VerifiedAccount : public Account
{
private:
	VerificationType verificationType;
	std::string verificationInfo;
	Date verificationDate;

public:

	VerifiedAccount();
	VerifiedAccount(const VerifiedAccount& c);
	VerifiedAccount(std::string name, uint age, std::string username, std::string password, Date* birthday, VerificationType verificationType, std::string verificationInfo, Date verificationDate);
	VerifiedAccount(const Account& c);

	bool isEqual(const VerifiedAccount& verAccount) const;
	std::string toString() const;
};