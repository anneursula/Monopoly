//oooooookay where to start? 
//Klasse Straße inkl Attribute

#include <list>
#include <iostream>
using namespace std;

class Straße {
    private:
    
        string name;
         
        //nicht veraendlich -> konstane machen
        int miete; 
        bool verkauft; 
        bool hypothek; 
        int posX; 
        int posY;
        string color; 
    
        Rect *r = nullptr;
        
    
    public:    

       
        Straße(string name, int miete){
            this->name = name;
            this->miete = miete;
            posX = 0; 
            posY = 0; 
            verkauft = false; 
            hypothek = false; 
            color = "black";
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
    
        //DESTRUKTOR
        ~Straße(){
        }
    
};

