#ifndef _HL_FORWARD_H
#define _HL_FORWARD_H

#include <memory>

class HLServer;
class TrackerConnection;
class TrackerSession;

using HLServerRef = std::weak_ptr<HLServer>;
using TrackerConnectionPtr = std::shared_ptr<TrackerConnection>;
using TrackerConnectionRef = std::weak_ptr<TrackerConnection>;
using TrackerSessionPtr = std::shared_ptr<TrackerSession>;
using TrackerSessionRef = std::weak_ptr<TrackerSession>;

#endif // _HL_FORWARD_H
