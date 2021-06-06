#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <data/dropdownvalue.h>
#include <QObject>
#include <QtQml/QQmlListProperty>
#include <QScopedPointer>

#include <cm-lib_global.h>

namespace cm {
namespace data {
class CMLIBSHARED_EXPORT DropDown: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<cm::data::DropDownValue> ui_values READ ui_values CONSTANT)
public:
    explicit DropDown(QObject* _parent = nullptr, const std::map<int, QString>& values = std::map<int, QString>());
    ~DropDown();
public:
    QQmlListProperty<DropDownValue> ui_values();

public slots:
    QString findDescriptionForDropdownValue(int valueKey) const;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};
}}

#endif // DROPDOWN_H
