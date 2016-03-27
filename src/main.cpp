#include "Application.h"
#include "Logger.h"
#if 0
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#endif
# if 0
struct Record
{
	uint8_t x, y;
	double z;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(x, y, z);
	}
};

struct Data
{
	int32_t id;
	std::string name;
	std::string surname;

	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(CEREAL_NVP(name), CEREAL_NVP(surname));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		static int32_t idGen = 0;
		id = ++idGen;
		ar(name, surname);
	}
};
#endif

int main(int argc, char** argv)
{
	try {
		splay::Application a{ argc, argv };
		return a.exec();
	} catch (const std::exception exc) {
		SPLAY_LOG_ERROR("std::exception has been occurred");
	} catch (...) {
		SPLAY_LOG_ERROR("exception has been occurred");
	}

	return 1;
}

#if 0
	//std::string str{ fmt::format("Hello {}!\n", "Slava") };
	//fmt::print(str);

	SPLAY_LOG_CRITICAL("hello {} logger", "lol");
	std::string tmp{ "hello logger from string" };
	SPLAY_LOG_DEBUG(tmp.c_str());
	SPLAY_LOG_ERROR("hello logger");
	SPLAY_LOG_INFO("hello logger");
	SPLAY_LOG_TRACE("hello logger");
	SPLAY_LOG_WARNING("hello logger");

	std::ofstream os{ "test.json", std::ios::binary };
	cereal::JSONOutputArchive archive{ os };

	Data data;
	data.name = std::move(std::string{ "Slava" });
	data.surname = std::string{ "Melanko" };
	//data.data = std::make_shared<std::unordered_map<uint32_t, Record>>();
	//data.data->insert(std::make_pair<uint32_t, Record>(
	//	123, Record{ 1,2,3.3 }));
	archive(cereal::make_nvp("User", data));
#endif
