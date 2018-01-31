#ifndef COLOR_PICKER_OVERLAY_WIDGET_H
#define COLOR_PICKER_OVERLAY_WIDGET_H

#include <QColor>
#include <QWidget>

class QMouseEvent;
class QKeyEvent;

class ColorPickerOverlayWidget 
	: public QWidget
{
	Q_OBJECT

public:
	ColorPickerOverlayWidget(QWidget *parent = nullptr);
	~ColorPickerOverlayWidget();

protected:
	void mouseMoveEvent(QMouseEvent *ev) override;
	void mousePressEvent(QMouseEvent *ev) override;
	void keyPressEvent(QKeyEvent *ev) override;
	void pickColor();
	void exitWithoutPickingColor();

private:
	QColor currentColor;

signals:
	void onColorPicked(const QColor &currentColor);
	void onCursorMoved(const QColor &currentColor);
	void onExitWithoutPickingColor();
};

#endif // COLOR_PICKER_OVERLAY_WIDGET_H
