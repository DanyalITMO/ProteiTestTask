//
// Created by danyal on 26.06.18.
//

#include <iostream>
#include "SyncErr.h"

namespace server {

SyncErr::~SyncErr() {
    std::lock_guard<std::mutex> lock(_mutex);
    std::cerr << this->str();
}
}