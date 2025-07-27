#include "customimageprovider.h"

#include <QTransform>
#include <QThreadPool>

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
    auto runnable = new AsyncImageResponseRunnable(id, requestedSize);
    connect(runnable, &AsyncImageResponseRunnable::done, this, [this](QImage image) {
        m_image = image;
        Q_EMIT finished();
    });

    QThreadPool::globalInstance()->start(runnable);
}

QQuickTextureFactory *CustomImageResponse::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(m_image);
}

AsyncImageResponseRunnable::AsyncImageResponseRunnable(const QString &id, const QSize &requestedSize)
    : m_id{id}
    , m_requestedSize{requestedSize}
{
}

void AsyncImageResponseRunnable::run()
{
    QImage image{m_id};
    QImage scaled = image.scaled(m_requestedSize);
    QImage rotatedImage = scaled.transformed(QTransform().rotate(180.0));

    Q_EMIT done(rotatedImage);
}
