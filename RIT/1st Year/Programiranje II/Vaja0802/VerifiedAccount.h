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
	VerifiedAccount(const std::string name, const uint age, const std::string username, const std::string password, const Date& birthday, const VerificationType verificationType, const std::string verificationInfo, const Date& verificationDate);
	VerifiedAccount(const Account& c);

	virtual bool isEqual(const VerifiedAccount& verAccount) const;
	std::string toString() const override;
	bool isEqualNV(const VerifiedAccount& verAccount) const;
	std::string toStringNV() const;

	std::string toJSON() override;
};