//
// Created by danyal on 21.06.18.
//

#ifndef PROTEITESTTASK_SYNCOUT_H
#define PROTEITESTTASK_SYNCOUT_H

#include <sstream>
#include <mutex>

namespace server {

class SyncOut : public std::ostringstream {
    std::mutex _mutex;
public:
    ~SyncOut();
};
}
#endif //PROTEITESTTASK_SYNCOUT_H