#pragma once

#include <QPushButton>

namespace splay
{

class PlaybackControlButton : public QPushButton
{
public:
	/// Constructor.
	explicit PlaybackControlButton(QWidget* parent,
		const QSize& size,
		const QIcon& icon,
		const QSize& iconSize,
		const QString& tooltip)
		: QPushButton{ parent }
	{
		setFixedSize(size);
		setIcon(icon);
		setIconSize(iconSize);
		setStyleSheet(
			"QPushButton {"
				"border: none;"
			"}"
			"QPushButton:hover { background: qradialgradient(cx:0.5, cy:0.5,"
				"radius: 0.6, fx:0.5, fy:0.5,"
				"stop:0.0 #BEBEBE, stop:1.0 transparent);"
			"}");
		setToolTip(tooltip);
	}
};

} // namespace splay
