#include "session.hpp"
#include "hlconnection.hpp"

Session::Session(suint16 id, PalaceConnectionPtr connection):
	connection(connection),
	id(id)
{
}

suint16 Session::getId() const
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

uint16 Session::getVersion() const
{
	return version;
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
