//
// Created by kalos on 28/04/19.
//

#include "rest_server.h"

rest_server::rest_server()
{

    utility::string_t port = U("50000");
    utility::string_t address = U("http://192.168.1.109:");
    address.append(port);

    uri_builder uri(address);


    auto addr = uri.to_uri();
    server_listener = new http_listener(addr);
    server_listener->open();
    server_listener->support(methods::GET, std::bind(&rest_server::handle_get, this, std::placeholders::_1));
    server_listener->support(methods::PUT, std::bind(&rest_server::handle_put, this, std::placeholders::_1));
    server_listener->support(methods::POST, std::bind(&rest_server::handle_post, this, std::placeholders::_1));
    server_listener->support(methods::DEL, std::bind(&rest_server::handle_delete, this, std::placeholders::_1));

    cout << utility::string_t(U("Listening for requests at: ")) << addr.to_string() << std::endl;

}

rest_server::~rest_server() {
    server_listener->close();
    delete server_listener;
}

void rest_server::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request
//
void rest_server::handle_get(const http_request& message)
{
    ucout <<  message.to_string() << endl;

    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    message.relative_uri().path();

    if(!paths.empty()){
        if(paths[0] == "list_film"){
            std::cout << getenv("USER") << std::endl;
            sq = synch_queue::get_instance();
            std::string path;
            path.append(path_series);
            path.append("/series/a/1/aS1E1.mp4");

            std::unique_ptr<Response> res;
            Message m(PLAY, path, "a", 1, 1, 0); //microsecondi
            sq->write_message(m);
            res = sq->read_response();
            std::cout << res->getResponse() << std::endl;

//            concurrency::streams::fstream::open_istream(U("list.json"), std::ios::in).then([=](concurrency::streams::istream is)
//               {
//                   message.reply(status_codes::OK, is,  U("raw"))
//                           .then([](pplx::task<void> t)
//                                 {
//                                     try{
//                                         t.get();
//                                     }
//                                     catch(...){
//                                         //
//                                     }
//                                 });
//               }).then([=](pplx::task<void>t)
//                       {
//                           try{
//                               t.get();
//                           }
//                           catch(...){
//                               message.reply(status_codes::InternalError,U("INTERNAL ERROR "));
//                           }
//                       });

        }
        else{
            message.reply(status_codes::NotFound,U("Requested resource is not available"));
        }
    }
    else{
        message.reply(status_codes::NotFound,U("Requested resource is not available"));
    }
}

//
// A POST request
//
void rest_server::handle_post(const http_request& message)
{
    cout <<  message.to_string() << endl;
    message.reply(status_codes::OK,message.to_string());

};

//
// A DELETE request
//
void rest_server::handle_delete(const http_request& message)
{
    ucout <<  message.to_string() << endl;

    string rep = U("WRITE YOUR OWN DELETE OPERATION");
    message.reply(status_codes::OK,rep);

};


//
// A PUT request
//
void rest_server::handle_put(const http_request& message)
{
    ucout <<  message.to_string() << endl;
    string rep = U("WRITE YOUR OWN PUT OPERATION");
    message.reply(status_codes::OK,rep);

};