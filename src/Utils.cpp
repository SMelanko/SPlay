#include "Utils.h"

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

} // namespace utils
