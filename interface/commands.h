#ifndef COMMANDS_H
#define COMMANDS_H
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QTextEdit>

using namespace std;

class Commands
{
  //PROTOTYPE
public:
    Commands();
    char *getCommand(QString id);
    int getCommand_from_shell(QString cmd,char *data);
    int getControllX(int val);
    int getControllY(int val);

    int ext(QString shcmd,char *data);

    bool Autocorrection(QString shcmd);

  //VARIABLE
public:
   string cmd;
};

#endif // COMMANDS_H
