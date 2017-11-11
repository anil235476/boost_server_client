// serialize_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>

template<typename T>
std::string serialize(const T& t) {
	std::ostringstream archive_stream;
	boost::archive::text_oarchive archive(archive_stream);
	archive << t;
	return archive_stream.str();
}

template<typename T>
T deserialize(const std::string& v) {
	std::istringstream archive_stream(v);
	boost::archive::text_iarchive archive(archive_stream);
	T t;
	archive >> t;
	return t;
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
	const auto a = serialize(h);
	const auto r = deserialize<header>(a);
    return 0;
}

