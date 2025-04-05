
#include "universedata.h"

#include <QFile>
#include <QTextStream>
#include <algorithm>
#include <string>

#include "universe.h"

UniverseData::UniverseData(std::size_t size, QObject* parent)
    : universe(size), QAbstractListModel(parent) {
  std::fill(universe.begin(), universe.end(), Alive);
}

UniverseData::UniverseData(const Universe& uni, QObject* parent)
    : universe(uni), QAbstractListModel(parent) {}

Q_INVOKABLE size_t UniverseData::columns() const {
  return universe.get_width();
}

Q_INVOKABLE size_t UniverseData::rows() const { return universe.get_height(); }

int UniverseData::rowCount(const QModelIndex& parent) const {
  return universe.get_height() * universe.get_width();
}
QVariant UniverseData::data(const QModelIndex& index, int role) const {
  return QVariant((int)universe[index.row()]);
}
bool UniverseData::setData(const QModelIndex& index, const QVariant& value,
                           int role) {
  universe[index.row()] = (Cell)value.value<int>();
  emit dataChanged(index, index);
  return true;
}
Qt::ItemFlags UniverseData::flags(const QModelIndex& index) const {
  return Qt::ItemIsEditable;
}

void UniverseData::tick() {
  universe.next();
  emit dataChanged(index(0), index(rowCount() - 1));
}

bool UniverseData::save_to_file(const QUrl& url) {
  QFile file(url.toLocalFile());
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "保存文件错误";
    return false;
  }

  QTextStream out(&file);
  out << static_cast<std::string>(universe).c_str();
  file.close();
  return true;
}
bool UniverseData::read_from_file(const QUrl& url) {
  QFile file(url.toLocalFile());
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "文件读取错误";
    return false;
  }

  QTextStream in(&file);
  QString text = in.readAll();
  universe = Universe(text.toStdString());
  file.close();
  emit dataChanged(index(0), index(rowCount() - 1));
  return true;
}