//
// Created by ctlister on 1/26/23.
//
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <memory>

using namespace boost::asio;

struct Session : std::enable_shared_from_this<Session> {
    explicit Session(ip::tcp::socket socket) : socket{ std::move(socket) } { }
    void read() {
        async_read_until(socket, dynamic_buffer(message), '\n',
                         [self=shared_from_this()] (boost::system::error_code ec,
                                                    std::size_t length) {
                             if (ec || self->message == "\n") return;
                             boost::algorithm::to_upper(self->message);
                             self->write();
                         });
    }
    void write() {
        async_write(socket, buffer(message),
                    [self=shared_from_this()] (boost::system::error_code ec, std::size_t length) {
                        if (ec) return;
                        self->message.clear();
                        self->read();
                    });
    }
private:
    ip::tcp::socket socket;
    std::string message;
};

void serve(ip::tcp::acceptor& acceptor) {
    acceptor.async_accept(
            [&acceptor](boost::system::error_code ec, ip::tcp::socket socket) {
                serve(acceptor);
                if (ec) return;
                auto session = std::make_shared<Session>(std::move(socket));
            }
            );
}

int main() {
    try {
        io_context io_context;
        ip::tcp::acceptor acceptor{ io_context,
                                    ip::tcp::endpoint(ip::tcp::v4(), 1895) };
        serve(acceptor);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}