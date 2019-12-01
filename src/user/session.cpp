#include <iomanip>
#include <sstream>

#include "session.hpp"
#include "hlconnection.hpp"

Session::Session(uint16 id, PalaceConnectionPtr connection):
	connection(connection),
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

std::string Session::getClientInfoText()
{
	static constexpr int spacing = 24;
	LockGuard lock(mutex);
	std::ostringstream ss;

	ss << std::setw(spacing) << "Name:" << nickname << '\r';
	ss << std::setw(spacing) << "Login:" << account->getLogin() << '\r';
	ss << std::setw(spacing) << "Address:" << connection->getAddress() << '\r';
	ss << std::setw(spacing) << "Host:" << connection->getHostName() << '\r';
	ss << std::setw(spacing) << "ID:" << id << '\r';
	ss << std::setw(spacing) << "Icon:" << icon << '\r';
	ss << std::setw(spacing) << "Hotline Version:" << version << '\r';
	ss << std::setw(spacing) << "Client:" << getClient();

	return ss.str();
}

std::string_view Session::getClient() const
{
	if (statusEx.test(UserStatusEx::hotline)) return "Hotline";
	if (statusEx.test(UserStatusEx::tide)) return "Panorama";
	if (statusEx.test(UserStatusEx::aniclient)) return "AniClient";
	if (statusEx.test(UserStatusEx::heidrun)) return "Heidrun";
	if (statusEx.test(UserStatusEx::frogblast)) return "Frogblast";
	return "";
}

void Session::setStatus(uint16 flags)
{
	LockGuard lock(mutex);
	status = std::bitset<UserStatus::all>(flags);
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
}
