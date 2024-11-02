#ifndef CUSTOMIMAGEPROVIDER_H
#define CUSTOMIMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>

class CustomImageProvider : public QQuickAsyncImageProvider
{
public:
    explicit CustomImageProvider();
    QQuickImageResponse *requestImageResponse(const QString &id, const QSize &requestedSize) override;
};

class CustomImageResponse : public QQuickImageResponse
{
public:
    CustomImageResponse(const QString &id, const QSize &requestedSize);

    QQuickTextureFactory *textureFactory() const override;

private:
    QImage m_image;
};

#endif // CUSTOMIMAGEPROVIDER_H