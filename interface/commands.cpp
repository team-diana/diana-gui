#include "commands.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "d_logger.h"
#include <QTextEdit>

/*
AUTHOR: Giuseppe Federico Gullo
DATE: 17/04/2012
DESCRIPTION: Classe che gestisce i comandi da inviare al rover
*/

string cmds[]={"camp master","camp potenza","camp motori","camp sensori","carica scheda","x","spegni motore","accendi motore","daimplementare","spegni scheda","accendi scheda","polling","pov","daimplementare","scarica scheda","tempo","velocità"};


//Costruttore della classe, vuoto perchè non c'è niente da inizializzare
Commands::Commands()
{

}

//Non mi ricordo cosa volevo fare con questa funzione
char *Commands::getCommand(QString shcmd)
{
    char *data;
    return data;
}

//Funzione molto confusa che decifra i comandi inviati da shell
int Commands::getCommand_from_shell(QString shcmd,char *data)
{
    //Se il comando è in sintassi estesa, divide il comando dall'argomento
    QStringList id_split=shcmd.split(":",QString::SkipEmptyParts);
    //Caso in cui il comando non richiede un'argomento
   if(id_split[0]=="blocca motori" || id_split[0]=="s") //solo il comando blocca motori non richiede un'argomento
    {
        data[0]='s';
        data[1]=NULL;
        return 1;
    }
   //Caso in cui il comando esteso richiedo un'argomento
    else if(id_split.length()>=2) //Se il comando è esteso e richiede un argomento
    {                               //la il vettore ottenuto dalla stringa conterrà almeno due valori
        sscanf(&id_split[1].toStdString().c_str()[0],"%s",&data[1]);
        string cmd2=id_split[0].toStdString();
        char ids[]={'a','b','c','d','e','x','g','h','i','f','o','n','p','r','q','t','v'};
        int i;
        for(i=0;i<19;i++)
        {
            qDebug("compare %s with %s",cmd2.c_str(),cmds[i].c_str());
            //qDebug("intero %d stringa %s",intero,stringa);


            if(cmd2.compare(cmds[i])==0)
            {
                data[0]=ids[i];
                return 1;
            }
        }
     }
   //Caso in cui il comando in forma abbreviata richiete un'argomento
   else if(shcmd.length()<=3) //Se il comando è in forma abbreviata, la lunghezza della stringa sarà <=3
    {
       sscanf(&shcmd.toStdString().c_str()[1],"%s",&data[1]);
       data[0]=shcmd.toStdString().c_str()[0];
       return 1;
    }
    return 0;
}

//Funzione deprecata
int Commands::ext(QString shcmd,char *data)
{

   /* if(shcmd[0]=='x')
    {
        data[0]='x';
        data[1]=shcmd[1].toAscii();
        data+2=tmp->mid(2).toStdString().c_str();
    }*/
    return 1;
}


//Matteo Bertolino: Legge i dati dal Joystick per l'asse Y
int Commands::getControllY(int val)
{
    FILE* registrazione_eventi;
    registrazione_eventi=fopen("file_eventi.txt", "w");
    int cval;
    qDebug("Joystick: %d\n",val);
    fprintf(registrazione_eventi, "Joystick ingresso destro: %d\n", val);


    cval=(((-254.00000/65535.00000)*val) + 128);
    fprintf(registrazione_eventi, "Joystick ingresso convertito destro: %d\n", cval);

    if (val==40000) //Relativo al tasto n 12
        cval=0;

if(cval<0 || cval>255)
{       dLog("Attenzione! Siamo fuori dall'intervallo 0-255 dx");
        fprintf(registrazione_eventi, "Attenzione, il valore %d del dx è fuori dall'intervallo 0-255\n", cval);

}

    dLog(QString().sprintf("Joystick convertito: %d\n", cval));
    dLog("TEST 0");

    return cval;
} //fine gestione joystick


bool Commands::Autocorrection(QString shcmd)
{
    int match=0,tmp,i,j,cstring;
    for(i=0;i<19;i++)
    {
        tmp=0;
        for(j=0;j<shcmd.length();j++)
        {
            if(j>cmds[i].length())
                break;
            if(shcmd.toStdString().at(j)==cmds[i].at(j))
                tmp++;
        }
        if(tmp>match)
        {
            match=tmp;
            cstring=i;
        }
    }
    if(match<4)
        return false;
    shcmd.fromStdString(cmds[cstring]);
    return true;
}
