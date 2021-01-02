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
        //Liste mit allen Spielern
        list<Spieler*> spieler;
        SVG *brett =nullptr;
        //Koordinaten der 20 Straßen
        int koord[20][2] ={{0,0}, {0,100},{0,200},{0,300},{0,400}, {0,500},
                               {100,500},{200,500},{300,500},{400,500},{500,500},
                               {500,400},{500,300},{500,200},{500,100},{500,0},
                               {400,0},{300,0},{200,0},{100,0}};
    
        string namen[20] = {"LOS", "WHITECHAPEL ROAD", "KINGS CROSS STATION", 
                         "EUSTON ROAD", "PENTONVILLE ROAD", "PALL MALL", 
                         "WHITEHALL", "FLEET STREET", "LEICESTER SQUARE", 
                         "OXFORD STREET", "PRISON", "BOND STREET", 
                          "BOW STREET", "VINE STREET", "THE STRAND", "MAYFAIR",
                          "ELECTRIC COMPANY", "WATER WORKS", "LIVERPOOL STREET", "MARYLEBONE STATION"};
     
        int colors[4][3] = {{153,0,0}, {0,0,153},{255,255,0},{255,153,0}};

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
                    spielerZeiger = new Spieler(s,brett,colors[i],10 + 15 * i);
                    spieler.push_front(spielerZeiger);
                    
                }
            }
    

         void straßenInitialisieren(){
            int len = 20;
            Straße *straßenZeiger=nullptr;
            int miete = 10;
             //i entspricht der Feldposition
            for(int i = 1; i < 20; i++){
                straßenZeiger = new Straße(namen[i], miete, koord[i][0],koord[i][1],brett);
                miete= miete +5;
                straßen[i] = straßenZeiger;
               
             //LOS Feld
            straßenZeiger = new Straße(namen[0], 0, koord[0][0],koord[0][1],brett);
            straßenZeiger->getRect()->setFill("purple"); 
            straßen[0] = straßenZeiger; 
               
            //GEFAENGNIS Feld 
            straßenZeiger = new Straße(namen[10], 0,koord[10][0],koord[10][1],brett);
            straßenZeiger->getRect()->setFill("darkblue"); 
            straßen[10] = straßenZeiger; 
               
             //Straßennamen auf das Feld zeichnen 
            for(int i = 0; i<20; i++){
                brett->drawText(namen[i], koord[i][0]+5, koord[i][1]+50, 8); 
            }
           }
        }
    


        void laufen(Spieler &spieler, int i){
            int altesFeld = spieler.getFeldPos();
            // i ist was gewürfelt wurde. 12 weil wir 12 Felder haben 
            int neuesFeld = (altesFeld + i) % 20;
            spieler.setFeldPos(neuesFeld);
            //x und y Koordinaten von neuem Feld herausfinden:
            int x = koord[neuesFeld][0];
            int y = koord[neuesFeld][1];
            Circle *c = spieler.getCircle();
            //bewegt Spieler (als Circle) zu neuen Koordinaten.
            c->moveTo(x + 50 + rand()%20 + 1, y + 50 + rand()%20 + 1);

            // checken, ob man über LOS gegangen ist 
            if(altesFeld+i>20){
                spieler.mieteErhalten(100); 
            }
            
            // checken ob man im Gefängnis ist 
            if(neuesFeld==10){
                spieler.setImprisoned(true); 
            }
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
            delete s;
        }
        for(int i = 0; i < 20; i++){
            delete straßen[i];
        }
    }
    
    

};