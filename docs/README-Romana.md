# Primitive
Libraria poate desena cateva figuri geometrice simple:
* puncte
* linii
* triunghiuri
* cercuri
* dreptunghiuri

Un program foarte simplu care foloseste libraria arata cam asa:
```c++
#include "graphics.hpp"

int main()
{
    point(50, 60);
    return draw();
}
```
Programul va desena un punct la coordonata (50, 60). Se poate atribui si o culoare punctului:
```c++
int main()
{
    point(50, 60, GREEN);
    return draw();
}
```
Acum punctul va fi verde. Culorile disponibile:
* RED - rosu
* GREEN - verde
* BLUE - albastru
* WHITE - alb
* BLACK - negru
* CYAN - albastru deschis
* YELLOW - galben
* LIME - verzui
* TEAL - albastru - verzui
* PURPLE - mov
* PINK - roz
* INDIGO - indigo
* AMBER - un fel de portocaliu
* ORANGE - portocaliu
* BROWN - maro
* GREY - gri
Culoare poate fi specificata ca ultim parametru la orice primitiva.

Cel mai usor mod de a desena ceva este de a chema functille care au numele primitivelor:
```c++
line(x0, y0, x1, y1);
```
va desena o linie de la (x0, y0) la (x1, y1).
```c++
point(x, y);
```
va desena un punct la (x, y).
```c++
triangle(x0, y0, x1, y1, x2, y2);
```
va desena un triunghi la (x0, y0), (x1, y1), (x2, y2).
```c++
rectangle(x, y, w, h);
```
va desena un dreptunghi la (x, y) cu latimea = w si latimea = h.
```c++
circle(x, y, r);
```
va desena un cerc la (x, y) cu raza = r.

Tineti cont ca punctul de pornire, adica coordonata (0, 0), se afla in coltul din stanga sus al ferestrei. X (reprezentand axa orizontala) si Y (reprezentand axa verticala) cresc pornind de acolo.

Pentru a desena doar conturul unei figuri geometrice se prefixeaza functiile cu 'outline\_' in afara de line sin point. Au aceeasi parametrii ca functiile normale:
```c++
outline_rectangle(...);
outline_triangle(...);
outline_circle(...);
```

# Mai multa culoare
Se pot specifica si alte culori decat cele predefinite. De exemplu pentru linie:
```c++
line(x0, y0, x1, y1, hw::color{ r, g, b });
```
Unde r, g si b reprezinta numere intregi cuprinse intre 0 si 255: rosu, verde si albastru. De exemplu (0, 0, 0) reprezinta negru iar (255, 255, 255) este alb.

