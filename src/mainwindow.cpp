#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEnginePage>
#include <QWebEngineDownloadRequest>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *vbox_main = new QVBoxLayout();
    ui->centralwidget->setLayout(vbox_main);
    std::string url_chatgpt = "https://chat.openai.com";
    std::string url_duckduckgo = "https://duckduckgo.com" ;
    std::string url_test1 = "https://github.com/neovim/neovim/releases" ;

    QUrl url = QUrl(QString::fromStdString(url_chatgpt));

    const std::string user_agent_firefox_linux115 = "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0";
    QString user_agent = QString::fromStdString(user_agent_firefox_linux115);
    QWebEngineView *view = new QWebEngineView(parent);

    // unique profile store per qtwbengine version
    QWebEngineProfile *profile = new QWebEngineProfile(QString::fromLatin1("MyApplication.%1").arg(qWebEngineChromiumVersion()));

    profile->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    profile->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    profile->settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
    profile->settings()->setAttribute(QWebEngineSettings::JavascriptCanPaste,true);
    profile->setHttpUserAgent(user_agent);
    // page using profile
    QWebEnginePage *page = new QWebEnginePage(profile);

     view->setPage(page);
     view->setUrl(url);

    vbox_main->addWidget(view);

}


MainWindow::~MainWindow()
{
    delete ui;
}



