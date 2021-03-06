// serialize_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include "buffer_serializer.h"


template<typename T>
T deserialize(const std::string& v) {
	std::istringstream archive_stream(v);
	boost::archive::text_iarchive archive(archive_stream);
	T t;
	archive >> t;
	return t;
}

std::string test_header(const std::string& v) {
	enum { header_length = 8 };
	std::ostringstream header_stream;
	header_stream << std::setw(header_length)
		<< std::hex << v.size();
	return header_stream.str();

}

struct header {
	int width_{ 1280 };
	int height_{ 90 };
	bool flag_{ false };

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & width_;
		ar & height_;
		ar & flag_;
	}
};

int main()
{
	header h;
	h.width_ = 600;
	h.height_ = 80;
	//const auto a = serialize(h);
	//const auto b = test_header(a);
	//const auto r = deserialize<header>(a);
	const auto r = get_serialze_buffer(h);
	const auto hh = deserialize_buffer<header>(r);
    return 0;
}

