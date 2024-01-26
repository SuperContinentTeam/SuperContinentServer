#include "state_worker.h"

StateWorker::StateWorker() : QThread(nullptr) {}

void StateWorker::setGameStatePtr(GameStatePtr gsPtr) { this->gsPtr = gsPtr; }

void StateWorker::textCommandExecuater(QString peer, QString message) {
  qDebug() << "From " << peer << " get signal: " << message;

  QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
  qDebug() << doc;

  if (!doc.isObject())
    return;

  QJsonObject obj = doc.object();

  std::string op = obj.value("op").toString().toStdString();
  QJsonValue body = obj.value("body");

  qDebug() << "Op: " << op;
  qDebug() << "Body:" << body;

  if (op == "updateStatus") {
    this->updateGameStatus(body.toString().toStdString());
  }

  if (op == "playerAction") {
    this->playerAction(peer, body.toObject());
  }

  if (op == "chatMessage") {
    this->chatMessage(peer, body.toString());
  }
}

void StateWorker::updateGameStatus(const std::string &body) {
  if (body == "start") {
    this->gsPtr->status = GameState::Status::RUNING;
    return;
  }

  if (body == "pause") {
    this->gsPtr->status = GameState::Status::PAUSE;
    return;
  }

  if (body == "") {
    this->gsPtr->status = GameState::Status::END;
    return;
  }
}

void StateWorker::playerAction(const QString &peer, const QJsonObject &body) {
  std::string action = body.value("action").toString().toStdString();
  QString name = body.value("name").toString();

  if (action == "join") {
      PlayerPtr player(new Player(name, peer));
      if (gsPtr->status != GameState::Status::INIT) {
          emit this->sendToOnePlayer(peer, "不能加入已运行的房间");
      }
      if (gsPtr->playerJoin(peer, player)) {
          qInfo() << QString("Player[%1] join").arg(name);
      } else {
          emit this->sendToOnePlayer(peer, "房间已满，加入失败");
      }
  }

  if (action == "leave") {
    this->gsPtr->playerLeave(peer);

    qInfo() << QString("Player[%1] leave").arg(name);
  }
}

void StateWorker::chatMessage(const QString &peer, const QString &message) {
    QString msg = QString("%1 said: %2").arg(peer, message);
    emit this->sendToAllPlayer(msg);
}
