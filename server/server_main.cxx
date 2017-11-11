#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <ctime>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::endpoint tcp_endpoint{ tcp::v4(), 2014 };
tcp::acceptor tcp_acceptor{ ioservice, tcp_endpoint };
tcp::socket tcp_socket{ ioservice };
std::string data;
std::array<char, 4096> bytes;
const char* ptr = "hi server ";
std::vector<int> a{ 1,2,3,4 };
void write();

struct header
{
	int width{ 1280 };
	int height{ 730 };
	int nal_unit{ 13 };
	int key_frame{ 1 };
};

header h{};

void write_handler(const boost::system::error_code &ec,
	std::size_t bytes_transferred) {
	if (!ec) {
		write();
	}
	if (ec)
		tcp_socket.shutdown(tcp::socket::shutdown_send);
}

void read_handler(const boost::system::error_code &ec,
	std::size_t bytes_transferred) {
	if (!ec) {
		std::cout.write(bytes.data(), bytes_transferred);
		//tcp_socket.async_read_some(buffer(bytes), read_handler);
	}
}

void write() {
	//std::time_t now = std::time(nullptr);
	//data = std::ctime(&now);
	//async_write(tcp_socket, buffer(data), write_handler);
	async_write(tcp_socket, buffer(a), write_handler);
	//async_write(tcp_socket, buffer(h), write_handler);
}

void accept_handler(const boost::system::error_code &ec) {
	if (!ec) {
		write();
	/*	std::time_t now = std::time(nullptr);
		data = std::ctime(&now);
		async_write(tcp_socket, buffer(data), write_handler);*/
		tcp_socket.async_read_some(buffer(bytes), read_handler);
		
	}
}

int main() {
	tcp_acceptor.listen();
	tcp_acceptor.async_accept(tcp_socket, accept_handler);
	ioservice.run();
}