#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    // ============================
    // QML
    // ============================
    QQmlApplicationEngine engine;
    engine.loadFromModule("Weeklyft", "App");

    return app.exec();
}