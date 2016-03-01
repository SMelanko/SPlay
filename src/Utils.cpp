#include "Utils.h"

#include <chrono>
#include <string>

namespace utils
{

QList<QMediaContent> FromUrlList(const splay::AudioUrls& urls)
{
	QList<QMediaContent> contents;
	contents.reserve(urls.size());

	for (const auto& url : urls) {
		contents.append(QMediaContent{ url });
	}

	return contents;
}

QString MillisecondsToHhMmSs(const qint64& millisecs)
{
	return SecondsToHhMmSs(
		std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::milliseconds{ millisecs }).count());
}

QString SecondsToHhMmSs(const int& secs)
{
	std::string str;
	std::chrono::seconds duration{secs};

	constexpr char colon{ ':' };
	constexpr char zero{ '0' };

	auto hh = std::chrono::duration_cast<std::chrono::hours>(duration);
	if (hh.count() > 0) {
		str += (std::to_string(hh.count()) + colon);
	}

	auto mm = std::chrono::duration_cast<std::chrono::minutes>(
		duration % std::chrono::hours{ 1 });
	if (hh.count() > 0 && mm.count() < 10) {
		str += zero;
	}
	str += (std::to_string(mm.count()) + colon);

	auto ss = std::chrono::duration_cast<std::chrono::seconds>(
		duration % std::chrono::minutes{ 1 });
	if (ss.count() < 10) {
		str += zero;
	}
	str += std::to_string(ss.count());

	return QString{ str.c_str() };
}

} // namespace utils
