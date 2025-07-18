#include "PayloadGenerator.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QUrl>

PayloadGenerator::PayloadGenerator(QObject *parent) : QObject(parent) {
    loadTemplates();
}

void PayloadGenerator::loadTemplates() {
    QFile file("/payloads/templates.json"); // Loaded from QRC
    if (!file.open(QIODevice::ReadOnly)) return;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QjsonObject obj = doc.object();
    for (auto key : obj.keys())
        m_templates[key] = obj[key].toString();
}

QString PayloadGenerator::encode(const QString &input, const QString &encoding) {
    QByteArray data = input.toUtf8();
    if (encoding == "Base64") return QString::fromUtf8(data.toBase64());
    if (encoding == "URL") return QString(QUrl::toPercentEncoding(input));
    if (encoding == "DoubleURL") return QString(QUrl::toPercentEncoding(QUrl::toPercentEncoding(input)));
    return input;
}

void PayloadGenerator::generate(const QString &language, const QString &ip, const QString &port, const QString &encoding) {
    QString templateStr = m_templates.value(language);
    templateStr.replace("$IP", ip).replace("$PORT", port);
    m_payload = encode(templateStr, encoding);
    emit payloadChanged();
}

QString PayloadGenerator::payload() const {
    return m_payload;
}
