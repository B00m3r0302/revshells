#include "mainwindow.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "PayloadGenerator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app (argc, argv);
    QQmlApplicationEngine engine;

    PayloadGenerator generator;
    engine.rootContext()->setContextProperty("generator", &generator);

    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
