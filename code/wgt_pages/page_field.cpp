#include "page_field.h"
#include "ui_page_field.h"


page_field::page_field(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_field)

{
    ui->setupUi(this);

    connect(ui->pushButton_menu, SIGNAL(clicked()), SLOT(pauseGame()));

    //Создаем окно паузы
    m_dialog_pause = new dialog_pause(this);
    m_dialog_pause->setFixedSize(dynamic_cast<QWidget*>(this->parent())->size());
    m_dialog_pause->repaint();

    //m_dialog_pause->raise();
    m_dialog_pause->hide();

    connect(m_dialog_pause, SIGNAL(button_resume()), SLOT(resumeGame()));
    connect(m_dialog_pause, SIGNAL(button_backMenu()), SLOT(saveGame()));
    connect(m_dialog_pause, SIGNAL(button_retry()), SIGNAL(button_newGame_pressed()));
}

page_field::~page_field()
{
    delete ui;
}

void page_field::launchPreviousGame()
{
    QSize fieldSize;
    int gameMode;
    int gameSpeed;
    QVector<QPoint> snake;
    int direction;
    int score;
    QPoint posBonus;
    loadSettings(fieldSize, gameMode, gameSpeed, snake, direction, score,posBonus);

    m_gameController = new GameController(fieldSize, gameMode, gameSpeed, score, this);
    m_drawFieldManager = new DrawFieldManager(ui->frame_field, m_gameController, fieldSize, this);

    m_gameController->resumeGame(snake, direction, posBonus);
    m_gameController->startGame();

    connect(m_gameController, SIGNAL(gameOver()), SLOT(exitGame())); //временно
    connect(m_gameController, SIGNAL(draw()), SLOT(updateField()));
}

void page_field::launchNewGame(QSize fieldSize, int type, int speed)
{
    m_gameController = new GameController(fieldSize, type, speed, 0, this);
    m_drawFieldManager = new DrawFieldManager(ui->frame_field, m_gameController, fieldSize, this);

    //ui->frame_field->show();

    m_gameController->newGame();
    m_gameController->startGame();

    connect(m_gameController, SIGNAL(gameOver()), SLOT(exitGame())); //временно
    connect(m_gameController, SIGNAL(draw()), SLOT(updateField()));
}

void page_field::loadSettings(QSize &fieldSize, int &gameType, int &speed, QVector<QPoint> &snake, int &direction, int &score, QPoint &posBonus)
{
    QSettings settings("MonkeyCo", "Snake");

    settings.beginGroup("field_settings");
    fieldSize = settings.value("/fieldSize").toSize();
    gameType = settings.value("/gameType", gameType).toInt();
    speed = settings.value("/speed").toInt();
    QList<QVariant> lv_snake = settings.value("/snake").toList();
    direction = settings.value("/direction").toInt();
    score = settings.value("/score").toInt();
    posBonus = settings.value("/bonus").toPoint();
    settings.endGroup();

    // QList<QVariant> => QList<QPoint> => QVector<QPoint>
    snake.clear();
    foreach (QVariant var, lv_snake) {
        snake.push_back(var.toPoint());
    }
}

void page_field::saveSettings(QSize fieldSize, int gameType, int speed, QVector<QPoint> snake, int direction, int score, QPoint posBonus)
{
    QSettings settings("MonkeyCo", "Snake");

    //QVector<QPoint> => QList<QPoint> => QList<QVariant>
    QList<QVariant> lv_snake;
    foreach (QPoint var, snake) {
        lv_snake.append(var);
    }
    settings.beginGroup("field_settings");
    settings.setValue("/fieldSize", fieldSize);
    settings.setValue("/gameType", gameType);
    settings.setValue("/speed", speed);
    settings.setValue("/snake", lv_snake);
    settings.setValue("/direction", direction);
    settings.setValue("/score", score);
    settings.setValue("/bonus",posBonus);
    settings.endGroup();
}

void page_field::clearSetting()
{
    QSettings settings("MonkeyCo", "Snake");

    settings.beginGroup("field_settings");
    settings.remove("");
    settings.endGroup();
}

void page_field::saveGame()
{
    QSize fieldSize = m_gameController->getFieldSize();
    int gameMode = m_gameController->getGameMode();
    int gameSpeed = m_gameController->getGameSpeed();
    QVector<QPoint> snake  = m_gameController->getSnake();
    int direction  = m_gameController->getDirection();
    int score = m_gameController->getScore();
    QPoint posBonus = m_gameController->getBonus();

    saveSettings(fieldSize, gameMode, gameSpeed, snake, direction, score, posBonus);

    emit button_menu_pressed();
}

void page_field::exitGame()
{
    clearSetting();
    emit endOfGame(getPlayerName(), getScore(), getType());
}

void page_field::pauseGame()
{
    m_dialog_pause->show();
    m_gameController->pauseGame();
}

void page_field::resumeGame()
{
    m_dialog_pause->hide();
    m_gameController->pauseGame();
    this->setFocus();
}

void page_field::updateField()
{
    int newScore = m_gameController->getScore();
    ui->score->setText(QString::number(newScore));
    m_drawFieldManager->updateField();
}

void page_field::keyPressEvent(QKeyEvent *event)
{
    m_gameController->keyPress(event);
}

void page_field::setPlayerName(const QString& playerName)
{
    m_playerName = playerName;
    ui->label_playerName->setText(playerName);
}

int page_field::getScore()
{
    return (m_gameController != nullptr)
            ? m_gameController->getScore()
            : 0;
}

QString page_field::getPlayerName()
{
    return (m_playerName != "")
            ? m_playerName
            : "Player";
}

int page_field::getType()
{
    return (m_gameController != nullptr)
            ? m_gameController->getGameMode()
            : 0;
}



