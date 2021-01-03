#include "Straße.hpp"
#include <iostream>
using namespace std;

class Spieler{
    
    private:
    string name;
    int kapital;
    //Alle Straßen des Spielers gesammelt in einem Vektor
    vector <Straße*> straßen; 
    int feldPos;
    //Color als RGB-Werte
    int color[3];
    //Der Circle stellt den Spieler auf dem Spielbrett da
    Circle *c = nullptr;
    bool imprisoned;
    
    

    public:
    Spieler(string name, SVG *brett, int color[], int pos){
        this -> name = name;
        kapital = 400; //Anfangskapital
        feldPos = 0;
        this->c= new Circle(pos,30,10,brett); //y-Werte und Radius festgelegt
        this->c->setFill(color[0],color[1],color[2]);
        this->color[0] = color[0];
        this->color[1] = color[1];
        this->color[2] = color[2];
        imprisoned = false;
        
    }
    
    void setName(string name){
        this->name = name; 
    }
    
    
    
    void setCircle(Circle *c2){
            this-> c = c2;
        }
    
    //würfel Zahl zwischen 1-6
    int wuerfeln(){
         return rand()%6 + 1;
    }
    
   
    int getKapital(){
        return kapital;
    }
    
    string getName(){
        return name;
    }
    
    
    Circle* getCircle(){
        return c;
    }
    
    int getFeldPos(){
        return feldPos;
    }
    
    void setFeldPos(int pos){
        this->feldPos = pos;
    }
    
    void setImprisoned(bool prison){
        this->imprisoned = prison; 
    }
    
    bool getImprisoned(){
        return imprisoned; 
    }
    
    /*
    Miete Zahlen nur möglich, falls Straße nicht hypothek gesetzt ist und 
    Spieler genug Kapital besitzt.
    */
    void mieteZahlen(Spieler &spieler, Straße &straße){
        if(straße.getHypothek() == false){
            if(straße.getMiete() <= kapital){
                spieler.mieteErhalten(straße.getMiete());
                kapital = kapital - straße.getMiete();
            }
        }

    }
    
    void mieteErhalten(int miete){
        this->kapital = this->kapital + miete;
    }
    
    /*
    Straße wird gekauft und nimmt die Farbe des Spielers an
    */
    void straßeKaufen(Straße &straße){
        straßen.push_back(&straße);
        straße.setVerkauft(true);
        this->kapital = this->kapital - straße.getMiete();
        straße.getRect()->setFill(color[0],color[1],color[2]);
    }   
    
    bool kaufenMoeglich(Straße &straße){
         return kapital >= straße.getMiete();

    }
    
    bool mieteZahlenMoeglich(Straße &straße){
        return (this->kapital > straße.getMiete());
    }
    
    
    /*
    Geht eigene Straßen durch und überprüft, ob Name gleich zu der 
    übergebenen Straße
    */
    bool besitzeStraße(Straße &str){
        for(Straße *eigeneStr: straßen){
            if(eigeneStr->getName()==str.getName()){
                return true;
            }
        }
        return false;
    }
    
    /*
    Straße wird hypothek gesetzt und Spieler erhält Wert der Straße.
    Straße wird transparent.
    */
    bool HypothekAufnehmen(Straße &str){
        if(str.getHypothek() == false){
            this->mieteErhalten(str.getMiete());
            str.setHypothek(true); 
            str.getRect()->setFill(color[0],color[1],color[2], 0.5);
            return true;
            }
        else{
            return false; 
        }
    }
    
    
    void HypothekAufloesen(Straße &str){
        kapital = kapital-str.getMiete(); 
        str.setHypothek(false); 
        str.getRect()->setFill(color[0],color[1],color[2]); 
        
    }
            
       
    vector <Straße*> getStreets(){
        return straßen; 
    }
    
    
    /*
    Gibt die Straßen zurück, die Spieler hypothek gesetzt hat.
    */
    vector <Straße*> getStreetsHypothek(){
        vector <Straße*> straßenHypothek;
        for(Straße *str: straßen){
                if(str->getHypothek()){
                    straßenHypothek.push_back(str);
                }
            }
        return straßenHypothek;
    }
    
    
    /*
    Methode zum Hausbau. Miete für Straße erhöht sich um 1/4.
    Haus nimmt Farbe des Spielers an.
    */
      void buildHouse(Straße &str){
          Haus *h = str.getHouse();
          h->setBuilt(true);
          h->getRect()->setFill(color[0],color[1],color[2]);
          bool b = true;
          str.setMiete(str.getMiete() + str.getMiete() * (1/4));
        }
    
    
    /*
    Hausbau möglich, falls noch nicht 4 Häuser gebaut wurden und genug Kapital vorhanden ist.
    */
      bool hausbauMoeglich(Straße &str){           
           return ((str.getMiete()>str.getHouse()->getPreis())&&str.getAnzahlHaeuser() < 4); 
       }
    
    
       
    //DESTRUKTOR
    ~Spieler(){
        delete c;
    }
};