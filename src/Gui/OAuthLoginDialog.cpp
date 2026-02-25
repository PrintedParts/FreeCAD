#include "OAuthLoginDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

namespace Gui {

OAuthLoginDialog::OAuthLoginDialog(const QUrl& url, QWidget* parent)
    : QDialog(parent), m_url(url)
{
    setWindowTitle(QStringLiteral("PrintedParts Login"));
    setModal(true);
    resize(520, 220);

    auto* layout = new QVBoxLayout(this);

    auto* lbl = new QLabel(this);
    lbl->setText(QStringLiteral("OAuth start URL:\n%1").arg(m_url.toString()));
    lbl->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lbl->setWordWrap(true);
    layout->addWidget(lbl);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttons);
}

} // namespace Gui
