#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <boost/asio.hpp>
#include "boost/asio/io_service.hpp"
#include <boost/asio/ip/tcp.hpp>

constexpr int HEADER_LEN{ 8 };

namespace wow
{
	class tcp_client
	{
	public:
		tcp_client(int port);

	private:
		//handler
		void resolve_handler(const boost::system::error_code &ec,
			boost::asio::ip::tcp::resolver::iterator it);
		void connect_handler(const boost::system::error_code &ec);
		void read_header_len(const boost::system::error_code &ec,
			std::size_t bytes_transferred);
		void read_header(const boost::system::error_code &ec,
			std::size_t bytes_transferred);
		void read_data_size(const boost::system::error_code &ec,
			std::size_t bytes_transferred);
		void read_data(const boost::system::error_code &ec,
			std::size_t bytes_transferred);
		

	private:
		boost::asio::io_service ioservice_;
		boost::asio::ip::tcp::resolver resolv_{ ioservice_ };
		boost::asio::ip::tcp::socket tcp_socket_{ ioservice_ };
		
		/// Holds an inbound header.
		char inbound_header_[HEADER_LEN];
		std::vector<char> inbound_data_;
	};
}


#endif//_TCP_CLIENT_H_