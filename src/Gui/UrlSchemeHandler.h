#pragma once

#include <QObject>
#include <QString>
#include <QUrl>
#include <QEvent>

namespace Gui {

class UrlSchemeHandler : public QObject
{
    Q_OBJECT
public:
    explicit UrlSchemeHandler(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* ev) override;

Q_SIGNALS:
    void oauthCodeReceived(const QString& code);

private:
    void handleUrl(const QUrl& url);
};

} // namespace Gui
