#ifndef PAGE_FIELD_H
#define PAGE_FIELD_H

#include <QWidget>
#include <QFrame>

namespace Ui {
class page_field;
}

class page_field : public QWidget
{
    Q_OBJECT

public:
    explicit page_field(QWidget *parent = 0);
    ~page_field();

    int getScore() const;
    void setScore(int s);
    QFrame* getGameField();

    QSize getFrameFieldSize() const;
    void setFrameFieldSize(const QSize& size);

private:
    Ui::page_field *ui;
private slots:
    void on_pushButton_menu_clicked();
};

#endif // PAGE_FIELD_H
