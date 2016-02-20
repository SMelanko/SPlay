#pragma once

#ifndef _SPLAY_PLAYLIST_MODEL_H_
#define _SPLAY_PLAYLIST_MODEL_H_

#include "Types.h"

#include <QAbstractTableModel>

namespace splay
{

class PlaylistModel : public QAbstractTableModel
{
	Q_OBJECT
	
public:
	//! Constructor.
	explicit PlaylistModel(QObject* parent = Q_NULLPTR);
	//! Destructor.
	virtual ~PlaylistModel() = default;

	//! Disable copy constructor and copy assign operator.
	Q_DISABLE_COPY(PlaylistModel)

public:
	//! Adds media content items to the playlist.
	void Add(const AudioUrls& urls);
	//! Opens new list of the media files and removes previous one.
	void Open(const AudioUrls& urls);
	//! Returns playlist pointer.
	Playlist* PlaylistPtr() Q_DECL_NOEXCEPT;

Q_SIGNALS:
	/// Emits new index.
	void NewIndex(int val);

public Q_SLOTS:
	//! Plays a media according to the new index.
	void OnMediaIndexChanged(int newIndex);
	//! TODO Inserts tracks into the end of model.
	void OnInsert(AudioUrls urls);
	//! TODO Executes internal moving of the rows.
	void OnMove(RowList selectedRows, int dest);
	//! Advances to the next media content in playlist.
	void OnNext();
	//! Advances to the previous media content in playlist.
	void OnPrevious();
	//! TODO Remove specified rows from view.
	void OnRemove(RowList selectedRows);

protected:
	//! Returns the number of columns for the children of the given parent.
	int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	//! Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index,
		int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	//! Returns the item flags for the given index.
	Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;
	//! Returns the data for the given role and section in the header.
	QVariant headerData(int section,
		Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	//! Returns the list of allowed MIME types.
	QStringList mimeTypes() const Q_DECL_OVERRIDE;
	//! Returns the number of rows under the given parent.
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	//! Returns the drop actions supported by this model.
	Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;

private:
	//! Removes all the items from the playlist.
	void _Clear();

private Q_SLOTS:
	//! Receives new media position from media playlist.
	void _OnCurrentIndexChanged(int val);

private:
	//! Container of the specified audio files.
	Playlist mData;
};

//
// Inline implementation.
//

inline Playlist* PlaylistModel::PlaylistPtr() Q_DECL_NOEXCEPT
{
	return &mData;
}
} // namespace splay

#endif // _SPLAY_PLAYLIST_MODEL_H_
