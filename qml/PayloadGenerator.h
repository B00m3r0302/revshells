#ifndef PAYLOADGENERATOR_H
#define PAYLOADGENERATOR_H

#include <QObject>
#include <QString>
#include <QMap>

class PayloadGenerator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString payload READ payload NOTIFY payloadChanged)

public:
    explicit PayloadGenerator(QObject *parent = nullptr);

    Q_INVOKABLE void generate(const QString &language, const QString &ip, const QString& port, const QString &encoding);
    QString payload() const;

signals:
    void payloadChanged();

private:
    QString m_payload;
    QMap<QString, QString> m_templates; // Loaded from file or hardcoded
    QString encode(const QString &input, const QString &encoding);
    void loadTemplates();
};

#endif // PAYLOADGENERATOR_H

