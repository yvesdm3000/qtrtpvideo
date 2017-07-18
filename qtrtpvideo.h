#ifndef __QTRTPVIDEO_H__
#define __QTRTPVIDEO_H__

#include <QObject>
#include <QGst/Pipeline>
#include <QGst/Message>

class RtpVideo : public QObject
{
    Q_OBJECT
public:
    explicit RtpVideo(QObject *parent = 0);

    void setVideoSink(const QGst::ElementPtr & sink);

public Q_SLOTS:
    void play();
    void pause();
    void stop();
    void setSource(const QString & uri);

private:
    void onBusMessage(const QGst::MessagePtr & message);

    QGst::PipelinePtr m_pipeline;
    QGst::ElementPtr m_videoSink;
};

#endif // __QTRTPVIDEO_H__
