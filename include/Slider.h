#pragma once

#ifndef _SPLAY_SLIDER_H_
#define _SPLAY_SLIDER_H_

#include <QSlider>

namespace splay
{

class Slider : public QSlider
{
public:
	/// Constructor.
	explicit Slider(Qt::Orientation orient, QWidget* parent = Q_NULLPTR);

protected:
	/// Receives and handles mouse press events.
	void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
	/// Makes a new custom style sheet.
	QString _Qss() const;
};

} // namespace splay

#endif // _SPLAY_SLIDER_H_
