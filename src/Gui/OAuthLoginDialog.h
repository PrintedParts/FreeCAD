#pragma once

#include <QDialog>
#include <QString>
#include <QUrl>

namespace Gui {

class OAuthLoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OAuthLoginDialog(const QUrl& url, QWidget* parent = nullptr);

Q_SIGNALS:
    void loginSucceeded(const QString& payload);

private:
    QUrl m_url;
};

} // namespace Gui
