#ifndef listener_DIANALISTENERFACTORY_H
#define listener_DIANALISTENERFACTORY_H

#include <QString>
#include "diana_listener.hpp"

/**
 * // written by Vincenzo Giovanni Comito < clynamen@gmail.com > the 19-07-13
 * Factory for creating listeners. Since we have to address the problem of the 
 * multiple threads in the future, we use a factory for creating each listener.
 * In the future, many listener will live in the same thread.
 * */

namespace dianalistener {

class DianaListenerFactory  {

public:
  DianaListenerFactory(const QString& master, const QString& host);
  DianaListener* createListener(const QString& publisherName);

private:
  QString master;
  QString host;

};

}  // namespace dianalistener

#endif 
