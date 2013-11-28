/*
AUTHOR: Giuseppe Federico Gullo
DATE: 07/05/2012
DESCRIPTION: Classe che decifra i segnali inviati dal Joystick (controller)
*/

#include "qcontroller.h"
#include "SDL/SDL.h"


SDL_Joystick *stick = NULL;
SDL_Event event;


//Costruttore della classe
QController::QController(QObject* parent) :
QObject(parent)
{
    refresh=new QTimer(this); //Costruisce un Timer per temporizzare la scansione dei tasti
    delay=new QTimer(this);   //Costruisce un Timer per inserire un delay dopo la pressione di un tasto
    delay->setInterval(1000);
    speed=time=0;
    wait=false;
}

//Cerca di inizializzare il joystick
bool QController::Init()
{
    if( SDL_Init( SDL_INIT_JOYSTICK) == -1 )
    {
        return false;
    }
    return true;
}

//Verifica se ci sono joystick disponibili
bool QController::Check()
{
    QString joy;
    if(SDL_NumJoysticks()==1)   //SDL_NumJoysticks() torna un intero che equivale al numero di joystick rilevati
    {
        log->append("Un joystick rilevato");
        return true;
    }
    else if(SDL_NumJoysticks()>1)
    {
        log->append(joy.number(SDL_NumJoysticks())+" joystick rilevati");
        return true;
    }
    else
    {
        log->append("Nessun joystick rilevato");
        return false;
    }
}

//Si connette al primo joystick disponibile
bool QController::Conn()
{
    SDL_JoystickEventState(SDL_ENABLE);
    stick = SDL_JoystickOpen(0);

    if( stick == NULL )
    {
        log->append("Impossibile collegare il joystick");
        return false;
    }
    log->append("Joystick collegato");
    refresh->setInterval(150);
    refresh->start();
    connect(refresh, SIGNAL(timeout()),this,SLOT(getData()));
    connect(delay, SIGNAL(timeout()),this,SLOT(waiting()));
    return true;
    
}

//Delay tra le letture del Joystick
void QController::waiting()
{
    delay->stop();
    wait=false;
}

//Leggi i dati dal joystick
int QController::getData()
{
    int ysx,y,s_plus,s_minus,t_plus,t_minus,f;
    SDL_Event event2;
    SDL_PollEvent(&event2);

    //Giusè ho attivato tutti i tasti ora no?
    ysx=(int)SDL_JoystickGetAxis(stick, 1);
    y= (int) SDL_JoystickGetAxis(stick, 3);
    f=(int)SDL_JoystickGetButton(stick,9);
    int tasto12 = SDL_JoystickGetButton(stick, 11);
    s_plus=(int)SDL_JoystickGetButton(stick,7);
    s_minus=(int)SDL_JoystickGetButton(stick,6);
    t_plus=(int)SDL_JoystickGetButton(stick,0);
    t_minus=(int)SDL_JoystickGetButton(stick,2);
    int tasto5= SDL_JoystickGetButton(stick, 4);
    int tasto11=SDL_JoystickGetButton(stick, 10);
    int tasto6= SDL_JoystickGetButton(stick, 5);

    if((int)SDL_JoystickGetButton(stick,8)) //Giusè, quando implementavo i tasti non ho implementato questo: era da fare?
                                            // è il tasto 9.
    {
        comm->send("s");
    }

    if(s_plus)
    {
        if(speed<5)
        {
        speed++;
        //log->append("Velocità: "+n.number(speed));
        comm->valSpeed->setCurrentIndex(speed);
        }
    }

    if(s_minus)
    {
        if(speed>0)
        {
        speed--;
        //log->append("Velocità: "+n.number(speed));
        comm->valSpeed->setCurrentIndex(speed);
        }
    }

    if(t_plus)
    {
        if(time<5)
        {
        time++;
        //log->append("Tempo: "+n.number(time));
        comm->valTime->setCurrentIndex(time);
        }
    }

    if(t_minus)
    {
        if(time>0)
        {
        time--;
        //log->append("Tempo: "+n.number(time));
        comm->valTime->setCurrentIndex(time);
        }
    }

    if(tasto12)
    {
        comm->sendControll(1, 40000, ysx, comm->valSpeed->currentIndex(),comm->valTime->currentIndex());
        wait=true;
        delay->start();
    }


    if(tasto11)
    {

        comm->sendControll(1, y, 40000, comm->valSpeed->currentIndex(),comm->valTime->currentIndex());
        wait=true;
        delay->start();
    }



    if(f && !wait) //Qua
    {
         comm->sendControll(1, y, ysx, comm->valSpeed->currentIndex(),comm->valTime->currentIndex());
         wait=true;
         delay->start();
    }

    return 1;
}



//Disconnette il Joystick
int QController::disc()
{
    refresh->stop();
    refresh->~QTimer(); //Distrugge il Timer
    return 1;
}
