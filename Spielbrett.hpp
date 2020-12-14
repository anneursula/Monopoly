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
    
        /*
        //Brauchen wir den Konstruktor überhaupt? Wir wollen doch immer mit Anzahl konstruieren
        Spielbrett(){
            
            //bin mir hier nicht sicher, ob ein SVG zu viel erstellt wird. Vielleicht irgendwie mit Referenzen arbeiten.
            brett = SVG(1000,1000);
            anzahl = 0; 
            width = 500; 
            height = 500;
            this-> straßen = straßen;
            this->spieler = spieler;
            
            buildBrett();
            setzeSpieler();
            }*/

        Spielbrett(int anzahl, SVG *brett){
            this-> brett = brett;
            this->anzahl = anzahl;
            width = 500; 
            height = 500;
            feldArrayInitialisieren();
            buildBrett();
            spielerInitialisieren();
            straßenInitialisieren();
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
                    Circle *c2 = new Circle(10 + 10 * i,10,5,brett);
                    spielerZeiger -> setCircle(c2);
                    spieler.push_front(spielerZeiger);
                    
                }
            }
    
        void straßenInitialisieren(){
            //Mein Spielbrett ist gerade nur 12 groß...
            string namen[12] = {"OLD KENT ROAD", "WHITECHAPEL ROAD", "KINGS CROSS STATION", 
                         "EUSTON ROAD", "PENTONVILLE ROAD", "PALL MALL", 
                         "WHITEHALL", "FLEET STREET", "LEICESTER SQUARE", 
                         "PICADILLY ROAD", "OXFORD STREET", "BOND STREET"};
            int len = 12;
            Straße *zeiger=nullptr;
            int miete = 10;
            for(int i = 0; i < 12; i++){
                //i als Argument entspricht der Feldposition
                zeiger = new Straße(namen[i], miete);
                miete= miete +5;
                straßen[i] = zeiger;
            }
        }
      
        //hier drin die Positionen der Straßen und Spieler setzen!
        void buildBrett(){   
            for(int i= 0; i < 12; i++){
                brett->drawRect(feld[i][0], feld[i][1], 100,100);
            }
        }
    
        // Methode besser in Klasse Spieler
        int wuerfeln(){
          return ((rand() % 6) + 1);  
        }

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
            c->moveTo(x+50,y+50);
        }
        
        
        list<Spieler*> getSpielerListe(){
            return spieler;
        }
    
        Straße* getStraße(int pos){
            return straßen[pos];
        }
    
          
};