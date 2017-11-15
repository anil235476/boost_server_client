#ifndef _SERVER_CONNECTION_H_
#define _SERVER_CONNECTION_H_
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <memory>
#include "sender_interface.h"
#include <iostream>
#include <thread>
#include "session.h"
#include <mutex>


namespace wow {
	
	class connection_events {
	public:
		virtual void add_event() = 0;
		virtual void remove_event() = 0;
	};

	class server_connection {
	public:
		server_connection( int port);
		~server_connection();
		void register_callback(connection_events * callback);
		void start();
		template<typename T>
		void send_data(std::vector<char>&& data, const T& t) {
			if (sender_interface_) {
				sender_interface_->async_send_struct(t, boost::bind(&server_connection::handle_write, 
					this, boost::asio::placeholders::error)
					);
				sender_interface_->async_send_data(move(data),
					boost::bind(&server_connection::handle_write,
						this, boost::asio::placeholders::error)
				);
			}
			
		}

	private:
		//handler

		void accept_handler(const boost::system::error_code &ec);
		/// Handle completion of a write operation.
		void handle_write(const boost::system::error_code& e/*,
			std::size_t bytes_transferred*/);
		void read_handler(const boost::system::error_code &ec,
			std::size_t bytes_transferred);
	private:
		void accept();
		void stop();
		bool keep_listen{ false };
		connection_events * callback_{ nullptr };
		const int port_{};

		std::unique_ptr<internal::sender_interface> sender_interface_;
		std::unique_ptr<internal::session> session_;
		std::mutex sesson_lock_;

		std::thread thread_;
	};

}


#endif//_SERVER_CONNECTION_H_