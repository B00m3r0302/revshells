#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGuiApplication>
#include <QClipboard>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 1) Make window frameless and translucent
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->setupUi(this);

    // 2) Add a glow effect to the central widget
    auto *glow = new QGraphicsDropShadowEffect(this);
    glow->setBlurRadius(40);
    glow->setOffset(0);
    glow->setColor(QColor(142, 68, 173, 200)); // neon purple
    ui->centralWidget->setGraphicsEffect(glow);

    // Semi-transparent, neon-accented styling
    qApp->setStyleSheet(R"(
        /* Base window: dark, semi-transparent */
        QMainWindow {
            background-color: rgba(20, 20, 30, 200);
        }
            
        /* All input controls */
        QLineEdit, QSpinBox, QComboBox, QTextEdit {
            background-color: rgba(30, 30, 50, 180);
            border: 1px solid rgba(100, 0, 200, 180);
            border-radius: 4px;
            color: #EEE;
            padding: 4px;
            selection-background-color: rgba(142, 68, 173, 150);
            selection-color: #FFF;
        }
            
        /*  Buttons with newo hover/focus */
        QPushButton {
            background-color: rgba(142, 68, 173, 200);
            border: none;
            border-radius: 4px;
            padding: 6px 12px;
            color: #FFF;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: rgba(188, 77, 232, 220);
        }
        QPushButton:pressed {
            background-color: rgba(120, 50, 145, 220);
        }
            
        /* Text in the output area: monospace */
        QTextEdit {
            font-family: "Courier New", monospace;
            font-size: 12px;
        }
    )");

    // Populate controls
    ui->listenerComboBox->addItems({
        "hoaxshell", "msfconsole", "nc_busybox", "nc_freebsd", "nc", "ncat_exe", "ncat_tls", "ncat", "openssl", "powercat", "pwncat_windows", "pwncat", "rlwrap_nc", "rustcat", "socat", "socat_tty", "windows_conpty" 
    });
    ui->payloadComboBox->addItems({
        "bash_i", "bash_196", "bash_rl", "bash_5", "nc_mkfifo", "nc_e", "nc_exe", "busybox_nc", "nc_c", "ncat_", "ncat_exe_e", "ncat_udp", "curl", "rustcat", "c", "c_windows", "c_sharp_tcp_client", "c_sharp_bash_i", "haskell", "openssl", "perl", "perl_no_sh", "perl_pentestmonkey", "php_pentestmonkey", "php_ivan"
    });
    ui->encodingComboBox->addItems({
        "none", "base64", "url", "double_url"
    });

    // Connect signals to slots
    connect(ui->copyButton, &QPushButton::clicked,
            this, &MainWindow::copyToClipboard);
    connect(ui->ipLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::generateCommand);
    connect(ui->portSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &MainWindow::generateCommand);
    connect(ui->listenerComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::generateCommand);
    connect(ui->payloadComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::generateCommand);
    connect(ui->encodingComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::generateCommand);

    // 4) Generate the initial command
    generateCommand();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateCommand()
{
    const QString ip               = ui->ipLineEdit->text();
    const int port                 = ui->portSpinBox->value();
    const QString listener         = ui->listenerComboBox->currentText();
    const QString payload          = ui->payloadComboBox->currentText();
    const QString encoding         = ui->encodingComboBox->currentText();

    // Placeholder for actual factory logic
    QString cmd = QString("%1 listener: %2 on %3:%4")
                    .arg(payload, listener, ip)
                    .arg(port);

    if (encoding == "base64") {
        cmd = cmd.toUtf8().toBase64();
    } else if (encoding == "url") {
        cmd = QUrl::toPercentEncoding(cmd);
    } else if (encoding == "double_url") {
        cmd = QUrl::toPercentEncoding(
            QUrl::toPercentEncoding(cmd)
        );
    }

    ui->commandTextEdit->setPlainText(cmd);
}

void MainWindow::copyToClipboard()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->commandTextEdit->toPlainText());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint()
            - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}