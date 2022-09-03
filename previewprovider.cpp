#include "previewprovider.h"

#include <QDebug>
#include <opencv2/opencv.hpp>

PreviewProvider::PreviewProvider(ImageType type, Flags flags)
    : QQuickImageProvider(type,flags)
{

}

PreviewProvider::~PreviewProvider()
{

}

QPixmap PreviewProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QString s=":/ima/" + id;        //本地图片加载路径的拼接，根据id不同可以调用不同图片
    QPixmap pix;                //新建一个QPixmap对象
    pix.load(s);                //加载图片
    pix=pix.scaled(150,250);    //图片缩放
    return pix;                 //返回QPixmap对象
}

QImage PreviewProvider::requestImage(const QString & id, QSize * size, const QSize & requestedSize)
{
    cv::Mat img;
    QString imgPath = id;
    imgPath = imgPath.replace("file://", "");
    img = cv::imread(imgPath.toStdString());
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
    QImage image((const unsigned char*)img.data, img.cols,
                 img.rows, img.step, QImage::Format_RGB888);
    qDebug() << "PreviewProvider::updateImage id: " << id;
//    size->setWidth(image.width());
//    size->setHeight(image.height());
    return image;
}
