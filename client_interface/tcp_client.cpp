#include "tcp_client.h"
#include <cassert>
#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "common/struct_header.h"
#include <boost/bind/bind.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;



namespace wow
{

	tcp_client::tcp_client(int port) {

		tcp::resolver::query q{ "127.0.0.1", "2016" };
	
		resolv_.async_resolve(
			q, boost::bind(
				&tcp_client::resolve_handler, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator
			)
		);

		ioservice_.run();
	}

	void tcp_client::resolve_handler(const boost::system::error_code &ec,
		tcp::resolver::iterator it) {
		if (!ec)
			tcp_socket_.async_connect(*it,
				boost::bind( &tcp_client::connect_handler, this,
					boost::asio::placeholders::error));
	}

	void tcp_client::connect_handler(const boost::system::error_code &ec) {
		if (!ec) {
			//header_len_reader a{ this };
			boost::asio::async_read(tcp_socket_,
				boost::asio::buffer(inbound_header_),
				boost::bind(
					&tcp_client::read_header_len,
					this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
				)
			);
		}
	}

	void tcp_client::read_header_len(const boost::system::error_code &ec,
		std::size_t bytes_transferred) {
		if (!ec) {
			std::istringstream is(std::string(inbound_header_, HEADER_LEN));
			std::size_t inbound_data_size = 0;
			if (!(is >> std::hex >> inbound_data_size)) {
				// Header doesn't seem to be valid. Inform the caller.
				assert(false);
			}
			std::cout << "read_header_len = " << inbound_data_size << '\n';
			// Start an asynchronous call to receive the data.
			inbound_data_.resize(inbound_data_size);
			//header_reader a{ this };
			boost::asio::async_read(tcp_socket_,
				boost::asio::buffer(inbound_data_),
				boost::bind(
					&tcp_client::read_header, this,
					boost::placeholders::_1, boost::placeholders::_2)
			);
		}
	}

	void tcp_client::read_header(const boost::system::error_code &ec,
		std::size_t bytes_transferred) {
		std::string archive_data(&inbound_data_[0], inbound_data_.size());
		std::istringstream archive_stream(archive_data);
		boost::archive::text_iarchive archive(archive_stream);
		struct_header t;
		archive >> t;
		//t.print();
		//data_size_reader a{ this };
		boost::asio::async_read(tcp_socket_, boost::asio::buffer(inbound_header_),
			boost::bind(
				&tcp_client::read_data_size, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)
		);
	}

	void tcp_client::read_data_size(const boost::system::error_code &ec,
		std::size_t bytes_transferred) {
		if (!ec) {
			std::istringstream is(std::string(inbound_header_, HEADER_LEN));
			std::size_t inbound_data_size = 0;
			if (!(is >> std::hex >> inbound_data_size)) {
				// Header doesn't seem to be valid. Inform the caller.
				assert(false);
			}

			// Start an asynchronous call to receive the data.
			inbound_data_.resize(inbound_data_size);
			//data_reader a{ this };
			boost::asio::async_read(tcp_socket_,
				boost::asio::buffer(inbound_data_),
				boost::bind(&tcp_client::read_data,
					this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)
			);
		}
	}

	void tcp_client::read_data(const boost::system::error_code &ec,
		std::size_t bytes_transferred) {
		std::cout << "data read = " << bytes_transferred << '\n';

	}

}