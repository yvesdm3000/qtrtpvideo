#ifndef __QTRTPVIDEOVIEW_H__
#define __QTRTPVIDEOVIEW_H__

#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include "qtrtpvideo.h"

class RtpVideoView : public QQuickView
{
    Q_OBJECT
public:
    RtpVideoView() : QQuickView(), m_video(nullptr){}

    void setVideo(RtpVideo* video)
    {
        rootContext()->setContextProperty(QLatin1String("player"), video);
        m_video = video;
    }

    bool event(QEvent *event) override
    {
        if (event->type() == QEvent::Close) {
            if (m_video)
                m_video->stop();
        }
        return QQuickView::event(event);
    }
private:
    RtpVideo* m_video;
};

#endif // __QTRTPVIDEOVIEW_H__
