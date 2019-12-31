#include <ctime>
#include <fmt/core.h>
#include <iomanip>
#include <sstream>

#include "session.hpp"
#include "hlconnection.hpp"
#include "../hlserver.hpp"

Session::Session(uint16 id, HLConnectionPtr connection):
	connection(connection),
	lastTransactionId(0),
	replies(0),
	id(id)
{
}

uint16 Session::getId() const
{
	return id;
}

uint16 Session::getIcon()
{
	LockGuard lock(mutex);
	return icon;
}

uint16 Session::getStatus()
{
	LockGuard lock(mutex);
	return static_cast<uint16>(status.to_ulong());
}

uint32 Session::getStatusEx()
{
	LockGuard lock(mutex);
	return static_cast<uint32>(statusEx.to_ulong());
}

std::string&& Session::getClientInfoText()
{
	static constexpr int spacing1 = 22;
	static constexpr int spacing2 = 32;
	LockGuard lock(mutex);
	std::ostringstream ss;
	std::time_t cLoginTime = std::chrono::system_clock::to_time_t(uptime);

	ss << fmt::format("{:<{}}{:>{}}\r", "Name:", spacing1, nickname, spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Login:", spacing1, account->getLogin(), spacing2);
	ss << fmt::format("{:<{}}{:>{}:{}}\r", "Address:", spacing1, connection->getAddress().to_string(),
		connection->getPort(), spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Host:", spacing1, connection->getHostName(), spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "ID:", spacing1, id, spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Color:", spacing1, color, spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Icon:", spacing1, icon, spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Version:", spacing1, getVersionString(), spacing2);
	//ss << fmt::format("{:<{}}{:>{}}\r", "Client:", spacing1, getClient(), spacing2);
	ss << fmt::format("{:<{}}{:>{}}\r", "Logged in:", spacing1,
		std::put_time(std::localtime(&cLoginTime), "%F %T"), spacing2);

	return ss.str();
}

std::string&& Session::getVersionString() const
{
	std::string s(std::to_string(version));
	s.insert(1, 1, '.');
	s.insert(3, 1, '.');
	return std::move(s);
}

/*std::string_view&& Session::getClient() const
{
	if (statusEx.test(UserStatusEx::isHL)) return "Hotline";
	if (statusEx.test(UserStatusEx::isTide)) return "Panorama";
	if (statusEx.test(UserStatusEx::isAniClient)) return "AniClient";
	if (statusEx.test(UserStatusEx::isHeidrun)) return "Heidrun";
	if (statusEx.test(UserStatusEx::isFrogblast)) return "Frogblast";
	return "";
}*/

void Session::setStatus(uint16 flags)
{
	LockGuard lock(mutex);
	status = std::bitset<UserStatus::all>(flags);
	if (status.test(UserStatus::away)) statusEx.set(UserStatusEx::away);
}

void Session::setIcon(uint16 newIcon)
{
	LockGuard lock(mutex);
	icon = newIcon;
}

void Session::setStatusEx(uint32 flags)
{
	LockGuard lock(mutex);
	statusEx = std::bitset<UserStatusEx::all>(flags);
	if (statusEx.test(UserStatusEx::away)) status.set(UserStatus::away);
}

void Session::handleLogin(HLInStream &stream, const Transaction &transaction)
{
	HLServerRef inst = HLServer::getInstance();
	uint16 fieldCount = stream.read();
	std::string login = stream.readStringField();
	ByteString password = stream.readStringField();
	version = stream.readField();

	account = inst->getAccount(login, password);
	uptime = std::chrono::system_clock::now();
	color = account->getColor();
	lastTransactionId = trans.id;

	Transaction reply { true, TransId::reply, transaction.id, 0, connection->getErrorState(),
		0, 0 };
	Buffer output;
	HLOutStream stream(output);
	
	if (version >= 151)
	{
		reply.totalSize = reply.thisSize = inst->getName().size() + 8; 
	}
	else
		reply.totalSize = reply.thisSize = 6;

	stream.write(reply);
	stream.write16(version >= 151 ? 2 : 1);
	stream.write(Field::vers, HLServer::version);
	if (version >= 151) stream.write(Field::serverName, inst->getName());
	connection->send(output);
}
