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

QString PreviewProvider::addSuffix2FileName(const QString fileName, const QString suffix)
{
    QString newName = fileName;
    char len = fileName.length();
    if (newName.endsWith(".jpg")) {
        newName = newName.replace(len-4, len-1, suffix + ".jpg");
    } else if (fileName.endsWith(".png")) {
        newName = newName.replace(len-4, len-1, suffix + ".png");
    } else if (fileName.endsWith(".jpeg")) {
        newName = newName.replace(len-5, len-1, suffix + ".jpeg");
    } else if (fileName.endsWith(".bmp")) {
        newName = newName.replace(len-4, len-1, suffix + ".bmp");
    }
    return newName;
}

//QImage PreviewProvider::requestImage(const QString & id, QSize * size, const QSize & requestedSize)
//{
//    cv::Mat img;
//    QString imgPath = id;
//    qDebug() << "PreviewProvider::updateImage id: " << id << "\t img_result: " << img_result.size();
//    imgPath = imgPath.replace("file://", "");
//    if (imgPath == QString(""))
//    {
//        return QImage();
//    } else if (imgPath.contains("save/")) {
//        imgPath = imgPath.replace("save/", "");
//        imgPath = addSuffix2FileName(imgPath, QString("_gray"));
//        img_result.save(imgPath);
//        QImage _img_result = img_result.copy();
//        img_result = QImage();
//        return _img_result;
//    }
//    img = cv::imread(imgPath.toStdString());
////    img_result = img;
//    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
//    cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
//    QImage _image((const unsigned char*)img.data, img.cols,
//                 img.rows, img.step, QImage::Format_RGB888);
//    img_result = _image.copy();
//    cv::resize(img, img, cv::Size(requestedSize.width(), requestedSize.height()));
//    QImage image((const unsigned char*)img.data, requestedSize.width(),
//                 requestedSize.height(), img.step, QImage::Format_RGB888);
////    size->setWidth(image.width());
////    size->setHeight(image.height());
////    qDebug() << "w: " << image.width() << ", h: " << image.height() << "\t rw: " << requestedSize.width() << "rh: " << requestedSize.height();
//    return image;
//}

PaintItem::PaintItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    imageToSend = new QImage(200,200,QImage::Format_RGB32);
    imageToSend->fill(QColor("black"));
}

QString PaintItem::addSuffix2FileName(const QString fileName, const QString suffix)
{
    QString newName = fileName;
    char len = fileName.length();
    if (newName.endsWith(".jpg")) {
        newName = newName.replace(len-4, len-1, suffix + ".jpg");
    } else if (fileName.endsWith(".png")) {
        newName = newName.replace(len-4, len-1, suffix + ".png");
    } else if (fileName.endsWith(".jpeg")) {
        newName = newName.replace(len-5, len-1, suffix + ".jpeg");
    } else if (fileName.endsWith(".bmp")) {
        newName = newName.replace(len-4, len-1, suffix + ".bmp");
    }
    return newName;
}
void PaintItem::toGray(cv::Mat *img)
{
    cv::cvtColor(*img, *img, cv::COLOR_BGR2GRAY);
}

QImage PaintItem::mat2QImage(const cv::Mat &mat)
{
    if(mat.type() == CV_8UC3)
    {
            //Copy input Mat
            const uchar *pSrc = (const uchar*)mat.data;
            // Create QImage with same dimensions as input Mat
            QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            return image.rgbSwapped();
    }
    qDebug() << "Mat2QImg error";
    return QImage();
}
void PaintItem::dealThisImg(QString path, QString mode)
{
    qDebug() << "dealThisImg received: " << path;
    path = path.replace("file://", "");
    if (path == QString(""))
    {
        *imageToSend = QImage();
    } else if (mode == QString("")) {
        cv::Mat img = cv::imread(path.toStdString());
        if (img.rows >= 1080) {
            double fx = (double)1080 / img.rows;
            qDebug() << "dealThisImg cv resize fx: " << fx;
            cv::resize(img, img, cv::Size(0, 0), fx, fx);
        }
        *imageToSend = mat2QImage(img);
//        QImage a = QImage(path);
//        if (a == *imageToSend) {
//            ;
//        } else {
//            *imageToSend = a;
//        }
    } else if (mode == QString("toGray")) {
        qDebug() << "dealThisImg cv read path: " << path;
        cv::Mat img = cv::imread(path.toStdString());
        if (img.rows >= 1080) {
            double fx = (double)1080 / img.rows;
            qDebug() << "dealThisImg cv resize fx: " << fx;
            cv::resize(img, img, cv::Size(0, 0), fx, fx);
        }
        toGray(&img);
        cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
        qDebug() << "dealThisImg chg done";
        *imageToSend = mat2QImage(img);
        qDebug() << "dealThisImg data chg done" << "\t cols: " << img.cols;
    } else if (mode == QString("save")) {
        // 使用数组记录操作步骤，预览使用小图处理，最后保存时再用原图处理一遍
        // 保留最原生的结果
        cv::Mat img = cv::imread(path.toStdString());
        toGray(&img);
        path = addSuffix2FileName(path, QString("_gray"));
//        path.insert(0, "file://");
        qDebug() << "image save to: " << path;
        cv::imwrite(path.toStdString(), img);
    }

//    update();
    updateImage(*imageToSend);
}
void PaintItem::updateImage(const QImage &image)
{
    update();
}
void PaintItem::paint(QPainter *painter)
{
    painter->drawImage(this->boundingRect(), *imageToSend);
}
