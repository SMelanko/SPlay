#pragma once

#ifndef _SPLAY_TABLE_WGT_H_
#define _SPLAY_TABLE_WGT_H_

#include <QTableWidget>

namespace splay
{

class TableWgt : public QTableWidget
{
	Q_OBJECT

public:
	//! Constructor.
	explicit TableWgt(QWidget* parent = Q_NULLPTR);
	//! Destructor.
	~TableWgt();

protected:
	//! Receives key press events for the widget.
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

	private slots:
	//! Handles mouse double click on a table row.
	void OnDoubleCkick(QTableWidgetItem* item);
	//! Handles a section (table header) clicking.
	void OnSectionClicked(int index);
	//! Handles a section (table header) resizing.
	void OnSectionResized(int logicalIndex, int oldSize, int newSize);

private:
	//! Creates custom style sheet for the widget.
	QString _Qss();

private:
	//! Count of the rows.
	int mRowCnt;
	//! ...
	bool mSectionResized;
};

} // namespace splay

#endif // _SPLAY_TABLE_WGT_H_
