//fucking Spielbrett
#include <algoviz/SVG.hpp>
#include "Spieler.hpp"
#include <iostream>
#include <list>

using namespace std; 

class Spielbrett {
    
    private: 
    
        int width; 
        int height;

        //Ist spielfeld. erste Dim gibt an, welches Feld. 2. Dim x und y Koordinaten
        int feld[20][2];
        //Array für Straßen. Index gibt an welches Feld es ist.
        Straße* straßen[20];
        int anzahl; 
        list<Spieler*> spieler;
        SVG *brett =nullptr; 
        int koord[20][2] ={{0,0}, {0,100},{0,200},{0,300},{0,400}, {0,500},
                               {100,500},{200,500},{300,500},{400,500},{500,500},
                               {500,400},{500,300},{500,200},{500,100},{500,0},
                               {400,0},{300,0},{200,0},{100,0}};
    
        array <string, 4> colors = {"red", "blue", "yellow", "orange"}; 

    public:
  
        Spielbrett(int anzahl, SVG *brett){
            this-> brett = brett;
            this->anzahl = anzahl;
            width = 500; 
            height = 500;
            straßenInitialisieren();
            spielerInitialisieren();
            }
    
        
    
       
        void spielerInitialisieren(){
            Spieler *spielerZeiger = nullptr;
                for(int i = 0; i <anzahl;i++){
                    string s = "Spieler_" + to_string(i);
                    spielerZeiger = new Spieler(s);
                    Circle *c2 = new Circle(10 + 15 * i,10,10,brett);
                    spielerZeiger->setColor(colors[i]);
                    c2->setFill(colors[i]);
                    spielerZeiger -> setCircle(c2);
                    spieler.push_front(spielerZeiger);
                    
                }
            }
    
     
    
        
           void straßenInitialisieren(){
            //x und Y Koordinaten 
            
           
            //Mein Spielbrett ist gerade nur 12 groß...
            string namen[20] = {"OLD KENT ROAD", "WHITECHAPEL ROAD", "KINGS CROSS STATION", 
                         "EUSTON ROAD", "PENTONVILLE ROAD", "PALL MALL", 
                         "WHITEHALL", "FLEET STREET", "LEICESTER SQUARE", 
                         "PICCADILLY ROAD", "OXFORD STREET", "BOND STREET", 
                          "BOW STREET", "VINE STREET", "THE STRAND", "MAYFAIR",
                          "ELECTRIC COMPANY", "WATER WORKS", "LIVERPOOL STREET STATION", "MARYLEBONE STATION"};
            int len = 20;
            Straße *straßenZeiger=nullptr;
            int miete = 10;
            for(int i = 0; i < 20; i++){
                //i als Argument entspricht der Feldposition
                straßenZeiger = new Straße(namen[i], miete);
                Rect *r2= new Rect(koord[i][0],koord[i][1],100,100,brett);
                r2->setFill("green");
                straßenZeiger -> setRect(r2);
                miete= miete +5;
                straßen[i] = straßenZeiger;
            }
        }
      


        void laufen(Spieler &spieler, int i){
            int altesFeld = spieler.getFeldPos();
            // i ist was gewürfelt wurde. 12 weil wir 12 Felder haben -> kann man noch in Variable speichern.
            int neuesFeld = (altesFeld + i) % 20;
            spieler.setFeldPos(neuesFeld);
            //x und y Koordinaten von neuem Feld herausfinden:
            int x = koord[neuesFeld][0];
            int y = koord[neuesFeld][1];
            Circle *c = spieler.getCircle();
            //bewegt Spieler (als Circle) zu neuen Koordinaten. Ist noch nicht so schön weil auf Linie).
            c->moveTo(x + 50 + rand()%20 + 1, y + 50 + rand()%20 + 1);
        }
        
        
        list<Spieler*> getSpielerListe(){
            return spieler;
        }
    
        Straße* getStraße(int pos){
            return straßen[pos];
        }
    
    
    int getWidth(){
            return width; 
            }
    
        int getHeight(){
            return height;
            }
          
    //DESTRUKTOR
    void deleteSpielerStraßen(){
        for(Spieler* s:spieler){
            delete (s->getCircle());
            delete s;
        }
        for(int i = 0; i < 20; i++){
            delete (straßen[i]->getRect());
            delete straßen[i];
        }
    }
    
    

};