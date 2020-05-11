#include "filesmodel.h"
#include "worker.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Worker *worker = new Worker(&engine);
    engine.rootContext()->setContextProperty("worker", worker);
    qRegisterMetaType<FilesModel *>("FilesModel*");

    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
