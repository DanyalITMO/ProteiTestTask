//
// Created by danyal on 26.06.18.
//

#ifndef PROTEITESTTASK_SYNCERR_H
#define PROTEITESTTASK_SYNCERR_H

#include <sstream>
#include <mutex>

namespace server {

class SyncErr : public std::ostringstream {
   std::mutex _mutex;
public:
   ~SyncErr();
};

}

#endif //PROTEITESTTASK_SYNCERR_H
