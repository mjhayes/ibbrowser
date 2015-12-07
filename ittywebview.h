#ifndef ITTYWEBVIEW_H
#define ITTYWEBVIEW_H

#include <QMouseEvent>
#include <QWebView>

class IttyWebView : public QWebView
{
    Q_OBJECT

public:
    IttyWebView();

private:
    bool middleClick;

    QWebView *createWindow(QWebPage::WebWindowType type);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void handleLinkClicked(const QUrl &url);
};

#endif // ITTYWEBVIEW_H
