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
        int feld[12][2];
        //Array für Straßen. Index gibt an welches Feld es ist.
        Straße* straßen[12];
        int anzahl; 
        list<Spieler*> spieler;
        SVG *brett =nullptr; 

    public:
  
        Spielbrett(int anzahl, SVG *brett){
            this-> brett = brett;
            this->anzahl = anzahl;
            width = 500; 
            height = 500;
            feldArrayInitialisieren();
           // buildBrett();
            straßenInitialisieren();
            spielerInitialisieren();
            }
    
        int getWidth(){
            return width; 
            }
    
        int getHeight(){
            return height;
            }

    
        void feldArrayInitialisieren(){
            //SWITCH CASE EINBAUEN?
            
            //das feld 2D Array durchlaufen und in erste Koordinate x Koordinate des Felds Nummer = Index
            // in zweiter Koordinate y Koordinate des Felds Nummer = Index.
            int x = 1;
            int k = 2;
            int m = 2;
            for(int i = 0; i < 12; i++){
                            if(i<4){
                                //x bleibt gleich y wird konstant höher
                                feld[i][0] = 0;
                                feld[i][1] = i* 100;
                            }

                            else if(i<7){

                                //y bleibt gleich, x wird konstant höher
                                feld[i][1]= 300;
                                feld[i][0] = x*100;
                                x++;
                            }
                            else if(i<10){
                                //x bleibt gleich, y konstant kleiner
                                feld[i][0] = 300;
                                feld[i][1] = k*100;
                                k--;
                            }else{
                                //y bleibt gleich, x konstant niedriger
                                feld[i][1] = 0;
                                feld[i][0] = m*100;
                                m--;
                            }
                        }
        }
    
        void spielerInitialisieren(){
            Spieler *spielerZeiger = nullptr;
                for(int i = 0; i <anzahl;i++){
                    string s = "Spieler_" + to_string(i);
                    spielerZeiger = new Spieler(s);
                    Circle *c2 = new Circle(10 + 15 * i,10,10,brett);
                    spielerZeiger->setColor();
                    c2->setFill(spielerZeiger->getColor()[0], spielerZeiger->getColor()[1],spielerZeiger->getColor()[2]);
                    spielerZeiger -> setCircle(c2);
                    spieler.push_front(spielerZeiger);
                    
                }
            }
    
        void straßenInitialisieren(){
            //x und Y Koordinaten 
            int koord[12][2] ={{0,0}, {0,100},{0,200},{0,300},{100,300},{200,300},{300,300},{300,200},{300,100},{300,0},{200,0},{100,0}};
           
            //Mein Spielbrett ist gerade nur 12 groß...
            string namen[12] = {"OLD KENT ROAD", "WHITECHAPEL ROAD", "KINGS CROSS STATION", 
                         "EUSTON ROAD", "PENTONVILLE ROAD", "PALL MALL", 
                         "WHITEHALL", "FLEET STREET", "LEICESTER SQUARE", 
                         "PICADILLY ROAD", "OXFORD STREET", "BOND STREET"};
            int len = 12;
            Straße *straßenZeiger=nullptr;
            int miete = 10;
            for(int i = 0; i < 12; i++){
                //i als Argument entspricht der Feldposition
                straßenZeiger = new Straße(namen[i], miete);
                Rect *r2= new Rect(koord[i][0],koord[i][1],100,100,brett);
                r2->setFill("green");
                straßenZeiger -> setRect(r2);
                miete= miete +5;
                straßen[i] = straßenZeiger;
            }
        }
      
        //hier drin die Positionen der Straßen und Spieler setzen!
    //Brauchen wir nicht mehr wegen den Rects :)
//         void buildBrett(){   
//             for(int i= 0; i < 12; i++){
//                 brett->drawRect(feld[i][0], feld[i][1], 100,100);
//             }
//         }
    
  

        void laufen(Spieler &spieler, int i){
            int altesFeld = spieler.getFeldPos();
            // i ist was gewürfelt wurde. 12 weil wir 12 Felder haben -> kann man noch in Variable speichern.
            int neuesFeld = (altesFeld + i) % 12;
            spieler.setFeldPos(neuesFeld);
            //x und y Koordinaten von neuem Feld herausfinden:
            int x = feld[neuesFeld][0];
            int y = feld[neuesFeld][1];
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
    
          
};