#include <iostream>
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver  resolver{io_context};
    boost::asio::ip::tcp::socket {io_context};
//    boost::asio::async_connect(
//            socket,
//            resolver.resolve("www.nostarch", "http"),
//            [] (boost::system::error_code ec, const auto& endpoint) {
//                std::cout << endpoint;
//            });
// deprecated
    boost::asio::async_connect(socket,
    resolver.resolve("www.nostarch.com", "http"),
    [] (boost::system::error_code ec, const auto& endpoint){
        std::cout << endpoint;
    });
    io_context.run();
    //std::cout << "Hello, World!" << std::endl;
    //return 0;
}
