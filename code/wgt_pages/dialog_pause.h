#ifndef DIALOG_PAUSE_H
#define DIALOG_PAUSE_H

#include <QWidget>

namespace Ui {
class dialog_pause;
}

class dialog_pause : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_pause(QWidget *parent = 0);
    ~dialog_pause();

private:
    Ui::dialog_pause *ui;
};

#endif // DIALOG_PAUSE_H
