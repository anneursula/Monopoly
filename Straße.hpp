//oooooookay where to start? 
//Klasse Straße inkl Attribute

#include <list>
#include <iostream>
using namespace std;

class Straße {
    private:
    
        string Name;
         
        //nicht veraendlich -> konstane machen
        int Miete; 
        bool verkauft; 
        bool Hypothek; 
        int posX; 
        int posY;
        string color; 
    
        Rect *r = nullptr;
        
    
    public:    
    
//         Straße(){
//             Name = ""; 
//             Miete = 0; 
//             posX = 0; 
//             posY = 0; 
//             verkauft = false; 
//             Hypothek = false; 
//             color = "black";

//         }   
       
        Straße(string name, int miete){
            this->Name = name;
            this->Miete = miete;
            posX = 0; 
            posY = 0; 
            verkauft = false; 
            Hypothek = false; 
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
            this->Name = name;
        }

        string getName() {
            return Name;
        }

        void setMiete(int miete){
            this->Miete = miete;
        }

        int getMiete(){
            return Miete;
        }

        void setVerkauft(bool verkauft){
            this->verkauft = verkauft; 
        }

        bool getVerkauft(){
            return verkauft;
        }

        void setHypothek(bool hypothek){
            this->Hypothek = hypothek;
        }

        bool getHypothek(){
            return Hypothek;
        }
    
};

