#include "server_connection.h"
#include <cassert>
#include <iostream>
#include <array>
#include <boost/asio/buffer.hpp>

using namespace std;
using boost::asio::ip::tcp;
std::array<char, 4000> buf_receiver_;
namespace wow {
	server_connection::server_connection( int port)
		: acceptor_(io_service_,
			boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	{
		
			
		
	}

	void server_connection::accept() {
		std::shared_ptr<tcp::socket> tcp_socket = make_shared<tcp::socket>(io_service_);

		acceptor_.async_accept(*tcp_socket,
			boost::bind(&server_connection::accept_handler, this,
				boost::asio::placeholders::error, tcp_socket)
		);
	}

	void server_connection::start() {
		keep_listen = true;
		thread_ = thread{ [this] {
			while (this->keep_listen) {
				this->accept();
				//io_service_.run_one();
				this->io_service_.run();
			}
		} };
		
	}

	void server_connection::accept_handler(const boost::system::error_code &ec, std::shared_ptr<tcp::socket> p) {
		std::cout << "accept handler 1 \n";
		if (!ec) {
			std::cout << "accept handler \n";
			sender_interface_ = make_unique<internal::sender_interface>(p);
			p->async_receive(boost::asio::buffer(buf_receiver_),
				boost::bind(&server_connection::read_handler, this, boost::asio::placeholders::error)
			);
			if (callback_) 
				callback_->add_event();
			

		}
	}

	void server_connection::register_callback(connection_events * callback) {
		assert(callback_ == nullptr);
		callback_ = callback;
	}

	void server_connection::handle_write(const boost::system::error_code& e)
	{
		std::cout << "error code " << e;
		if (e) {
			std::cout << "error event\n";
			if (callback_)
				callback_->remove_event();
			start();

		}
			
	}

	void server_connection::read_handler(const boost::system::error_code &ec/*,
		std::size_t bytes_transferred*/) {
		std::cout << "read_handler" << ec << '\n';
		//assert(false);
	}
}