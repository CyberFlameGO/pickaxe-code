#include "serverthread.h"
#include <cstdlib>

void ServerThread::run() {
    if(system(command.c_str())) {
        emit runError();
    }
}

void ServerThread::setCommand(std::string command) {
    this->command = command;
}
