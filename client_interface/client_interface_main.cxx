#include <iostream>
#include <boost/asio.hpp>
#include "boost/asio/io_service.hpp"
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <array>
#include <string>
#include "common/struct_header.h"
#include "tcp_client.h"

using namespace boost::asio;
using namespace boost::asio::ip;

//io_service ioservice;
//tcp::resolver resolv{ ioservice };
//tcp::socket tcp_socket{ ioservice };
std::array<char, 4096> bytes; 
std::array<int, 4096> a{};
constexpr int header_length{ 8 };
/// Holds an inbound header.
char inbound_header_[header_length];
std::vector<char> inbound_data_;
void write();


//void read_data(const boost::system::error_code &ec, std::size_t bytes_transferred) {
//	std::cout << "data read = " << bytes_transferred << '\n';
//
//}
//
//void read_data_size(const boost::system::error_code &ec,
//	std::size_t bytes_transferred) {
//	if (!ec) {
//		std::istringstream is(std::string(inbound_header_, header_length));
//		std::size_t inbound_data_size = 0;
//		if (!(is >> std::hex >> inbound_data_size))
//		{
//			// Header doesn't seem to be valid. Inform the caller.
//			assert(false);
//		}
//
//		// Start an asynchronous call to receive the data.
//		inbound_data_.resize(inbound_data_size);
//		boost::asio::async_read(tcp_socket, 
//			boost::asio::buffer(inbound_data_),
//			read_data);
//	}
//}
//
//void read_header(const boost::system::error_code &ec, 
//	std::size_t bytes_transferred) {
//	std::string archive_data(&inbound_data_[0], inbound_data_.size());
//	std::istringstream archive_stream(archive_data);
//	boost::archive::text_iarchive archive(archive_stream);
//	struct_header t;
//	archive >> t;
//	//t.print();
//	boost::asio::async_read(tcp_socket, boost::asio::buffer(inbound_header_), read_data_size);
//}
//
//void read_header_len(const boost::system::error_code &ec,
//	std::size_t bytes_transferred) {
//	if (!ec) {
//		std::istringstream is(std::string(inbound_header_, header_length));
//		std::size_t inbound_data_size = 0;
//		if (!(is >> std::hex >> inbound_data_size))
//		{
//			// Header doesn't seem to be valid. Inform the caller.
//			assert(false);
//		}
//		std::cout << "read_header_len = " << inbound_data_size << '\n';
//		// Start an asynchronous call to receive the data.
//		inbound_data_.resize(inbound_data_size);
//		boost::asio::async_read(tcp_socket, boost::asio::buffer(inbound_data_),
//			read_header);
//	}
//}

//void write_handler(const boost::system::error_code &ec,
//	std::size_t bytes_transferred) {
//	if (ec)
//		tcp_socket.shutdown(tcp::socket::shutdown_send);
//}


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
//void write() {
//	std::string data{ "get" };
//	/*
//	This variable is on the stack, 
//	and so it goes out of scope before the asynchronous operation completes. 
//	If you're lucky then the application will crash, but random failures are more likely.
//	*/
//	async_write(tcp_socket, buffer(data), write_handler);
//}



//void connect_handler(const boost::system::error_code &ec) {
//	if (!ec) {
//		boost::asio::async_read(tcp_socket, boost::asio::buffer(inbound_header_), read_header_len);
//		//tcp_socket.aync_(buffer(a), read_handler);
//	}
//}
//
//void resolve_handler(const boost::system::error_code &ec,
//	tcp::resolver::iterator it) {
//	if (!ec)
//		tcp_socket.async_connect(*it, connect_handler);
//}

int main() {
	//tcp::resolver::query q{ "127.0.0.1", "2016" };
	//resolv.async_resolve(q, resolve_handler);
	//ioservice.run();
	wow::tcp_client client_{ 2016 };
}