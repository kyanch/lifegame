#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "universe.h"
#include "universedata.h"

UniverseData read_default_universe() {
  QFile file(":/universe/default.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "无法打开文件：" << file.errorString();
    return UniverseData(10);
  }
  QTextStream in(&file);
  return UniverseData(Universe(in.readAll().toStdString()));
}

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  UniverseData data = read_default_universe();

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("universe", &data);
  engine.loadFromModule("lgX", "Main");

  return app.exec();
}