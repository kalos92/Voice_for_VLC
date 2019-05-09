//
// Created by kalos on 28/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_REST_SERVER_H
#define GOOGLE_ASSISTANT_FOR_VLC_REST_SERVER_H

#include <cpprest/http_listener.h>
#include <cpprest/asyncrt_utils.h>
#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/json.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"
#include "cpprest/producerconsumerstream.h"
#include "synch_queue.h"
#include "TextOperation.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class rest_server {

    public:
        rest_server();
        ~rest_server();

    private:
        http_listener *server_listener;
        void handle_get(const http_request& message);
        void handle_put(const http_request& message);
        void handle_post(const http_request& message);
        void handle_delete(const http_request& message);
        void handle_error(pplx::task<void>& t);
        synch_queue *sq;
        pplx::task<void>open(){return server_listener->open();}
        pplx::task<void>close(){return server_listener->close();}


};


#endif //GOOGLE_ASSISTANT_FOR_VLC_REST_SERVER_H
