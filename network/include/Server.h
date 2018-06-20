//
// Created by danyal on 17.06.18.
//

#ifndef PROTEITESTTASK_SERVER_H
#define PROTEITESTTASK_SERVER_H


class Server {
public:
    explicit Server(int port);
    virtual ~Server();
protected:
    int _listener;

};


#endif //PROTEITESTTASK_SERVER_H
