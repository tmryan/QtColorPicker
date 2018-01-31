#ifndef TITLE_BAR_WIDGET_H
#define TITLE_BAR_WIDGET_H

#define DEFAULT_TITLEBAR_HEIGHT 32

#include <QWidget>

class QLabel;
class QPushButton;

class TitleBarWidget 
	: public QWidget
{
	Q_OBJECT

public:
	TitleBarWidget(QString title, QWidget *parent = nullptr, int height = DEFAULT_TITLEBAR_HEIGHT);
	~TitleBarWidget();

protected:
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;

	QPoint previousMousePosition;
	QPoint mouseDragPosition;

private:
	QLabel* titleLabel;
	QPushButton* exitButton;

signals:
	void onWidgetBeingDragged(const QPoint &draggedDistance);
};

#endif // TITLE_BAR_WIDGET_H
