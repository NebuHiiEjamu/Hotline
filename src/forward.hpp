#ifndef _HL_FORWARD_H
#define _HL_FORWARD_H

#include <memory>

class HLServer;
class TrackerConnection;

using HLServerRef = std::weak_ptr<HLServer>;
using TrackerConnectionPtr = std::shared_ptr<TrackerConnection>;
using TrackerConnectionRef = std::weak_ptr<TrackerConnection>;

#endif // _HL_FORWARD_H
