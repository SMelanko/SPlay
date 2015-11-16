#include <iostream>
#include <cereal\archives\binary.hpp>
#include <cereal\archives\json.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\types\unordered_map.hpp>
#include <fstream>
#include "cppformat\format.h"
#include "Logger.h"
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
	decltype(auto) logger = splay::log::Logger::GetInstance();

	splay::log::Logger::GetInstance().Ref()->debug() << "asd";
	splay::log::Logger::GetInstance().Ref()->debug() << "qwe";
	splay::log::Logger::GetInstance().Ref()->debug() << "123";
	
	//for (int i = 100; i < 200; ++i)
	//	LOG_TRACE << i << " * " << i << " = " << i * i;
#if 0
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
	return 0;
}
