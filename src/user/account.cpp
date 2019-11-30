#include "account.hpp"

uint64 Account::getAccess()
{
	LockGuard lock(mutex);
	return access.to_ullong();
}

uint32 Account::getAccessEx()
{
	LockGuard lock(mutex);
	return static_cast<uint32>(accessEx.to_ulong());
}

std::string_view Account::getLogin()
{
	LockGuard lock(mutex);
	return login;
}

void Account::setAccess(uint64 flags)
{
	LockGuard lock(mutex);
	access = std::bitset<Access::all>(flags);
}

void Account::setAccessEx(uint32 flags)
{
	LockGuard lock(mutex);
	accessEx = std::bitset<AccessEx::all>(flags);
}
