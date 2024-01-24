#include "state_worker.h"
#include "qjsonobject.h"


StateWorker::StateWorker():QThread(nullptr){}

void StateWorker::setGameStatePtr(GameStatePtr gsPtr)
{
    this->gsPtr = gsPtr;
}

void StateWorker::textCommandExecuater(QString peer, QString message)
{
    qDebug() << "From " << peer << " get signal: " << message;

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    qDebug() << doc;

    if(!doc.isObject()) return;

    QJsonObject obj = doc.object();

    QString op = obj.value(QString("op")).toString();
    QJsonValue body = obj.value(QString("body"));

    qDebug() << "Op: " << op;
    qDebug() << "Body:" << body;

    if(!op.compare("updateStatus")) {
        this->updateGameStatus(body.toString());
    }
}


void StateWorker::updateGameStatus(QString body)
{
    if(!body.compare("start")) {
        this->gsPtr->status = GameState::Status::RUNING;
        return;
    }

    if(!body.compare("pause")) {
        this->gsPtr->status = GameState::Status::PAUSE;
        return;
    }

    if(!body.compare("end")) {
        this->gsPtr->status = GameState::Status::END;
        return;
    }
}
