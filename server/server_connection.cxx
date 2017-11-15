#include "server_connection.h"
#include <cassert>
#include <iostream>
#include <array>
#include <boost/asio/buffer.hpp>


using namespace std;
//using boost::asio::ip::tcp;
std::array<char, 4000> buf_receiver_;

namespace wow {
	server_connection::server_connection( int port)
		:port_{port}
		{
	}

	server_connection::~server_connection() {
		stop();
	}

	void server_connection::accept() {
	
		session_->acceptor_.async_accept(session_->socket_,
			boost::bind(&server_connection::accept_handler, this,
				boost::asio::placeholders::error)
		);
	}

	void server_connection::start() {

		keep_listen = true;
		int i = 0;
		
		{
			thread_ = thread{ [this]() {
				while (keep_listen) {

					{ lock_guard<mutex> lck_{ sesson_lock_ };
						session_.reset(nullptr);
						session_ = make_unique<internal::session>(port_);
					}
					sender_interface_.reset(nullptr);
					accept();
					session_->run();
					if (callback_)
						callback_->remove_event();
				}
				
			} };
			
		}
	}

	void server_connection::stop() {
		keep_listen = false;
		//todo: this code still has thread safety issue
		{ lock_guard<mutex> lck_{ sesson_lock_ };
			if (session_)
				session_->stop();
		}
		//todo above code should be thread safe
		thread_.join();

	}

	void server_connection::accept_handler(const boost::system::error_code &ec ) {
		std::cout << "accept handler 1 \n";
		if (!ec) {
			std::cout << "accept handler \n";
			sender_interface_ = make_unique<internal::sender_interface>(
				session_->socket_);
			session_->socket_.async_receive(boost::asio::buffer(buf_receiver_),
				boost::bind(&server_connection::read_handler, 
					this,
					boost::asio::placeholders::error, 
					boost::asio::placeholders::bytes_transferred)
			);
			if (callback_) 
				callback_->add_event();
		}
	}

	void server_connection::register_callback(connection_events * callback) {
		assert(callback_ == nullptr);
		callback_ = callback;
	}

	void server_connection::handle_write(
		const boost::system::error_code& e /*, std::size_t bytes_transferred*/){
		std::cout << "error code " << e;
		if (e) {
			std::cout << "error event\n";
		}
	}

	void server_connection::read_handler(const boost::system::error_code &ec,
		std::size_t bytes_transferred) {
		std::cout << "read_handler" << ec << '\n';
	}
}