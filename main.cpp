#include "qtrtpvideo.h"
#include "qtrtpvideoview.h"
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QGst/Init>
#include <QGst/Quick/VideoSurface>

int main(int argc, char **argv)
{
//    qputenv("GST_PLUGIN_PATH", QTVIDEOSINK_PATH);

    QGuiApplication app(argc, argv);
    QGst::init(&argc, &argv);

    RtpVideoView view;

    
    QGst::Quick::VideoSurface *surface = new QGst::Quick::VideoSurface;
    view.rootContext()->setContextProperty(QLatin1String("videoSurface1"), surface);

    RtpVideo *video = new RtpVideo(&view);
    video->setVideoSink(surface->videoSink());
    if (argc > 1)
        video->setSource(QString::fromLocal8Bit(argv[1]));
    else
        video->setSource(QLatin1Literal("1234"));
    //view.rootContext()->setContextProperty(QLatin1String("player"), video);
    view.setVideo(video);

//    view.engine()->addImportPath(QLatin1String(UNINSTALLED_IMPORTS_DIR));

    view.setSource(QUrl(QLatin1String("qrc:///qtrtpvideo.qml")));
    view.show();

    video->play();

    return app.exec();
}
