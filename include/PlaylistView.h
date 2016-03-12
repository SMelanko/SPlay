#pragma once

#ifndef _SPLAY_PLAYLIST_VIEW_H_
#define _SPLAY_PLAYLIST_VIEW_H_

#include "Types.h"

#include <QTableView>

namespace splay
{

class PlaylistView : public QTableView
{
	Q_OBJECT

public:
	/// Constructor.
	explicit PlaylistView(QWidget* parent = Q_NULLPTR);
	/// Destructor.
	virtual ~PlaylistView() = default;

	/// Disabled copy constructor and copy assign operator.
	Q_DISABLE_COPY(PlaylistView)

Q_SIGNALS:
	/// Emits new current index.
	void MediaIndexChanged(int index);
	/// Emits new media list which have been added via drag and drop operation.
	void Insert(AudioUrls urls);
	/// TODO Emits the signal when internal moving of the rows is executed.
	void Move(const RowList selectedRows, int dest);
	/// Emits a list with rows for removing.
	void Remove(const RowList selectedRows);

protected:
	/// Handles event that is sent to the current widget when a drag action
	/// enters it.
	void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
	/// Handles event that is sent to the current widget when a drag action
	/// leaves it.
	void dragLeaveEvent(QDragLeaveEvent* event) Q_DECL_OVERRIDE;
	/// Handles event when a drag and drop action is completed.
	void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;
	/// Receives key press events for the widget.
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

private Q_SLOTS:
	/// Handles mouse double click on a table row.
	void OnDoubleCkicked(const QModelIndex& index);
	/// Handles a section (table header) clicking.
	void OnSectionClicked(int index);
	/// Handles a section (table header) resizing.
	void OnSectionResized(int logicalIndex, int oldSize, int newSize);

private:
	/// Returns a list of the rows which have been selected.
	RowList _GetSelectedRows() const Q_DECL_NOEXCEPT;
	/// Sets up drag and drop behaviour.
	void _SetUpDragAndDrop() Q_DECL_NOEXCEPT;
	/// Sets up the horizontal header.
	void _SetUpHorizontalHeader() Q_DECL_NOEXCEPT;
	/// Sets up the vertical header.
	void _SetUpVerticalHeader() Q_DECL_NOEXCEPT;
	/// Creates custom style sheet for the widget.
	QString _Qss() const Q_DECL_NOEXCEPT;

private:
	/// Checks if table header section has been resized.
	bool mSectionResized;
};

} // namespace splay

#endif // _SPLAY_PLAYLIST_VIEW_H_
