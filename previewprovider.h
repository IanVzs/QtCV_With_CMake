#ifndef PREVIEWPROVIDER_H
#define PREVIEWPROVIDER_H

#include <QImage>
#include <QQuickImageProvider>

class PreviewProvider : public QQuickImageProvider
{
public:
    PreviewProvider(ImageType type, Flags flags = 0);
    ~PreviewProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);  //重写requestPixmap函数
    QImage requestImage(const QString & id, QSize * size, const QSize & requestedSize); //重写requestImage函数
};

#endif // PREVIEWPROVIDER_H
