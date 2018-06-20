//
// Created by danyal on 19.06.18.
//

#ifndef PROTEITESTTASK_CLIENT_H
#define PROTEITESTTASK_CLIENT_H

#include "string"

class Client {
public:
   virtual ~Client() = default;
   virtual void send(const std::string& msg) = 0;
   virtual std::string recv() = 0;
};

#endif //PROTEITESTTASK_CLIENT_H
