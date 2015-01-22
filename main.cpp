#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <asteroidfield.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<AsteroidField>("Asteroids", 1, 0, "AsteroidField");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
