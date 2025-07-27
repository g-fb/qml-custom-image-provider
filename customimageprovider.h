#ifndef CUSTOMIMAGEPROVIDER_H
#define CUSTOMIMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>
#include <QRunnable>

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

class AsyncImageResponseRunnable : public QObject, public QRunnable
{
    Q_OBJECT

public:
    AsyncImageResponseRunnable(const QString &id, const QSize &requestedSize);
    void run() override;

Q_SIGNALS:
    void done(QImage image);

private:
    QString m_id;
    QSize m_requestedSize;
};

#endif // CUSTOMIMAGEPROVIDER_H
