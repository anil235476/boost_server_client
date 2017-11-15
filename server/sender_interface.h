#ifndef _SENDER_INTERFACE_H__
#define _SENDER_INTERFACE_H__
#include <boost/asio.hpp>
#include <vector>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>


namespace internal{
	class sender_interface {
	public:
		sender_interface(boost::asio::ip::tcp::socket& socket)
			: socket_(socket)
		{
		}

		
		std::string get_header(std::size_t len) {
			// Format the header.
			std::ostringstream header_stream;
			header_stream << std::setw(header_length)
				<< std::hex << len;
			return header_stream.str();
		}

		template<typename T, typename Handler>
		void async_send_struct(const T&t, Handler handler) {
			// Serialize the data first so we know how large it is.
			std::ostringstream archive_stream;
			boost::archive::text_oarchive archive(archive_stream);
			archive << t;
			outbound_struct_ = archive_stream.str();

			outbound_struct_header_ =  get_header(outbound_struct_.size());
			if (outbound_struct_header_.size() != header_length) {

				// Something went wrong, inform the caller.
				boost::system::error_code error(boost::asio::error::invalid_argument);
				socket_.get_io_service().post(boost::bind(handler, error));
				return;
			}


			// Write the serialized data to the socket. We use "gather-write" to send
			// both the header and the data in a single write operation.
			std::vector<boost::asio::const_buffer> buffers;
			buffers.push_back(boost::asio::buffer(outbound_struct_header_));
			buffers.push_back(boost::asio::buffer(outbound_struct_));
			boost::asio::async_write(socket_, buffers, handler);
		}

		template<typename Handler>
		void async_send_data(std::vector<char>&& data, Handler handler) {
			outbound_data_ = std::move(data);
			outbound_data_header_ = get_header(outbound_data_.size());
			if (outbound_data_header_.size() != header_length) {

				// Something went wrong, inform the caller.
				boost::system::error_code error(boost::asio::error::invalid_argument);
				socket_.get_io_service().post(boost::bind(handler, error));
				return;
			}
			std::vector<boost::asio::const_buffer> buffers;
			buffers.push_back(boost::asio::buffer(outbound_data_header_));
			buffers.push_back(boost::asio::buffer(&outbound_data_[0], outbound_data_.size()));
			boost::asio::async_write(socket_, buffers, handler);
		}
	
	private:
		/// The underlying socket.
	//	std::shared_ptr<boost::asio::ip::tcp::socket > socket_;
		boost::asio::ip::tcp::socket& socket_;
		/// Holds an outbound header.
		std::string outbound_struct_header_;
		std::string outbound_data_header_;

		/// Holds the outbound data.
		//std::string outbound_data_;
		std::string outbound_struct_;
		std::vector<char> outbound_data_;

		/// The size of a fixed length header.
		enum { header_length = 8 };
	};
}


#endif//_SENDER_INTERFACE_H__