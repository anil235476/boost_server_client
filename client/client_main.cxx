#include <iostream>
#include "boost/asio/io_service.hpp"
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <array>
#include <string>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::resolver resolv{ ioservice };
tcp::socket tcp_socket{ ioservice };
std::array<char, 4096> bytes; 
std::array<int, 4096> a{};

void write();

void read_handler(const boost::system::error_code &ec,
	std::size_t bytes_transferred) {
	if (!ec) {
		//std::cout.write(bytes.data(), bytes_transferred);
		//tcp_socket.async_read_some(buffer(bytes), read_handler);
		int i{ 0 };
		std::cout << "bytes received = " << bytes_transferred << std::endl;;
		for(int j = 0; j <bytes_transferred; j += 4)
			std::cout << a[i++] << '\n';
		//write();
		tcp_socket.asy
		tcp_socket.async_receive()
		tcp_socket.async_read_some(buffer(a), read_handler);
	}
}

void write_handler(const boost::system::error_code &ec,
	std::size_t bytes_transferred) {
	if (ec)
		tcp_socket.shutdown(tcp::socket::shutdown_send);
}


//socket.non_blocking(true);
//...
//socket.async_read_some(null_buffers(), read_handler);
//...
//void read_handler(boost::system::error_code ec)
//{
//	if (!ec)
//	{
//		std::vector<char> buf(socket.available());
//		socket.read_some(buffer(buf));
//	}
//}

//don't do this
//when you call an asynchronous read or write you need to ensure that 
//the buffers for the operation are valid until the completion handler is called.
void write() {
	std::string data{ "get" };
	/*
	This variable is on the stack, 
	and so it goes out of scope before the asynchronous operation completes. 
	If you're lucky then the application will crash, but random failures are more likely.
	*/
	async_write(tcp_socket, buffer(data), write_handler);
}

void connect_handler(const boost::system::error_code &ec) {
	if (!ec) {
		
		//tcp_socket.async_read_some(buffer(bytes), read_handler);
		tcp_socket.async_read_some(buffer(a), read_handler);
	}
}

void resolve_handler(const boost::system::error_code &ec,
	tcp::resolver::iterator it) {
	if (!ec)
		tcp_socket.async_connect(*it, connect_handler);
}

int main() {
	tcp::resolver::query q{ "127.0.0.1", "2014" };
	resolv.async_resolve(q, resolve_handler);
	ioservice.run();
}