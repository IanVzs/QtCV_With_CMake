#include<QDebug>

#include "androidfile.h"

AndroidFile::AndroidFile(QObject *parent) : QObject(parent)
  ,myName("none")
{
    msgRefresh();
}

bool AndroidFile::checkPermission(QString permission_cmd)
{
#ifdef ANDROID_PLATFORM
    QtAndroid::PermissionResult r = QtAndroid::checkPermission(permission_cmd);
    if (r == QtAndroid::PermissionResult::Denied)
    {
            QtAndroid::requestPermissionsSync( QStringList() << permission_cmd );
            r = QtAndroid::checkPermission(permission_cmd);
            if (r == QtAndroid::PermissionResult::Denied)
            {
                    return false;
            }
    }
#endif
    return true;
}

void AndroidFile::msgRefresh()
{
    if(!checkPermission("android.permission.CAMERA"))
    {
        emit fromCheckPermission("安卓相机权限获取失败");
    } else {
        qDebug() << "emit AndroidFile::msgRefresh 成功获取安卓相机权限";
        emit fromCheckPermission("成功获取安卓相机权限");
    }
    if(!checkPermission("android.permission.WRITE_EXTERNAL_STORAGE"))
    {
        emit fromCheckPermission("安卓存储卡写权限获取失败");
    } else {
        emit fromCheckPermission("成功获取安卓存储卡写权限");
    }
}



void AndroidFile::setName(const QString &name)
{
        qDebug() << "setName: " << name;
        if (myName != name) {
            qDebug() << "emit nameChanged";
            myName = name;
            emit nameChanged(name);
//            emit fromCheckPermission("成功获取安卓相机权限");
        }

}
QString AndroidFile::getName() const
{
    qDebug() << "getName: " << myName;
    return myName;
}
