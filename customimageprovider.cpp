#include "customimageprovider.h"

#include <QTransform>

CustomImageProvider::CustomImageProvider()
    : QQuickAsyncImageProvider()
{

}

QQuickImageResponse *CustomImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize)
{
    auto response = new CustomImageResponse(id, requestedSize);
    return response;
}

CustomImageResponse::CustomImageResponse(const QString &id, const QSize &requestedSize)
{
    QImage image{id};
    QImage scaled = image.scaled(requestedSize);
    QImage rotated = scaled.transformed(QTransform().rotate(180.0));
    m_image = rotated;

    Q_EMIT finished();
}

QQuickTextureFactory *CustomImageResponse::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(m_image);
}