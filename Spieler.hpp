// #include <algoviz/SVG.hpp> brauche ich glaub nicht.
#include "Straße.hpp"
//#include "Spielbrett.hpp"
#include <iostream>
using namespace std;

class Spieler{
    
    private:
    string name;
    double kapital;
    list<Straße> straßen; //sollte dass dann auch eine Pointer list sein? Glaube schon :D 
    int feldPos;
    
    //die Form auf dem Spielfeld
    Circle *c = nullptr;

    public:
    Spieler(string name){
        this -> name = name;
        kapital = 400; //Welcher Betrag??
        feldPos = 0;
    }
    
    void setCircle(Circle *c2){
            this-> c = c2;
        }
    
    int wuerfeln(){
        return rand()%6 + 1; 
    }
    
   
    double getKapital(){
        return kapital;
    }
    
    string getName(){
        return name;
    }
    
    
    //returne pointer auf Circle
    Circle* getCircle(){
        return c;
    }
    
    int getFeldPos(){
        return feldPos;
    }
    
    void setFeldPos(int pos){
        this->feldPos = pos;
    }
    
    void mieteZahlen(Spieler &spieler, double miete){
        if(miete <= kapital){
            spieler.mieteErhalten(miete);
            kapital = kapital - miete;
        }
    }
    
    void mieteErhalten(double miete){
        kapital = kapital + miete;
    }
    
    
    void straßeKaufen(Straße &straße){
        //in main checken, ob Straße vergeben ist
             straßen.push_front(straße);
             straße.setVerkauft(true);
    }   
    
    bool kaufenMoeglich(Straße &straße){
        return kapital >= straße.getMiete();
    }
    
    bool mieteZahlenMoeglich(Straße &straße){
        return false;
    }
    
    bool besitzeStraße(Straße &str){
        for(Straße eigeneStr: straßen){
            if(eigeneStr.getName()==str.getName()){
                return true;
            }
        }
        return false;
    }
};