#include "Straße.hpp"
#include <iostream>
using namespace std;

class Spieler{
    
    private:
    string name;
    double kapital;
    //mit nem vector kann man einfacher auf elemente zugreifen (in der theorie zumindest)
    vector <Straße*> straßen; 
    int feldPos;
   // string color;
    //Color hierdring
    int color[3];
    //die Form auf dem Spielfeld
    Circle *c = nullptr;
    
    bool imprisoned;
    
    

    public:
    Spieler(string name, SVG *brett, int color[], int pos){
        this -> name = name;
        kapital = 400; //Welcher Betrag??
        feldPos = 0;
        this->c= new Circle(pos,30,10,brett);
        this->c->setFill(color[0],color[1],color[2]);
        this->color[0] = color[0];
        this->color[1] = color[1];
        this->color[2] = color[2];
        imprisoned = false;
        
    }
    
    void setName(string name){
        this->name = name; 
    }
    
//     void setColor(string s){
//         color = s;
//     }
    
    
    void setCircle(Circle *c2){
            this-> c = c2;
        }
    
    int wuerfeln(){
//         return rand()%6 + 1;
        return 5;
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
    
    void setImprisoned(bool prison){
        this->imprisoned = prison; 
    }
    
    bool getImprisoned(){
        return imprisoned; 
    }
    
    void mieteZahlen(Spieler &spieler, Straße &straße){
        if(straße.getHypothek() == false){
            if(straße.getMiete() <= kapital){
                spieler.mieteErhalten(straße.getMiete());
                kapital = kapital - straße.getMiete();
            }
        }

    }
    
    void mieteErhalten(double miete){
        this->kapital = this->kapital + miete;
    }
    
    
    void straßeKaufen(Straße &straße){
        straßen.push_back(&straße);
        straße.setVerkauft(true);
        this->kapital = this->kapital - straße.getMiete();
        
        //Änderung 1
        straße.getRect()->setFill(color[0],color[1],color[2]);
      //  straße.getRect()->setColor(this->color);
    }   
    
    bool kaufenMoeglich(Straße &straße){
         return kapital >= straße.getMiete();

    }
    
    bool mieteZahlenMoeglich(Straße &straße){
        return (this->kapital > straße.getMiete());
    }
    
    bool besitzeStraße(Straße &str){
        for(Straße *eigeneStr: straßen){
            if(eigeneStr->getName()==str.getName()){
                return true;
            }
        }
        return false;
    }
    
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
    
    
    vector <Straße*> getStreetsHypothek(){
        
        vector <Straße*> straßenHypothek;
        
        for(Straße *str: straßen){
                if(str->getHypothek()){
                    straßenHypothek.push_back(str);
                }
            }
        return straßenHypothek;
    }
    
    
        void buildHouse(Straße &str){
            str.getHouse()->setBuilt(true);
            //muss noch geändert werden
            str.getHouse()->getRect()->setFill(color[0],color[1],color[2]);
            bool b = true;
            str.setMiete(str.getMiete() + str.getMiete() * (1/4));
        }
    
        bool hausbauMoeglich(Straße &str){
           
           return ((str.getMiete()>str.getHouse()->getPreis())&&str.getAnzahlHaeuser() < 4); 
        }
    
    
        
        
    
    //DESTRUKTOR
    ~Spieler(){
        delete c;
    }
};