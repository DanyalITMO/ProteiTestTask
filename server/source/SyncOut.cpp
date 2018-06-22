//
// Created by danyal on 21.06.18.
//

#include <iostream>
#include "SyncOut.h"

SyncOut::~SyncOut()
{
   std::lock_guard<std::mutex> lock(_mutex);
   std::cout << this->str();
}