#ifndef listener_DIANALISTENER_H
#define listener_DIANALISTENER_H

#include <QString>
#include <QObject>

/**
 * Diana listener public class. 
 * */

namespace dianalistener {

class Listener;

class DianaListener : public QObject {
Q_OBJECT
  friend class DianaListenerFactory;
public:

  QString getPublisherName() { return publisherName; };
  ~DianaListener();


private:
	DianaListener(QObject* parent, const QString& publisherName);
  void init(const QString& master, const QString& host);

Q_SIGNALS:
  void newMessage(const QString& data);

private:
  QString publisherName;
  Listener* listener;

};

}  // namespace dianalistener

#endif 
