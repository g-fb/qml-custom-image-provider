#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "customimageprovider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider(QStringLiteral("provider_name"), new CustomImageProvider());
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
    engine.loadFromModule("custom_image_provider", "Main");

    return app.exec();
}
