#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui { class MainWindow; }

void MainWindow::startHTTPserver()
{
    httpServer = new QHttpServer;

    httpServer->route("/qt_api/test", QHttpServerRequest::Method::Get,
                      []() {
                          qDebug() << "receive response";
                          return QString("hello");
                      });

    httpServer->afterRequest([](QHttpServerResponse &&resp)
    {

    });

    const auto port = httpServer->listen(QHostAddress::Any, 45823);
    if (!port)
    {
        qDebug() << QCoreApplication::translate(
                "QHttpServerExample", "Server failed to listen on a port.");
    }

    qDebug() << QCoreApplication::translate(
            "QHttpServerExample", "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startHTTPserver();
}

MainWindow::~MainWindow()
{
    delete ui;
}

