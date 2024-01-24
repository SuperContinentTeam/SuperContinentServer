#include "state_worker.h"


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

    std::string op = obj.value("op").toString().toStdString();
    QJsonValue body = obj.value("body");

    qDebug() << "Op: " << op;
    qDebug() << "Body:" << body;

    if(op == "updateStatus") {
        this->updateGameStatus(body.toString().toStdString());
    }

    if(op == "playerAction") {
        this->playerAction(peer, body.toObject());
    }
}


void StateWorker::updateGameStatus(const std::string& body)
{
    if(body == "start") {
        this->gsPtr->status = GameState::Status::RUNING;
        return;
    }

    if(body == "pause") {
        this->gsPtr->status = GameState::Status::PAUSE;
        return;
    }

    if(body == "") {
        this->gsPtr->status = GameState::Status::END;
        return;
    }
}

void StateWorker::playerAction(const QString& peer, const QJsonObject& body)
{
    std::string action = body.value("action").toString().toStdString();
    if(action == "join") {
        QString name = body.value("name").toString();
        PlayerPtr player(new Player(name, peer));
        this->gsPtr->playerJoin(peer, player);
    }

    if(action == "leave") {
        this->gsPtr->playerLeave(peer);
    }
}
