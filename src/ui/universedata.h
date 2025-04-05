#pragma once

#include <QAbstractListModel>
#include <QHash>
#include <QUrl>
#include <QVariant>
#include <cstddef>

#include "universe.h"

/* This is a adapter connect the core component and QT */
class UniverseData : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit UniverseData(std::size_t size, QObject* parent = nullptr);
  UniverseData(const Universe& uni, QObject* parent = nullptr);
  Q_INVOKABLE size_t columns() const;
  Q_INVOKABLE size_t rows() const;
  Q_INVOKABLE bool set_cell(const int index, int value) {
    return setData(createIndex(index, 1), (Cell)value);
  }
  Q_INVOKABLE void clear(const Cell& cell = Dead) {
    universe = Universe(columns(), cell);
    emit dataChanged(index(0), index(rowCount() - 1));
  }
  Q_INVOKABLE bool save_to_file(const QUrl&);
  Q_INVOKABLE bool read_from_file(const QUrl&);

  QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "cell";
    return roles;
  }
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex& index, const QVariant& value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

 public slots:
  void tick();

 private:
  Universe universe;
};