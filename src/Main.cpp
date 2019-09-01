#include <iostream>
#include <unistd.h>
#include "synchronization/ConcurrentQueue.h"
#include "player/VlcManager.h"
#include "network/RestServer.h"
#include "utils/StateMachine.h
#include <thread>



int main(int argc, char ** argv) {


    std::string address;
    std::string path;

    if (argc == 1){
        std::cout << "Not enough params, please relaunch with --help" << std::endl;
        return -1;
    }

    if(strcasecmp(argv[1],"--help") == 0){
        std::cout << "VfV is a simple application that allow to command vlc from IFTTT, read the README file" <<
        "to know more\nIn order to start VfV specify the local IP address of your device and the absolute path of" <<
        "your videos folder" << std::endl;

        std::cout << "Example: ./Voice_for_VLC 192.168.1.1 /home/user/videos" << std::endl;
        return 1;

    }

    if(argc != 3){
        std::cout << "Not enough params, please relaunch with --help" << std::endl;
        return -1;
    }

    VlcManager vlc;

    std::thread threadVlc(&VlcManager::controller, &vlc);
    rest_server restServer;

    threadVlc.join();

    return 0;
}