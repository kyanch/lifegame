#include "universedata.h"

#include <qabstractitemmodel.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <qvariant.h>

#include "universe.h"

UniverseData::UniverseData(std::size_t size, QObject* parent)
    : universe(size), QAbstractListModel(parent) {}

Q_INVOKABLE size_t UniverseData::columns() const {
  return universe.get_width();
}

Q_INVOKABLE size_t UniverseData::rows() const { return universe.get_height(); }

int UniverseData::rowCount(const QModelIndex& parent) const {
  return universe.get_height() * universe.get_width();
}
QVariant UniverseData::data(const QModelIndex& index, int role) const {
  return QVariant(universe[index.row()]);
}
bool UniverseData::setData(const QModelIndex& index, const QVariant& value,
                           int role) {
  universe[index.row()] = value.value<Cell>();
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