#ifndef _FILE_FORWARD_H
#define _FILE_FORWARD_H

#include <memory>

class FileConnection;
class FileSession;

using FileConnectionPtr = std::shared_ptr<FileConnection>;
using FileConnectionPtr = std::shared_ptr<FileConnection>;
using FileSessionPtr = std::shared_ptr<FileSession>;
using FileSessionRef = std::weak_ptr<FileSession>;

#endif // _FILE_FORWARD_H
