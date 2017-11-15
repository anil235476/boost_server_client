#ifndef _SESSION_H__
#define _SESSION_H__
#include <boost/asio.hpp>

namespace internal{
	class session
	{
	public:
		session(int port) :acceptor_{ io_service_,
			boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port) }
			, socket_{ io_service_ } {
		}

		void run() {
			io_service_.run();
		}

		void stop() {
			io_service_.stop();
		}

		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::socket socket_;
		/// The acceptor object used to accept incoming socket connections.
		boost::asio::ip::tcp::acceptor acceptor_;
	};
}//namespace internal


#endif//_SESSION_H__