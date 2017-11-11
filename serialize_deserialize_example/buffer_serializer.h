#ifndef _BUFFER_SERIALIZER_H__
#define _BUFFER_SERIALIZER_H__
#include <vector>
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>

constexpr int HEADER_LEN{ 8 };//header len is fixed.

namespace internal{
	template<typename T>
	std::string serialize(const T& t) {
		std::ostringstream archive_stream;
		boost::archive::text_oarchive archive(archive_stream);
		archive << t;
		return archive_stream.str();
	}
}
template< typename T> 
std::vector<char> get_serialze_buffer(const T& t) {
	const auto r = internal::serialize(t);

	// Format the header.
	std::ostringstream header_stream;
	header_stream << std::setw(HEADER_LEN)
		<< std::hex << r.size();
	if (!header_stream || header_stream.str().size() != HEADER_LEN)
	{
		throw std::runtime_error{ "something went wrong" };
	}

	std::vector<char> ret;
	const auto h = header_stream.str();
	std::copy(h.begin(), h.end(), std::back_inserter(ret));
	std::copy(begin(r), end(r), std::back_inserter(ret));

	return ret;
}

template<typename T>
T deserialize_buffer(const std::vector<char>& b) {
	//read header first
	char header_str[HEADER_LEN];
	std::copy(begin(b), begin(b) + HEADER_LEN, header_str);
	std::istringstream is(std::string(header_str, HEADER_LEN));
	std::size_t inbound_data_size = 0;
	if (!(is >> std::hex >> inbound_data_size))
	{
		throw std::runtime_error{ "something went wrong" };
	}
	std::string archive_data(&b[HEADER_LEN], inbound_data_size);
	std::istringstream archive_stream(archive_data);
	boost::archive::text_iarchive archive(archive_stream);
	T t;
	archive >> t;
	return t;
}

#endif//_BUFFER_SERIALIZER_H__
