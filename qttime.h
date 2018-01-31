#ifndef QTTIME_H
#define QTTIME_H

#include <QtGui/QColor>
#include <QtWidgets/QMainWindow>

#include <ui_qttime.h>

class ColorPickerOverlayWidget;
class TitleBarWidget;

class QtTime 
	: public QMainWindow
{
	Q_OBJECT

public:
	QtTime(QWidget *parent = nullptr);
	~QtTime();

protected:
	bool eventFilter(QObject *obj, QEvent *ev) override;
	void updateDraggedWindowPosition(const QPoint &draggedDistance);
	void displayColorInfoInGUI(QColor const &color);

	ColorPickerOverlayWidget* colorPickerOverlay;
	TitleBarWidget* titleBar;

private:
	void initMainWindowUi();
	void initColorPickerButton();
	void initPickedColorLabel();
	void initTilteBarUi();
	void initColorPickerOverlayUi();
	void initColorValuesUi();
	
	Ui::QtTimeClass ui;
	QColor pickedColor;

private slots:
	void activateColorPickerMode();
	void displayCurrentMouseoverColor(const QColor &currentColor);
	void pickCurrentMouseoverColor(const QColor &currentColor);
	void resetColorToLastPicked();
};

#endif // QTTIME_H
