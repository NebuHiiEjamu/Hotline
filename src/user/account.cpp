#include <fstream>
#include <memory>

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

uint16 Account::getColor()
{
	LockGuard lock(mutex);
	return color;
}

std::string_view& Account::getLogin()
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
	HLOutStream stream;

	stream.write(legacyUserDataMagic);
	stream.write(access.to_ullong());
	stream.pad(516); // padding
	stream.write(name, 134);
	stream.write(login, maxLoginSize);
	stream.write(password, maxPasswordSize);

	std::ofstream outFile(path / "UserData", std::ofstream::binary);
	outFile << stream.getBuffer();
	outFile.close();
}

void Account::exportHxdAccess(const FilePath &path) const
{
	std::ofstream outFile(path / "access");

	outFile << "user_visibility=" << accessEx.test(AccessEx::userVisibility) ? '1' : '0' << std::endl;
	outFile << "user_color=" << accessEx.test(AccessEx::userColor) ? '1' : '0' << std::endl;
	outFile << "can_spam=" << accessEx.test(AccessEx::canSpam) ? '1' : '0' << std::endl;
	outFile << "set_subject=" << accessEx.test(AccessEx::setSubject) ? '1' : '0' << std::endl;
	outFile << "user_access=" << accessEx.test(AccessEx::userAccess) ? '1' : '0' << std::endl;
	outFile << "user_0wn=" << accessEx.test(AccessEx::user0wn) ? '1' : '0' << std::endl;
	outFile << "access_volatile=" << accessEx.test(AccessEx::accessVolatile) ? '1' : '0' << std::endl;
	outFile << "is_0wn3d=" << accessEx.test(AccessEx::is0wn3d) ? '1' : '0' << std::endl;
	outFile << "manage_users=" << accessEx.test(AccessEx::manageUsers) ? '1' : '0' << std::endl;
	outFile << "color=" << color << std::endl;
	outFile << "invisibility=" << statusEx.test(UserStatusEx::visible) ? '1' : '0' << std::endl;
	outFile << "icon=" << icon << std::endl;
	outFile << "msg=" << accessEx.test(AccessEx::msg) ? '1' : '0' << std::endl;
	outFile.close();
}

void Account::exportHxdConf(const FilePath &path) const
{
	std::ofstream outFile(path / "conf");
	outFile << "limits {" << std::endl;
	outFile << "\tindividual_downloads " << downloads << ';' << std::endl;
	outFile << "\tindividual_uploads " << uploads << ';' << std::endl;
	outFile << "\tout_Bps " << outBps << ';' << std::endl;
	outFile << "};" << std::endl;
	outFile.close();
}
