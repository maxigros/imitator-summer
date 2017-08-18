#include "storage.h"

Storage::Storage(QObject *parent) : QObject(parent)
{
    qDebug() << "Storage created";
}

Storage::~Storage()
{
    qDebug() << "Storage deleting";
}

void Storage::process(QString configFilename)
{
    configFile.setFileName(configFilename);
    if (!configFile.open(QIODevice::ReadOnly)){
        emit sendInfo(INFO_CONFIG_ERROR);
    }
    QJsonDocument configDocument = QJsonDocument::fromJson(configFile.readAll());
    configFile.close();
    QJsonObject configObject = configDocument.object();
    for (int i = 0; i < configObject.keys().count(); i++){
        // Текущее название параметра
        QString currentKey = configObject.keys().at(i);
        if (!currentKey.compare("TARGETS")){
            // Если сейчас "TARGETS", то сложная обработка
            if (configObject.value(currentKey).isArray()){
                // "TARGETS", все норм, действительно список
                QJsonArray configArray = configObject.value(currentKey).toArray();
                for (int j = 0; j < configArray.count(); j++){
                    QJsonObject tempObj = configArray[j].toObject();
                    QMap<QString, double> tempMap;
                    for (int k = 0; k < tempObj.keys().count(); k++){
                        QString currentTempKey = tempObj.keys().at(k);
                        tempMap[currentTempKey] = tempObj.value(currentTempKey).toDouble();
                    }
                    parameters.targets.append(tempMap);
                }
            } else{
                // "TARGETS", но ошибка в синтаксисе файла (не список)
                qDebug() << "targets error";
            }
        } else {
            // Если сейчас не "TARGETS", то простая обработка
            parameters.simple[currentKey] = configObject.value(currentKey).toDouble();
//            qDebug() << QString("%1 : %2")
//                        .arg(parameters.simple.keys().at(i))
//                        .arg(parameters.simple.value(parameters.simple.keys().at(i)));
        }
    }
}
