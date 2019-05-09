//
// Created by kalos on 28/04/19.
//

#include "rest_server.h"
#include "NotValidURL.h"
#include "NotRunningException.h"

rest_server::rest_server()
{

    utility::string_t port = U("50000");
    utility::string_t address = U("http://192.168.1.120:");
    address.append(port);

    uri_builder uri(address);


    auto addr = uri.to_uri();
    server_listener = new http_listener(addr);
    server_listener->open();
    server_listener->support(methods::GET, std::bind(&rest_server::handle_get, this, std::placeholders::_1));
    server_listener->support(methods::PUT, std::bind(&rest_server::handle_put, this, std::placeholders::_1));
    server_listener->support(methods::POST, std::bind(&rest_server::handle_post, this, std::placeholders::_1));
    server_listener->support(methods::DEL, std::bind(&rest_server::handle_delete, this, std::placeholders::_1));
    sq = synch_queue::get_instance();
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
void rest_server::handle_get(const http_request& message) {
    ucout << message.to_string() << endl;

    //path api/{COMMAND}/{NAME}/S/{SEASON}
    //     api/{COMMAND}/{NAME}/E/{EPISODE}
    //     api/{COMMAND}/[S M H]/{NUMBER}
    //     api/{COMMAND}/P/{NUMBER}
    //     api/{COMMAND}

    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

    message.relative_uri().path();
    try {
        if (!paths.empty()) {

            if (paths[0] == "api") {

                if (paths.size() > 2) {
                    std::unique_ptr<Response> res;

                    if (State_Machine::string_to_command(paths[1]) == PLAY) {

                        if (paths.size() == 5) {

                            std::string name_video = TextOperation::convert_space(paths[2]);

                            TextOperation::vfv_toupper(&paths[3]);

                            if (paths[3] == "S") {

                                Message m(PLAY, name_video, std::strtol(paths[4].c_str(), nullptr, 10), 0,
                                          std::make_pair("none", 0));
                                sq->write_message(m);
                                res = sq->read_response();
                                std::cout << res->getResponse() << std::endl;
                            } else if (paths[3] == "E") {

                                Message m(PLAY, name_video, 0, std::strtol(paths[4].c_str(), nullptr, 10),
                                          std::make_pair("none", 0));
                                sq->write_message(m);
                                res = sq->read_response();
                                std::cout << res->getResponse() << std::endl;
                            } else {
                                throw NotValidURL();
                            }

                        } else
                            throw NotValidURL();

                    }

                    if (State_Machine::string_to_command(paths[1]) == PAUSE) {
                        Message m(PAUSE, "", 0, 0, std::make_pair("none", 0));
                        sq->write_message(m);
                        res = sq->read_response();
                        std::cout << res->getResponse() << std::endl;

                    }

                    if (State_Machine::string_to_command(paths[1]) == STOP) {
                        Message m(STOP, "", 0, 0, std::make_pair("none", 0));
                        sq->write_message(m);
                        res = sq->read_response();
                        std::cout << res->getResponse() << std::endl;

                    }

                    if (State_Machine::string_to_command(paths[1]) == PREVIOUS) {
                        Message m(PREVIOUS, "", 0, 0, std::make_pair("none", 0));
                        sq->write_message(m);
                        res = sq->read_response();
                        std::cout << res->getResponse() << std::endl;

                    }

                    if (State_Machine::string_to_command(paths[1]) == NEXT) {
                        Message m(NEXT, "", 0, 0, std::make_pair("none", 0));
                        sq->write_message(m);
                        res = sq->read_response();
                        std::cout << res->getResponse() << std::endl;

                    }

                    if (State_Machine::string_to_command(paths[1]) == RESUME) {
                        Message m(RESUME, "", 0, 0, std::make_pair("none", 0));
                        sq->write_message(m);
                        res = sq->read_response();
                        std::cout << res->getResponse() << std::endl;

                    }

                    if (State_Machine::string_to_command(paths[1]) == RESTART) {
                        Message m(RESTART, "", 0, 0, std::make_pair("none", 0));
                        sq->write_message(m);
                        res = sq->read_response();
                        std::cout << res->getResponse() << std::endl;

                    }

                    if (State_Machine::string_to_command(paths[1]) == DESTROY) {
                        Message m(DESTROY, "", 0, 0, std::make_pair("none", 0));
                        sq->write_message(m);
                        res = sq->read_response();
                        std::cout << res->getResponse() << std::endl;

                    }

                    if (State_Machine::string_to_command(paths[1]) == TIME) {


                    }

                    if (State_Machine::string_to_command(paths[1]) == PERCENTAGE) {


                    }

                }

            } else {
                message.reply(status_codes::NotFound, U("Requested resource is not available"));
            }
        } else {
            message.reply(status_codes::NotFound, U("Requested resource is not available"));
        }
    } catch (const NotValidURL &nfu) {
        std::cout << nfu.what() << std::endl;

    }
    catch(const NotRunningException &nre) {
        std::cout << nre.what() << std::endl;
    }
}

//
// A POST request
//
void rest_server::handle_post(const http_request& message)
{
    cout <<  message.to_string() << endl;
    message.reply(status_codes::OK,message.to_string());

}

//
// A DELETE request
//
void rest_server::handle_delete(const http_request& message)
{
    ucout <<  message.to_string() << endl;

    string rep = U("WRITE YOUR OWN DELETE OPERATION");
    message.reply(status_codes::OK,rep);

}


//
// A PUT request
//
void rest_server::handle_put(const http_request& message)
{
    ucout <<  message.to_string() << endl;
    string rep = U("WRITE YOUR OWN PUT OPERATION");
    message.reply(status_codes::OK,rep);

}




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