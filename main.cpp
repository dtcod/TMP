#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <FboNode.h>
#include <easylogging++.h>
using namespace std;

void registerCoreClassForQML() {
    qmlRegisterType<FboNode>("TMPCore", 1, 0, "Viewer");
}
INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]){

    QGuiApplication app(argc, argv);
    registerCoreClassForQML();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
