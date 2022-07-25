
#include <graphics.h>
#include <string>

using std::string;



void marco(){
    setcolor(WHITE);
    rectangle(10, 10, 1900, 990);
}

void eje(){
    setcolor(DARKGRAY);
    line(10, 860, 1900,860);
    line(210, 10, 210, 990);
    //
    string value;
    int x = 75;
    int y = -20;
    char* valor;

    for(int i = 10; i < 990; i += 50){
        setcolor(DARKGRAY);
        line(206, i, 214, i);

    }

    for(int i = 10; i < 1900; i += 50){
        setcolor(DARKGRAY);
        line(i, 856, i, 864);
    }
}
