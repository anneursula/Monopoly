#include <iostream>
using namespace std;

class Haus{
    
    private:

    Rect *r = nullptr;
    bool built;
    int preis;
    
    
    public:
    Haus(int preis){
      built = false;  
      this->preis= preis;
    }
    
    void setRect(Rect *r2){
            this -> r = r2;
        }
    
    Rect* getRect(){
            return r;
        }
    
    bool getBuilt(){
        return built;
    }
    
    void setBuilt(bool b){
       built =b; 
    }
    
    int getPreis(){
        return this->preis;
    }
    
    ~Haus(){
    }
    
};