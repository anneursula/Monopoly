//oooooookay where to start? 
//Klasse Straße inkl Attribute
#include "Haus.hpp"
#include <list>
#include <iostream>
using namespace std;

class Straße {
    private:
    
        string name;
        int miete; 
        bool verkauft; 
        bool hypothek; 
        int posX; 
        int posY;
        string color; 
        //stellt die Straße als Rechteck auf dem Spielfeld da.
        Rect *r = nullptr;
        //stellt die Häuser da
        Haus *haeuser[4] = {nullptr, nullptr, nullptr, nullptr};

    
    public:    

       
        Straße(string name, int miete, int posX, int posY, SVG* brett){
            this->name = name;
            this->miete = miete;
            verkauft = false; 
            hypothek = false; 
            this->posX = posX;
            this->posY = posY;
            this->r= new Rect(posX,posY,100,100,brett);
            this ->r->setFill("green");
            
            //Häuser initialisieren
            for(int i = 0; i <4;i++){               
                Haus *hausZeiger = new Haus(miete *(1/3));
                haeuser[i] = hausZeiger;
                Rect *r3= new Rect(posX + (i*10),posY,10,10,brett);
                r3->setFill("white");
                haeuser[i] -> setRect(r3);
            }
        }
        
    
       
    
        void setRect(Rect *r2){
            this -> r = r2;
        }
    
        Rect* getRect(){
            return r;
        }
    
        void setColor(string color){
            this->color = color; 
        }
   
        void setName(string name) {
            this->name = name;
        }

        string getName() {
            return name;
        }

        void setMiete(int miete){
            this->miete = miete;
        }

        int getMiete(){
            return miete;
        }

        void setVerkauft(bool verkauft){
            this->verkauft = verkauft; 
        }

        bool getVerkauft(){
            return verkauft;
        }

        void setHypothek(bool hypothek){
            this->hypothek = hypothek;
        }

        bool getHypothek(){
            return hypothek;
        }
    
        /*
        gibt nächstes baufähige Haus zurück.
        */
        Haus* getHouse(){
           return haeuser[this->getAnzahlHaeuser()];
        }
    
    
        /*
        gibt an, wieviele Häuserschon gebaut wurden.
        */
        int getAnzahlHaeuser(){
          int zaehler = 0;
          for(int i= 0;i<4;i++){
              if(haeuser[i]->getBuilt()){
                 zaehler++;
               }
          }
            return zaehler;
        }
       
        //DESTRUKTOR
        ~Straße(){
            delete r;
             for(int i = 0; i <4;i++){               
                delete haeuser[i];
            }
        }
    
};

