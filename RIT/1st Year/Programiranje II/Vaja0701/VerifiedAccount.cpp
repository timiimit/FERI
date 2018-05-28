#include "VerifiedAccount.h"
#include <sstream>

VerifiedAccount::VerifiedAccount() : VerifiedAccount("", -1, "", "", Date(), phone, "", Date())
{
}

VerifiedAccount::VerifiedAccount(const VerifiedAccount& c) : VerifiedAccount(c.person->getName(), c.person->getAge(), c.username, c.password, c.person->getBirthday(), c.verificationType, c.verificationInfo, c.verificationDate)
{
}

VerifiedAccount::VerifiedAccount(const std::string name, const uint age, const std::string username, const std::string password, const Date& birthday, const VerificationType verificationType, const std::string verificationInfo, const Date& verificationDate) : Account(name, age, username, password, birthday),
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

bool VerifiedAccount::isEqualNV(const VerifiedAccount& verAccount) const
{
	return
		verificationDate == verAccount.verificationDate &&
		verificationType == verAccount.verificationType &&
		verificationInfo == verAccount.verificationInfo &&
		Account::isEqualNV(verAccount);
}

std::string VerifiedAccount::toStringNV() const
{
	std::stringstream ss;
	ss << "{ Account: " << Account::toStringNV() << " verificationType: " << verificationType << " verificationDate: " << verificationDate << " verificationInfo: " << verificationInfo << " }";
	return ss.str();
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
