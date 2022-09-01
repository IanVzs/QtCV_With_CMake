#ifndef ANDROIDFILE_H
#define ANDROIDFILE_H

#include <QObject>

class AndroidFile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:
    explicit AndroidFile(QObject *parent = nullptr);
    bool checkPermission(QString permission_cmd);
    void msgRefresh();

    void setName(const QString &name);
    QString getName() const;
signals:
    void fromCheckPermission(QString msg);
    void nameChanged(const QString name);

private:
    // 类私属性
    // name some3 other
    QString myName;
};
#endif // ANDROIDFILE_H
