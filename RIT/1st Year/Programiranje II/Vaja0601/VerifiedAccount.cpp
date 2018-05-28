#include "VerifiedAccount.h"
#include <sstream>

VerifiedAccount::VerifiedAccount() : VerifiedAccount("", -1, "", "", nullptr, phone, "", Date())
{
}

VerifiedAccount::VerifiedAccount(const VerifiedAccount& c) : VerifiedAccount(c.name, c.age, c.username, c.password, c.birthday, c.verificationType, c.verificationInfo, c.verificationDate)
{
}

VerifiedAccount::VerifiedAccount(std::string name, uint age, std::string username, std::string password, Date* birthday, VerificationType verificationType, std::string verificationInfo, Date verificationDate) : Account(name, age, username, password, birthday),
	verificationType(verificationType),
	verificationDate(verificationDate),
	verificationInfo(verificationInfo)
{
}

VerifiedAccount::VerifiedAccount(const Account& c) : Account(c),
	verificationType(phone),
	verificationDate(),
	verificationInfo()
{
}

bool VerifiedAccount::isEqual(const VerifiedAccount& verAccount) const
{
	return
		verificationDate == verAccount.verificationDate &&
		verificationType == verAccount.verificationType &&
		verificationInfo == verAccount.verificationInfo &&
		Account::isEqual(verAccount);
}

std::string VerifiedAccount::toString() const
{
	std::stringstream ss;
	ss << "{ Account: " << Account::toString() << " verificationType: " << verificationType << " verificationDate: " << verificationDate << " verificationInfo: " << verificationInfo << " }";
	return ss.str();
}
