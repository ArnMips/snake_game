#include "drawfieldmanager.h"
#include <QLabel>

#include <QDebug>

DrawFieldManager::DrawFieldManager(page_field* gf, GameController *gc, QSize fieldSize, QObject *parent)
    : m_page_field(gf)
    , m_gameController(gc)
    , m_fieldSize(fieldSize)
    , QObject(parent)
    , count(0)

    //загружаем картинки
    ,imgEmpty(QPixmap("C:/Qt/Projects/Game_snake/code/img/empty.png"))
    ,imgSnake(QPixmap("C:/Qt/Projects/Game_snake/code/img/snakeBody.png"))
    ,imgBonus(QPixmap("C:/Qt/Projects/Game_snake/code/img/bonus1.png"))
    ,imgWall(QPixmap("C:/Qt/Projects/Game_snake/code/img/wall.png"))
{
    m_gameField = m_page_field->getGameField();
    ///При получении сигнала draw необходимо перерисовать поле
    QObject::connect(m_gameController, SIGNAL(draw()), SLOT(updateField()));

    ///получаем разрешение окошка игры
    QSize pageFieldSize = m_page_field->size();
    ///изменяем размер поля в виджете
    m_page_field->setFrameFieldSize(pageFieldSize * 0.8);

    ///вычисляем размер клетки
    m_boxSize = m_page_field->getFrameFieldSize().height() / m_fieldSize.height();


    //--------------------------------------------------------------------------
    //создаем массив картинок для поля
    for (int i = 0; i < m_fieldSize.width(); ++i) {
        QVector<QLabel*> temp;
        for (int j = 0; j < m_fieldSize.height(); ++j) {
            QLabel* plbl = new QLabel(m_gameField);
            plbl->setPixmap(imgEmpty);
            plbl->setGeometry(i*m_boxSize, j*m_boxSize, m_boxSize, m_boxSize);
            plbl->setScaledContents(true);

            temp.push_back(plbl);
        }
        imgField.push_back(temp);
    }
}

void DrawFieldManager::updateField()
{
    //if (count++ > 3) return;

    //int newScore = m_gameController->getScore();
    //m_page_field->setScore(newScore);

    ///Получение массива сущностей на поле
    const QVector<QVector<GameController::ObjectType> >& objFields = m_gameController->getField();

    ///Перерисовка поля
    for (int i = 0; i < m_fieldSize.width(); ++i) {
        for (int j = 0; j < m_fieldSize.height(); ++j) {
            switch (objFields[i][j]) {
            case GameController::fEmpty : imgField[i][j]->setPixmap(imgEmpty); break;
            case GameController::fSnake : imgField[i][j]->setPixmap(imgSnake); break;
            case GameController::fBonus : imgField[i][j]->setPixmap(imgBonus); break;
            case GameController::fWall  : imgField[i][j]->setPixmap(imgWall);  break;
            }
        }
    }

    //qDebug() << "Lapse: " << count++;

    for (int i = 0; i < m_fieldSize.width(); ++i) {
        for (int j = 0; j < m_fieldSize.height(); ++j) {
            switch (objFields[i][j]) {
            //case GameController::fEmpty : qDebug() << "fEmpty"<< i << " " << j; break;
            //case GameController::fSnake : qDebug() << "fSnake" << i << " " << j; break;
            //case GameController::fBonus : qDebug() << "fBonus" << i << " " << j; break;
            //case GameController::fWall  : qDebug() << "fWall" << i << " " << j;  break;
            }
        }
    }

}
