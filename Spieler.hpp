#include "Straße.hpp"
#include <iostream>
using namespace std;

class Spieler{
    
    private:
    string name;
    double kapital;
    list<Straße> straßen; //sollte dass dann auch eine Pointer list sein? Glaube schon :D 
    int feldPos;
    //array <string, 4> colors = {"red", "blue", "yellow", "orange"};
    string color;
    
    //die Form auf dem Spielfeld
    Circle *c = nullptr;

    public:
    Spieler(string name){
        this -> name = name;
        kapital = 400; //Welcher Betrag??
        feldPos = 0;
    }
    
    void setName(string name){
        this->name = name; 
    }
    
    void setColor(string s){
        color = s;
    }
    
//     array <int, 3> getColor(){
//         return colors; 
//     }
        
    
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
             straßen.push_front(straße);
             straße.setVerkauft(true);
        
        //Änderung 1
        straße.getRect()->setFill(this->color);
    }   
    
    bool kaufenMoeglich(Straße &straße){
        return kapital >= straße.getMiete();
    }
    
    bool mieteZahlenMoeglich(Straße &straße){
        return (this->kapital > straße.getMiete());
    }
    
    bool besitzeStraße(Straße &str){
        for(Straße eigeneStr: straßen){
            if(eigeneStr.getName()==str.getName()){
                return true;
            }
        }
        return false;
    }
    
    //DESTRUKTOR
    ~Spieler(){
    }
};