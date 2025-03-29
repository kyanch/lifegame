#pragma once

#include <qtmetamacros.h>
#include <QAbstractListModel>

#include "universe.h"

/* This is a adapter connect the core component and QT */
class UniverseData : public QAbstractListModel {
  Q_OBJECT
 public:
  explicit UniverseData(std::size_t size, QObject* parent = nullptr);
  Q_INVOKABLE size_t columns() const;
  Q_INVOKABLE size_t rows() const;

  int rowCount(const QModelIndex& parent=QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex& index, const QVariant& value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

 public slots:
  void tick() ;

 private:
  Universe universe;
};