#include "qtrtpvideo.h"
#include <QUrl>
#include <QDebug>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/ElementFactory>
#include <QGst/Parse>
#include <QGst/Bus>

RtpVideo::RtpVideo(QObject *parent)
    : QObject(parent), m_pipeline()
{
}

void RtpVideo::setVideoSink(const QGst::ElementPtr & sink)
{
    m_videoSink = sink;
}

void RtpVideo::play()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePlaying);
    }
}

void RtpVideo::pause()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePaused);
    }
}

void RtpVideo::stop()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StateNull);
    }
}

void RtpVideo::setSource(const QString & port)
{
    if (!m_pipeline) {
        QString pipe1Descr = QString("udpsrc port=\"")+port+QString("\" caps=\"application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)RAW, sampling=(string)RGB, depth=(string)8, width=(string)720, height=(string)576, colorimetry=(string)BT601-5, payload=(int)127, ssrc=(uint)0, timestamp-offset=(uint)0, seqnum-offset=(uint)0\" ! rtpjitterbuffer ! rtpvrawdepay ! videoconvert ! queue name=\"queue\""); // ! qtquick2videosink");
        m_pipeline = QGst::Parse::launch(pipe1Descr).dynamicCast<QGst::Pipeline>();
        if (m_pipeline) {
            m_pipeline->setProperty("video-sink", m_videoSink);
            if (!m_pipeline->add(m_videoSink))
            {
                qCritical()<<"Adding video sink to the pipeline failed";
            }
            QGst::ElementPtr el = m_pipeline->getElementByName("queue");
            if (!el)
            {
                qCritical()<<"Could not find the queue element";
            }
            else if(!el->link(m_videoSink))
            {
               qCritical()<<"Could not link queue to the video sink";
            }

            QGst::BusPtr bus = m_pipeline->bus();
            bus->addSignalWatch();
            QGlib::connect(bus, "message", this, &RtpVideo::onBusMessage);
        } else {
            qCritical() << "Failed to create the pipeline";
        }
    }
}

void RtpVideo::onBusMessage(const QGst::MessagePtr & message)
{
    switch (message->type()) {
    case QGst::MessageError: //Some error occurred.
        qCritical() << message.staticCast<QGst::ErrorMessage>()->error();
        stop();
        break;
    case QGst::MessageStateChanged:
        qCritical() << "State changed";
        break;
    case QGst::MessageApplication:
        qCritical() << "Application";
        break;
    default:
        qCritical() << "Custom event: " << message->type();
    }
}

#include "moc_qtrtpvideo.cpp"
