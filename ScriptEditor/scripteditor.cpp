#include "scripteditor.h"
#include "ui_scripteditor.h"
#include <QNetworkDatagram>
#include <QDataStream>
#include <QDir>

ScriptEditor::ScriptEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScriptEditor)
    , isConnected(false)
{
    ui->setupUi(this);

    // Создаем UDP сокет
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(12345); // Порт редактора

    connect(udpSocket, &QUdpSocket::readyRead, this, &ScriptEditor::readResponse);

    setCurrentFile("");

    // Загружаем пример скрипта
    QString defaultScript = QString::fromUtf8(R"(// QTScript для отрисовки геометрических фигур
var canvas = new Canvas(800, 600);

// 1. Синий залитый круг
canvas.setBrushColor(0, 0, 255); // Синий
canvas.setPenColor(0, 0, 255);
canvas.drawFilledCircle(200, 150, 80);

// 2. Незалитый круг с бирюзовым контуром
canvas.setBrushColor(0, 0, 0, 0); // Прозрачная заливка
canvas.setPenColor(0, 255, 255); // Бирюзовый
canvas.setPenWidth(3);
canvas.drawCircle(400, 150, 70);

// 3. Треугольник
canvas.setPenColor(255, 0, 0); // Красный
canvas.setBrushColor(255, 200, 200); // Светло-красный
var points = [300, 300, 400, 200, 500, 300];
canvas.drawPolygon(points);

// 4. Прямоугольник
canvas.setPenColor(0, 255, 0); // Зеленый
canvas.setBrushColor(200, 255, 200); // Светло-зеленый
canvas.setPenWidth(2);
canvas.drawRect(150, 350, 200, 100);

// 5. 4 линии разного цвета
canvas.setPenWidth(4);
canvas.setPenColor(255, 255, 0); // Желтый
canvas.drawLine(50, 50, 200, 50);

canvas.setPenColor(255, 0, 255); // Пурпурный
canvas.drawLine(50, 80, 200, 80);

canvas.setPenColor(0, 255, 255); // Голубой
canvas.drawLine(50, 110, 200, 110);

canvas.setPenColor(255, 165, 0); // Оранжевый
canvas.drawLine(50, 140, 200, 140);

// Отображаем результат
canvas.show();
)");

    ui->scriptEditor->setPlainText(defaultScript);
}

ScriptEditor::~ScriptEditor()
{
    delete ui;
}

void ScriptEditor::closeEvent(QCloseEvent *event)
{
    // Здесь можно добавить проверку на сохранение изменений
    event->accept();
}

void ScriptEditor::on_actionNew_triggered()
{
    ui->scriptEditor->clear();
    setCurrentFile("");
}

void ScriptEditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Открыть QTScript"), "", tr("QTScript (*.js);;Все файлы (*)"));

    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }
}

void ScriptEditor::on_actionSave_triggered()
{
    if (currentFile.isEmpty()) {
        on_actionSaveAs_triggered();
    } else {
        saveFile(currentFile);
    }
}

void ScriptEditor::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить QTScript"), "", tr("QTScript (*.js);;Все файлы (*)"));

    if (!fileName.isEmpty()) {
        saveFile(fileName);
        setCurrentFile(fileName);
    }
}

void ScriptEditor::on_connectButton_clicked()
{
    QString ip = ui->executorIP->text();
    QString portStr = ui->executorPort->text();

    if (ip.isEmpty() || portStr.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите IP адрес и порт"));
        return;
    }

    quint16 port = portStr.toUShort();
    if (port == 0) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите корректный порт"));
        return;
    }

    isConnected = true;
    ui->connectButton->setEnabled(true);
    ui->connectButton->setText(tr("Подключено"));
    ui->connectButton->setEnabled(false);
    ui->statusbar->showMessage(tr("Подключено к %1:%2").arg(ip).arg(port));
}

void ScriptEditor::on_executeButton_clicked()
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Сначала подключитесь к исполнителю"));
        return;
    }

    QString script = ui->scriptEditor->toPlainText();
    if (script.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Скрипт пуст"));
        return;
    }

    // Отправляем скрипт через UDP
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << QString("EXECUTE_SCRIPT");
    out << script;

    QString ip = ui->executorIP->text();
    quint16 port = ui->executorPort->text().toUShort();

    udpSocket->writeDatagram(datagram, QHostAddress(ip), port);
    ui->statusbar->showMessage(tr("Скрипт отправлен для выполнения..."));
}

void ScriptEditor::readResponse()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray data = datagram.data();

        QDataStream in(&data, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_15);

        QString command;
        QString result;
        bool success;

        in >> command >> success >> result;

        if (command == "SCRIPT_RESULT") {
            if (success) {
                QMessageBox::information(this, tr("Результат выполнения"),
                                         tr("Скрипт выполнен успешно:\n%1").arg(result));
                ui->statusbar->showMessage(tr("Скрипт выполнен успешно"));
            } else {
                QMessageBox::warning(this, tr("Ошибка выполнения"),
                                     tr("Ошибка выполнения скрипта:\n%1").arg(result));
                ui->statusbar->showMessage(tr("Ошибка выполнения скрипта"));
            }
        }
    }
}

void ScriptEditor::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = tr("безымянный.js");

    setWindowTitle(QString("%1[*] - QTScript Editor").arg(shownName));
}

bool ScriptEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Не удалось сохранить файл %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }

    QTextStream out(&file);
    out << ui->scriptEditor->toPlainText();
    ui->statusbar->showMessage(tr("Файл сохранен"), 2000);
    return true;
}

bool ScriptEditor::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Не удалось открыть файл %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }

    QTextStream in(&file);
    ui->scriptEditor->setPlainText(in.readAll());
    setCurrentFile(fileName);
    ui->statusbar->showMessage(tr("Файл загружен"), 2000);
    return true;
}
