#include "ittywebview.h"

IttyWebView::IttyWebView() : QWebView(), middleClick(false)
{
    QObject::connect(this, SIGNAL(titleChanged(QString)), this, SLOT(setWindowTitle(QString)));
    QObject::connect(this, SIGNAL(linkClicked(QUrl)), this, SLOT(handleLinkClicked(QUrl)));
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

QWebView *IttyWebView::createWindow(QWebPage::WebWindowType type)
{
    Q_UNUSED(type);

    qDebug() << "createWindow";
    return new IttyWebView();
}

void IttyWebView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
        middleClick = true;
    else
        middleClick = false;

    QWebView::mouseReleaseEvent(event);
}

void IttyWebView::handleLinkClicked(const QUrl &url)
{
    qDebug() << "handleLinkClicked";

    if (middleClick) {
        IttyWebView *wv = new IttyWebView();
        wv->load(url);
        wv->show();
    } else {
        this->load(url);
    }
}
