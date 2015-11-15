#include <iostream>
#include <cereal\archives\binary.hpp>
#include <cereal\archives\json.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\types\unordered_map.hpp>
#include <fstream>
#include "cppformat\format.h"
#include "spdlog\spdlog.h"
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
#endif
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
#if 0
	template <class Archive>
	void load(Archive& ar)
	{
		static int32_t idGen = 0;
		id = ++idGen;
		ar(name, surname);
	}
#endif
};

int main()
{
	std::string str{ fmt::format("Hello {}!\n", "Slava") };
	fmt::print(str);

	// Create a file rotating logger with 5mb size max and 3 rotated files
	auto log = spdlog::rotating_logger_mt("file_logger", "mylogfile", 10240, 3);
	for (int i = 200; i < 300; ++i)
		log->info("{} * {} equals {:>10}", i, i, i*i);

	std::ofstream os{ "test.json", std::ios::binary };
	cereal::JSONOutputArchive archive{ os };

	Data data;
	data.name = std::move(std::string{ "Slava" });
	data.surname = std::string{ "Melanko" };
	//data.data = std::make_shared<std::unordered_map<uint32_t, Record>>();
	//data.data->insert(std::make_pair<uint32_t, Record>(
	//	123, Record{ 1,2,3.3 }));
	archive(cereal::make_nvp("User", data));

	return 0;
}
