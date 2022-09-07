#ifndef PREVIEWPROVIDER_H
#define PREVIEWPROVIDER_H

#include <QImage>
#include <QPainter>
#include <opencv2/core.hpp>
#include <QQuickPaintedItem>
#include <QQuickImageProvider>

class PreviewProvider : public QQuickImageProvider
{
public:
    PreviewProvider(ImageType type, Flags flags = 0);
    ~PreviewProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);  //重写requestPixmap函数
//    QImage requestImage(const QString & id, QSize * size, const QSize & requestedSize); //重写requestImage函数

    QString addSuffix2FileName(const QString fileName, const QString suffix);

private:
    QImage img_result;
};


class PaintItem : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit PaintItem(QQuickItem *parent=nullptr);
    Q_INVOKABLE void dealThisImg(QString path, QString mode);

public slots:
    void updateImage(const QImage &);
protected:
    void paint(QPainter *painter);
private:
    QString addSuffix2FileName(const QString fileName, const QString suffix);
    QImage *imageToSend;
    void toGray(cv::Mat *img);
    QImage mat2QImage(const cv::Mat &mat);
};

#endif // PREVIEWPROVIDER_H
