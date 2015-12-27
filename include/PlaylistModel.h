#pragma once

#ifndef _SPLAY_PLAYLIST_MODEL_H_
#define _SPLAY_PLAYLIST_MODEL_H_

#include "Track.h"

#include <QAbstractTableModel>

#include <vector>

namespace splay
{

class PlaylistModel : public QAbstractTableModel
{
	Q_OBJECT
	
public:
	//! Constructor.
	explicit PlaylistModel(QObject* parent = Q_NULLPTR);
	//! Destructor.
	~PlaylistModel() = default;

public:
	//! Returns the number of columns for the children of the given parent.
	int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	//! Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	//! Returns the item flags for the given index.
	Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;
	//! Returns the data for the given role and section in the header with the specified orientation.
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	//! Returns the number of rows under the given parent.
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	//! Returns the drop actions supported by this model.
	Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;

private:
	//! Container of the specified audio files.
	std::vector<Track> mPlaylist;
};

} // namespace splay

#endif // _SPLAY_PLAYLIST_MODEL_H_
