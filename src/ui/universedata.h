#pragma once

#include <QAbstractListModel>

#include "universe.h"

/* This is a adapter connect the core component and QT */
class UniverseData : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit UniverseData(std::size_t size, QObject* parent = nullptr)
      : QAbstractListModel(parent), universe(size) {}
  Q_INVOKABLE size_t columns() const { return universe.get_width(); }
  Q_INVOKABLE size_t rows() const { return universe.get_height(); }

  int rowCount(const QModelIndex& parent) const override {
    return columns() * rows();
  }
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override {
    return QVariant(universe[index.row()]);
  }
  bool setData(const QModelIndex& index, const QVariant& value,
               int role = Qt::EditRole) override {
    universe[index.row()] = value.value<Cell>();
    return true;
  }
  Qt::ItemFlags flags(const QModelIndex& index) const override {
    return Qt::ItemIsEditable;
  }

 public slots:
  void tick() { universe.next(); }

 private:
  Universe universe;
};