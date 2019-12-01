#include <fstream>

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

void Account::exportLegacyUserData(const FilePath &path) const
{
	ByteBuffer buffer;

	buffer.write32(legacyUserDataMagic);
	buffer.write64(access.to_ullong());
	buffer.writeNull(516); // padding
	buffer.writeString(name, 134);
	buffer.writeString(login, 34);
	buffer.writeString(password, 32);

	ByteString userData = buffer.getBytes();
	std::ofstream outFile(path / "UserData", std::ofstream::binary);
	outFile.write(reinterpret_cast<const char*>(userData.data()), legacyUserDataSize);
	outFile.close();
}

void Account::exportHxdAccess(const FilePath &path) const
{
}

void Account::exportHxdConf(const FilePath &path) const
{
}
