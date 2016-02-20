#include "PlaylistModel.h"
#include "Utils.h"

#include <fileref.h>

#include <QDataStream>
#include <QDebug>
#include <QMimeData>
#include <QPixmap>

namespace splay
{

PlaylistModel::PlaylistModel(QObject* parent)
	: QAbstractTableModel{ parent }
	, mData{}
{
	mData.setPlaybackMode(QMediaPlaylist::Loop);

	connect(&mData, &QMediaPlaylist::currentIndexChanged,
		this, &PlaylistModel::_OnCurrentIndexChanged);
}

void PlaylistModel::Add(const AudioUrls& urls)
{
	Q_EMIT layoutAboutToBeChanged();

	auto oldModelIndex = QModelIndex();

	if (!mData.addMedia(utils::FromUrlList(urls))) {
		throw std::runtime_error{ mData.errorString().toStdString() };
	}

	changePersistentIndex(oldModelIndex, QModelIndex());

	Q_EMIT layoutChanged();
}

int PlaylistModel::columnCount(const QModelIndex& parent) const
{
	// Note! When implementing a table based model,
	// columnCount() should return 0 when the parent is valid.
	return parent.isValid() ? 0 : 4;
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	const auto row(index.row());
	const auto column(index.column());

	if (row >= static_cast<int>(mData.mediaCount())) {
		return QVariant();
	}

	TagLib::FileRef f{ mData.media(row).canonicalUrl().toLocalFile().toStdString().c_str() };

	if (role == Qt::DisplayRole) {
		switch (column) {
			case 1: {
				if (!f.isNull() && f.tag()) {
					return QVariant(f.tag()->artist().toCString());
				}
			}
			case 2: {
				if (!f.isNull() && f.tag()) {
					return QVariant(f.tag()->title().toCString());
				}
			}
			case 3: {
				if (!f.isNull() && f.audioProperties()) {
					return QVariant(f.audioProperties()->length());
				}
			}
		}
	}

	return QVariant();
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex& index) const
{
	auto defFlags = QAbstractTableModel::flags(index);

	if (index.isValid()) {
		return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defFlags;
	}
	else {
		return Qt::ItemIsDropEnabled | defFlags;
	}
}

QVariant PlaylistModel::headerData(int section,
	Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QLatin1String("Playing");
			case 1:
				return QLatin1String("Author");
			case 2:
				return QLatin1String("Title");
			case 3:
				return QLatin1String("Duration");
			}
		}
	}

	return QVariant();
}

QStringList PlaylistModel::mimeTypes() const
{
	QStringList types;
	types << "application/splay-track";
	return types;
}

void PlaylistModel::OnMediaIndexChanged(int newIndex)
{
	mData.setCurrentIndex(newIndex);
}

void PlaylistModel::OnInsert(AudioUrls urls)
{
	Add(urls);

	if (mData.currentIndex() == -1) {
		mData.setCurrentIndex(0);
	}
}

void PlaylistModel::OnMove(RowList selectedRows, int dest)
{
	Q_EMIT layoutAboutToBeChanged();

	auto oldModelIndex = index(selectedRows[0], -1);

	QList<QMediaContent> tmp;
	for (const auto& row : selectedRows) {
		// Copy moving row into the temporary vector.
		tmp.push_back(mData.media(row));
		// Delete this row directly from the current playlist.
		mData.removeMedia(row);
	}

	if (dest > static_cast<int>(mData.mediaCount()))
		dest = mData.mediaCount();

	int coef = 0;
	if (selectedRows[0] < dest) {
		coef = -1;
	}

	// Move selected rows to the destination.
	if (!mData.insertMedia(dest + coef, tmp)) {
		qDebug() << "PlaylistModel::OnMove: Insert media failed.";
		return;
	}

	changePersistentIndex(oldModelIndex, index(dest, -1));

	Q_EMIT layoutChanged();
}

void PlaylistModel::OnNext()
{
	mData.next();
}

void PlaylistModel::OnPrevious()
{
	mData.previous();
}

void PlaylistModel::OnRemove(RowList selectedRows)
{
	Q_EMIT layoutAboutToBeChanged();

	auto oldModelIndex = QModelIndex();

	// coef var is used for the correction. We should update
	// values in the list of selected rows after erasing,
	// since size of list on every iteration decreasing.
	int coef = 0;

	for (const auto& row : selectedRows) {
		mData.removeMedia(row - coef);
		++coef;
	}

	changePersistentIndex(oldModelIndex, QModelIndex());

	Q_EMIT layoutChanged();
}

void PlaylistModel::Open(const AudioUrls& urls)
{
	if (mData.mediaCount() > 0) {
		_Clear();
	}

	Add(urls);

	mData.setCurrentIndex(0);
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
	// Note! When implementing a table based model,
	// rowCount() should return 0 when the parent is valid.
	return parent.isValid() ? 0 : mData.mediaCount();
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

void PlaylistModel::_Clear()
{
	Q_EMIT layoutAboutToBeChanged();

	auto oldModelIndex = QModelIndex();

	if (!mData.clear()) {
		throw std::runtime_error{ mData.errorString().toStdString() };
	}

	changePersistentIndex(oldModelIndex, QModelIndex());

	Q_EMIT layoutChanged();
}

void PlaylistModel::_OnCurrentIndexChanged(int val)
{
	auto cnt = mData.mediaCount();

	if (cnt > 0) {
		Q_EMIT NewIndex(val);
		Q_EMIT dataChanged(index(0, 0),
			index(cnt - 1, 0), { Qt::DecorationRole });
	}
}

} // namespace splay
