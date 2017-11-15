#ifndef _STRUCT_HEADER_H__
#define _STRUCT_HEADER_H__

struct struct_header
{
	int width_{ 1280 };
	int height_{ 90 };
	int nal_count_{};
	int encoded_frame_size_{};
	bool key_frame_{ false };

	/*void print() {
		std::cout << "width = " << width_ << '\n';
		std::cout << "height = " << height_ << '\n';
	}*/

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & width_;
		ar & height_;
		ar & nal_count_;
		ar & encoded_frame_size_;
		ar & key_frame_;
	}
};

#endif//_STRUCT_HEADER_H__