#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "universedata.h"

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  UniverseData data(10);
  Universe temp = Universe("XXX000XXX");

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("universe", &data);
  engine.loadFromModule("lgX", "Main");

  return app.exec();
}