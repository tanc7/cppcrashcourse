#include <iostream>
#include <boost/asio.hpp>

//int main() {
//    boost::asio::io_context io_context;
//    boost::asio::ip::tcp::resolver resolver { io_context };
//    boost::system::error_code ec;
//    for (auto&& result : resolver.resolve("www.nostarch.com", "http", ec)) {
//        std::cout << result.service_name() <<  " "
//        << result.host_name() << " "
//        << result.endpoint() << " "
//        << std::endl;
//    }
//    if (ec) std::cout << "Error code: " << ec << std::endl;
////    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
int main() {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver { io_context };
    resolver.async_resolve("www.nostarch.com", "http", [](boost::system::error_code ec, const auto& results) {
        if (ec) {
            std::cerr << "Error: " << ec << std::endl;
            return;
        }
        for (auto&& result : results) {
            std::cout << result.service_name() << " "
            << result.host_name() << " "
            << result.endpoint() << " "
            << std::endl;
        }

    }
    );
    io_context.run();
}
