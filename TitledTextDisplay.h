#ifndef TITLED_TEXT_DISPLAY_H
#define TITLED_TEXT_DISPLAY_H

#include <QtWidgets/QLineEdit>

class QFocusEvent;
class QLabel;

class TitledTextDisplay
	: public QLineEdit
{
	Q_OBJECT

public:
	TitledTextDisplay(QString title, QWidget *parent = nullptr);
	~TitledTextDisplay();

protected:
	void focusInEvent(QFocusEvent *ev) override;

private:
	QLabel *titleLabel;
};

#endif // TITLED_TEXT_DISPLAY_H
