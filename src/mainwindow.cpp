#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEnginePage>
#include <QWebEngineDownloadRequest>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QVBoxLayout *vbox_main = new QVBoxLayout(this);
    ui->centralwidget->setLayout(vbox_main);
    std::string url_chatgpt = "https://chat.openai.com";
    std::string url_duckduckgo = "https://duckduckgo.com" ;
    std::string url_test1 = "https://github.com/neovim/neovim/releases" ;
    QString darkreader_cdn_jsdeliver = "https://cdn.jsdelivr.net/npm/darkreader@4.9.73/darkreader.min.js";

    QUrl url = QUrl(QString::fromStdString(url_chatgpt));

    const std::string user_agent_firefox_linux115 = "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0";
    QString user_agent = QString::fromStdString(user_agent_firefox_linux115);
    QWebEngineView *view = new QWebEngineView(parent);

    // unique profile store per qtwbengine version
    QWebEngineProfile *profile = new QWebEngineProfile(QString::fromLatin1("MyApplication.%1").arg(qWebEngineChromiumVersion()));

    profile->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    profile->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    profile->setHttpUserAgent(user_agent);
    // page using profile
    QWebEnginePage *page = new QWebEnginePage(profile);

     view->setPage(page);
     view->setUrl(url);

    vbox_main->addWidget(view);

    // Inject external JavaScript from a CDN after the page has loaded
    QObject::connect(page, &QWebEnginePage::loadFinished, [=](bool) {
        QNetworkAccessManager *networkManager = new QNetworkAccessManager(page);

        // Replace 'https://cdn.example.com/your/script.js' with the actual CDN URL of your script
        QUrl scriptUrl = QUrl(darkreader_cdn_jsdeliver);

        QNetworkRequest request(scriptUrl);

        QNetworkReply *reply = networkManager->get(request);

        QObject::connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QString scriptContent = QString::fromUtf8(reply->readAll());

                // Run the JavaScript code in the context of the loaded webpage
                page->runJavaScript(scriptContent);
                page->runJavaScript("DarkReader.enable();");
            } else {
                qDebug() << "Failed to download the script from the CDN. Error: " << reply->errorString();
            }

            // Clean up
            reply->deleteLater();
            networkManager->deleteLater();
        });
    });

}


MainWindow::~MainWindow()
{
    delete ui;
}



