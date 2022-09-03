#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QLocale>
#include <QTranslator>
#include <QtCore/QStandardPaths>
#include <opencv2/opencv.hpp>
#include "androidfile.h"
#include "previewprovider.h"

#ifdef Android_Platform
#include <QtAndroid>
#endif

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#ifdef ANDROID_PLATFORM
    // 权限申请
    QString strPermission = "android.permission.READ_EXTERNAL_STORAGE";
    QtAndroid::requestPermissionsSync(QStringList() << strPermission);
#endif
#ifdef ANDROID_PLATFORM
    const QStringList m_currentDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << "Android writable location ... " + QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#elif IOS_PLATFORM
    const QStringList m_currentDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
#endif

    QGuiApplication app(argc, argv);
    // qml register
    qmlRegisterType<AndroidFile>("com.permission.module", 1, 0, "AndPermission");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QCV_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    // image provider 1
    PreviewProvider *imageProvider = new PreviewProvider(QQmlImageProviderBase::Image);

    QQmlApplicationEngine engine;
    // image provider 2
    engine.addImageProvider("previewprovider", imageProvider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    qDebug() << "RGB2BGR int is: " << cv::COLOR_RGB2BGR;

    return app.exec();
}
