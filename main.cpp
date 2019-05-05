#include <iostream>
#include "synch_queue.h"
#include "message.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "vlc_manager.h"
#include "rest_server.h"



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

    synch_queue *sq = nullptr;
    Costants k(argv[1], argv[2]);
    std::thread vlc(&vlc_manager::controller , k);
    sq = synch_queue::get_instance();
    //rest_server restServer;


    std::unique_ptr<Response> res;
    Message m(FF, "", 0, 0, 0); //microsecondi
    sq->write_message(m);
    res = sq->read_response();
    std::cout << res->getResponse() << std::endl;

    /*int i = random()%15+2;
    std::cout << std::to_string(i) << std::endl;
    sleep (i);*/
    Message m2(PLAY, "a", 0, 4, 0);
    sq->write_message(m2);
    res = sq->read_response();
    std::cout << res->getResponse() << std::endl;
//

    sleep (5);
    Message m3(PLAY, "a",  0, 2, 0);
    sq->write_message(m3);
    res = sq->read_response();
    std::cout << res->getResponse() << std::endl;
//
    sleep (5);
    Message m4(STOP, "", 0, 0, 0);
    sq->write_message(m4);
    res = sq->read_response();
    std::cout << res->getResponse() << std::endl;

//    sleep (5);
//    Message m5(REW, "", "", 0, 0, 500);
//    sq->write_message(m5);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    sleep (5);
//    Message m6(STOP, "", "", 0, 0, 0);
//    sq->write_message(m6);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    std::string path2;
//    path2.append(path_series);
//    path2.append("/series/a/1/aS1E3.mp4");
//    sleep (5);
//    Message m7(PLAY, path2, "a", 1, 3, 50000);
//    sq->write_message(m7);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    sleep (5);
//    Message m8(NEXT, "", "", 0, 0, 0);
//    sq->write_message(m8);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//
//    sleep (5);
//    Message m9(DESTROY, "", "", 0, 0, 0);
//    sq->write_message(m9);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//
//    sleep (5);
//    Message m10(NEXT, "", "", 0, 0, 0);
//    sq->write_message(m10);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//
//    sleep (5);
//    Message m11(NEXT, "", "", 0, 0, 0);
//    sq->write_message(m11);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    sleep (5);
//    Message m12(NEXT, "", "", 0, 0, 0);
//    sq->write_message(m12);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    sleep (5);
//    Message m13(PREVIOUS, "", "", 0, 0, 0);
//    sq->write_message(m13);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    sleep (5);
//    Message m14(PREVIOUS, "", "", 0, 0, 0);
//    sq->write_message(m14);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//
//    sleep (5);
//    Message m15(PREVIOUS, "", "", 0, 0, 0);
//    sq->write_message(m15);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//
//    sleep (5);
//    Message m16(PREVIOUS, "", "", 0, 0, 0);
//    sq->write_message(m16);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//
//    sleep (5);
//    Message m17(PREVIOUS, "", "", 0, 0, 0);
//    sq->write_message(m17);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    sleep (5);
//    Message m18(PREVIOUS, "", "", 0, 0, 0);
//    sq->write_message(m18);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;
//
//    sleep (5);
//    Message m19(PREVIOUS, "", "", 0, 0, 0);
//    sq->write_message(m19);
//    res = sq->read_response();
//    std::cout << res->getResponse() << std::endl;





    vlc.join();

    return 0;
}