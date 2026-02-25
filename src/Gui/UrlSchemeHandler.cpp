#include "UrlSchemeHandler.h"

#include <QFileOpenEvent>
#include <QUrlQuery>

#include <cstdio>

namespace Gui {

UrlSchemeHandler::UrlSchemeHandler(QObject* parent)
    : QObject(parent)
{
    const char* path = "/tmp/PrintedPartsOAuth.log";
    if (FILE* f = std::fopen(path, "a")) {
        std::fprintf(f, "UrlSchemeHandler constructed\n");
        std::fclose(f);
    }
}

bool UrlSchemeHandler::eventFilter(QObject* obj, QEvent* ev)
{
    if (ev && ev->type() == QEvent::FileOpen) {
        auto* fe = static_cast<QFileOpenEvent*>(ev);
        const QUrl url = fe->url();
        if (url.isValid()) handleUrl(url);
        return false;
    }
    return QObject::eventFilter(obj, ev);
}

void UrlSchemeHandler::handleUrl(const QUrl& url)
{
    if (url.scheme() != "printedparts") return;

    QUrlQuery q(url);
    const QString code = q.queryItemValue("code");
    if (!code.isEmpty()) Q_EMIT oauthCodeReceived(code);
}

} // namespace Gui
