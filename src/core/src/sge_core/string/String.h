#pragma once

#include "../base/sge_base.h"
#include "Fmt.h"

namespace sge {

class StringUtil {
public:
	static void binToHex(String& result, Span<u8> data) {
		result.clear();
		appendBinToHex(result, data.data(), data.size());
	}

	static void appendBinToHex(String& result, const u8* data, size_t dataSize);
};

} // namespace

inline
std::ostream& operator<<(std::ostream& s, const sge::StrView& v) {
	s.write(v.data(), v.size());
	return s;
}

template<>
struct fmt::formatter<sge::StrView> {
	auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
	auto format(const sge::StrView& v, fmt::format_context& ctx) {
		auto it = *ctx.out();
		for (const auto& c : v) {
			it = c;
			it++;
		}
		return ctx.out();
	}
};

template<>
struct fmt::formatter<sge::String> {
	auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
	auto format(const sge::String& v, fmt::format_context& ctx) {
		sge::StrView view(v.data(), v.size());
		return fmt::format_to(ctx.out(), "{}", view);
	}
};
