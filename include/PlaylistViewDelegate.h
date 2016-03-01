#pragma once

#ifndef _SPLAY_TABLE_VIEW_DELEGATE_H_
#define _SPLAY_TABLE_VIEW_DELEGATE_H_

#include <atomic>

#include <QStyledItemDelegate>

namespace splay
{

class PlaylistViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	/// Constructor.
	explicit PlaylistViewDelegate(QObject* parent = Q_NULLPTR);
	/// Destructor.
	~PlaylistViewDelegate() = default;

	//! Disable copy constructor and copy assign operator.
	Q_DISABLE_COPY(PlaylistViewDelegate)

public:
	/// Renders the delegate using the given painter and style option
	/// for the item specified by index.
	void paint(QPainter* painter, const QStyleOptionViewItem& option,
		const QModelIndex& index) const Q_DECL_OVERRIDE;

public Q_SLOTS:
	/// Updates current media index.
	void SetNewIndex(int val);

private:
	/// Current index of the track which is being played.
	std::atomic<int> mIndex;
};

} // namespace splay

#endif // _SPLAY_TABLE_VIEW_DELEGATE_H_

