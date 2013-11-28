#include "qutty.h"
#include "qutty_config_window.h"
#include "GuiTerminalWindow.h"
#include <QBoxLayout>
#include <QSizePolicy>
#include <QTabWidget>


Qutty::Qutty(QObject *parent, QTabWidget* tabWidget) :
    QObject(parent),
    tabWidget(tabWidget)
{
    tabWidget->setTabsClosable(true);
    connect( tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)) );
}

void Qutty::closeTab(int tabN) {
   tabWidget->removeTab(tabN);
}

bool Qutty::createNewTab() {
    Qutty_config_window* config = new Qutty_config_window();
    connect(config, SIGNAL(onAccepted()), this, SLOT(initTab()));
    initConfigDefaults(config->getConfig());
    config->show();

    return true;
}

bool Qutty::initTab() {
    Qutty_config_window* config = (Qutty_config_window*) sender();
    if(!config)
        return false;
    QWidget* page = new QWidget(tabWidget);
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, page);
    GuiTerminalWindow* termWnd = new GuiTerminalWindow(page);
    layout->addWidget(termWnd);
    termWnd->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    termWnd->setUpdatesEnabled(true);
    int newTabIndex = tabWidget->addTab(page, tr("PuTTY"));
    tabWidget->setCurrentIndex(newTabIndex);
    termWnd->setFocus();
//    termWnd->setWindowState(termWnd->windowState() | Qt::WindowMaximized);
    termWnd->cfg = *(config->getConfig());

    if (termWnd->initTerminal()) {
        // remove page here;
    } else {    // success
        tabWidget->setCurrentWidget(page);
    }


    config->close();
    delete config;
    return true;
}
