#pragma once
#if 0
#include <cereal/archives/json.hpp>
#include <fstream>

#include <QtGlobal>

namespace splay
{

//
// SettingsBase class.
//

class SettingsBase
{
public:
	/// Destructor.
	virtual ~SettingsBase() = default;
};

//
// CoreSettings class.
//

class CoreSettings : public SettingsBase
{
public:
	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(mDefaultMediaDir);
	}

private:
	/// Default path to the media for 'Open' action from main menu.
	std::string mDefaultMediaDir;
};

//
// PlaylistSettings class.
//

class PlaylistSettings : public SettingsBase
{
public:
	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(mSavePlaylist);
	}

private:
	/// If true - save current playlist.
	bool mSavePlaylist;
};

//
// ViewSettings class.
//

class ViewSettings : public SettingsBase
{
public:
	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(mSaveColumnProportions);
	}

private:
	/// If true - save column proportions during window resizing.
	bool mSaveColumnProportions;
};

//
// SettingsImpl class
//

class SettingsImpl
{
public:
	SettingsImpl(const std::string& path)
		: mPath{ path }
	{
	}
public:
	/// Loads
	void Load()
	{
		std::ifstream is{ path };
		cereal::JSONInputArchive archive{ is };
		archive(mCore);
		archive(mPlaylist);
		archive(mView);
	}
	/// Saves
	void Save()
	{
		std::ofstream os{ path };
		cereal::JSONOutputArchive archive{ os };
		archive(mCore);
		archive(mPlaylist);
		archive(mView);
	}
private:
	std::string mStream;

	CoreSettings mCore;
	PlaylistSettings mPlaylist;
	ViewSettings mView;
};

//
// Settings class.
//

class Settings
{
public:
	enum class Type
	{
		Core,
		Playlist,
		View
	};

public:
	/// Destructor.
	~Settings() = default;

	/// Disable copy constructor and copy assign operator.
	Q_DISABLE_COPY(Settings);

	/// Disable move constructor and move assign operator.
	Settings(Settings&&) Q_DECL_NOEXCEPT = delete;
	Settings& operator=(Settings&&) Q_DECL_NOEXCEPT = delete;

	/// Returns singleton settings instance.
	static Settings& Instance(const std::string& filename);

private:
	/// Constructor.
	Settings(const std::string& filename);

	/// Loads settings.
	void Load(const std::string& filename);
};

} // namespace splay
#endif
