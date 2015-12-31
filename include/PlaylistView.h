#pragma once

#ifndef _SPLAY_PLAYLIST_VIEW_H_
#define _SPLAY_PLAYLIST_VIEW_H_

#include "Types.h"

#include <QTableView>

namespace splay
{

class Track;

class PlaylistView : public QTableView
{
	Q_OBJECT

public:
	//! Constructor.
	explicit PlaylistView(QWidget* parent = Q_NULLPTR);
	//! Destructor.
	~PlaylistView();

Q_SIGNALS:
	//! Emits signal for adding new tracks via drag and drop operation.
	void Insert(QStringList list);
	//! Emits signal when internal moving of the rows is executed.
	void Move(const QVector<int> rows, int dest);

protected:
	//! Handles event that is sent to the current widget when a drag action enters it.
	void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
	//! Handles event that is sent to the current widget when a drag action leaves it.
	void dragLeaveEvent(QDragLeaveEvent* event) Q_DECL_OVERRIDE;
	//! Handles event when a drag and drop action is completed.
	void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;
	//! Receives key press events for the widget.
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

private Q_SLOTS:
	//! Handles mouse double click on a table row.
	void OnDoubleCkick(const QModelIndex& index);
	//! Handles a section (table header) clicking.
	void OnSectionClicked(int index);
	//! Handles a section (table header) resizing.
	void OnSectionResized(int logicalIndex, int oldSize, int newSize);

private:
	//! Returns a list of rows whose have been selected.
	QVector<int> _GetSelectedRows() const NOEXCEPT;
	//! Creates custom style sheet for the widget.
	QString _Qss() const NOEXCEPT;

private:
	//! Checks if table header section has been resized.
	bool mSectionResized;
};

} // namespace splay

#endif // _SPLAY_PLAYLIST_VIEW_H_
