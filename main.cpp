
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <graphics.h>
#include "graficar.h"

using std::vector;
using namespace std;

struct Pueblo{
	int id;
	char nombre;
	int xCoord;
	int yCoord;
	int hombres;
	int mujeres;
	int poblacion;
	float perCapita;
	int elevacion;
};
Pueblo pueblos[10] = {
	1,'A',12,15,22,12,0,2000,50,
	2,'B',18,64,24,14,0,1800,100,
	3,'C',52,45,26,16,0,1600,150,
	4,'D',13,12,28,22,0,1400,200,
	5,'E',28,60,30,24,0,1300,250,
	6,'F',62,80,32,26,0,2200,400,
	7,'G',19,56,10,28,0,2400,500,
	8,'H',49,55,12,30,0,1500,600,
	9,'I',23,12,14,32,0,1600,400,
	10,'J',30,5,15,16,0,1000,1000
	};

struct Poblado{
	int poblacion;
	char nombre;
};
struct Ciudad{
	char nombre;
	int altura;
};

//se declara el arreglo de la estructura pueblo para poder trabajar con ello


//se declaran las variables globales
vector<int> vectID;
int distancia, distancia1;
int suma;
vector<int> grupoA;
vector<int> grupoH;
Poblado poblado1, poblado2;
Ciudad alta, baja;

void mostrarColumnas();
void calcularPoblacion(Pueblo pueblo);
void mostrarTabla(Pueblo pueblo);
Pueblo encontrarCiudad(char nombre);
Pueblo encontrarCiudad(int id);
float calcularCiudadesDistantes(Pueblo pueblo, Pueblo pueblo1);
int sumarCantidadVarones(Pueblo pueblo);
void agruparDistantes30km(Pueblo, Pueblo);
void almacenarIdDistantes50(Pueblo);
int sumarPoblacion(Pueblo);
void ejercicio11(Pueblo, Pueblo);
float promPerCapita(vector<int> );
Poblado hallarDosCiudadesMasPobladas();
Ciudad hallarCiudadMasBajaYMasAlta();


//int sumar_poblacion (Pueblo pueblo1, Pueblo pueblo);



int main(){

	int opcion;
	char ciudad, ciudad1;
	mostrarColumnas();
	//para mostrar la tabla con los datos
	for(int i = 0; i < 10; i++){
		calcularPoblacion(pueblos[i]);
	}
	system("pause");
	while(opcion != 15){
		system("cls");
		suma = 0;
		cout<<"\tMENU DE OPCIONES: "<<endl;
		cout<<"1. Arreglo de ciudades que disten 30 km"<<endl;
		cout<<"2. Arreglo de ID's de ciudades que disten en 50km y cuya altura sea menor a 800"<<endl;
		cout<<"3. Sumar la poblacion de varones cuyas ciudades disten en 50km y cuya altura sea menor a 800"<<endl;
		cout<<"4. Calcular la suma de la poblaciondne ciudades que disten en 50km y cuto ingreo sea mayor a 1500"<<endl;
		cout<<"5. Se agrupan a las ciudades de acuerdo a las distancia que tengan a la ciudad A y la ciudad H"<<endl;
		cout<<"6. Dos grupos de acuerdo a las ciudades mas pobladas"<<endl;
		cout<<"7. Dos grupos de acuerdo seleccionando las ciudades que tengan mayor y menor altura"<<endl;
		cout<<"8. Grafique todas las ciudades en un eje coordenado, utilizando escalas e incluir nombres"<<endl;
		cout<<"9. Graficar la agrupación de ciudades de acuerdo a la altura"<<endl;
		cout<<"15. Salir"<<endl;
		cin>>opcion;
		system("cls");
		switch(opcion){
			case 1:
				cout<<"Ingrese el nombre de la ciudad"<<endl;
				cin>>ciudad;
				ciudad = toupper(ciudad);
				for(int i = 0; i < 10; i++){
					agruparDistantes30km(encontrarCiudad(ciudad), pueblos[i]);
				}
				cout<<"La informacion de las ciudades que distan en 30km respecto a la ciudad "<<ciudad<<" es:"<<endl;
				mostrarColumnas();
				for(int j = 0; j < vectID.size(); j++){
					mostrarTabla(encontrarCiudad(vectID[j]));
				}
				system("pause");
				vectID.clear();
				break;
			case 2:
				cout<<"Ingrese el nombre de la ciudad"<<endl;
				cin>>ciudad;
				ciudad = toupper(ciudad);
				almacenarIdDistantes50(encontrarCiudad(ciudad));
				mostrarColumnas();
				for(int i = 0; i < vectID.size(); i++){
					mostrarTabla(encontrarCiudad(vectID[i]));
				}
				system("pause");
				vectID.clear();
				break;
			case 3:
				cout<<"Ingrese el nombre de la ciudad"<<endl;
				cin>>ciudad;
				ciudad = toupper(ciudad);
				cout<<"La suma de varones las cuales distan a mas de 50 respecto a la ciudad "<<ciudad<<" su altura es menor de 800 msnm"<<endl;
				cout<<sumarCantidadVarones(encontrarCiudad(ciudad))<<endl;
				cout<<"La informacion que de las ciudades son "<<endl;
				for(int i = 0; i < vectID.size(); i++){
					mostrarTabla(encontrarCiudad(vectID[i]));
				}
				vectID.clear();
				system("pause");
				break;
			case 4:
				cout<<"Ingrese el nombre de la ciudad"<<endl;
				cin>>ciudad;
				ciudad = toupper(ciudad);
				for(int i = 0; i < 10; i++){
					if(calcularCiudadesDistantes(encontrarCiudad(ciudad), pueblos[i]) == 50 && pueblos[i].perCapita > 1500){
						sumarPoblacion(pueblos[i]);
					}
				}
				cout<<"La suma de la poblacion que distan en 50km y cuyos ingros son mayores a 1500 es de "<<endl<<suma<<endl;
				system("pause");
				break;
			case 5:

				cout<<"se agrupan las ciudades de acuerdo a la distancia que estas tienen respecto a A y H "<<endl;

				ejercicio11(pueblos[0], pueblos[9]);
				cout<<"El grupo de ciudades mas cercanas a la ciudad A son :"<<endl;
				mostrarColumnas();
				for(int i = 0; i <grupoA.size(); i++){
					mostrarTabla(encontrarCiudad(grupoA[i]));
				}
				cout<<"La suma de la cantidad de las poblaciones para el grupo A es: "<<endl;
				for(int j = 0; j < grupoA.size(); j++){
					sumarPoblacion(encontrarCiudad(grupoA[j]));
				}
				cout<<suma;
				cout<<endl<<"El grupo de ciudades mas cercanas a la ciudad H son :"<<endl;
				mostrarColumnas();
				for(int i = 0; i <grupoH.size(); i++){
					mostrarTabla(encontrarCiudad(grupoH[i]));
				}
				cout<<"La suma de la cantidad de las poblaciones para el grupo H es: "<<endl;
				suma = 0;
				for(int j = 0; j < grupoA.size(); j++){
					sumarPoblacion(encontrarCiudad(grupoH[j]));
				}
				cout<<suma<<endl;
				system("pause");
				break;
			case 6:
				hallarDosCiudadesMasPobladas();
				ejercicio11(encontrarCiudad(poblado1.nombre), encontrarCiudad(poblado2.nombre));
				cout<<"El grupo de ciudades mas cercanas al pueblo "<<poblado1.nombre<<" son:"<<endl;
				mostrarColumnas();
				for(int i = 0; i <grupoA.size(); i++){
					mostrarTabla(encontrarCiudad(grupoA[i]));
				}
				cout<<endl<<"El grupo de ciudades mas cercanas al pueblo "<<poblado2.nombre<<" son :"<<endl;
				mostrarColumnas();
				for(int i = 0; i <grupoH.size(); i++){
					mostrarTabla(encontrarCiudad(grupoH[i]));
				}
				grupoA.clear();
				grupoH.clear();
				system("pause");
				break;
			case 7:
				hallarCiudadMasBajaYMasAlta();
				ejercicio11(encontrarCiudad(baja.nombre), encontrarCiudad(alta.nombre));
				cout<<"El pueblo que tiene la menor elevacion es: "<<baja.nombre<<", y los pueblos que estan mas cerca son:"<<endl;
				mostrarColumnas();
				for(int i = 0; i <grupoA.size(); i++){
					mostrarTabla(encontrarCiudad(grupoA[i]));
				}
				cout<<endl<<"El pueblo que tiene la elevacion mayor es: "<<alta.nombre<<" y los pueblos que estan mas cerca son: "<<endl;
				mostrarColumnas();
				for(int i = 0; i <grupoH.size(); i++){
					mostrarTabla(encontrarCiudad(grupoH[i]));
				}
				grupoA.clear();
				grupoH.clear();
				system("pause");
				break;
            case 8:
                initwindow(1910,1000);

                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                marco();
                int x,y;

                for(int j = 0; j < 10; j++){
                    x = 210;
                    y = 860;
                    for(int i = 0; i < pueblos[j].xCoord; i++){
                        x += 10;
                    }
                    for(int i = 0; i < pueblos[j].yCoord; i++){
                        y -= 10;
                    }
                    line( x- 3, y-3, x+3, y+3);
                    line( x+ 3, y-3, x-3, y+3);

                    switch(pueblos[j].id){
                        case 1:
                            outtextxy(x+10,y-5, "A");
                            break;
                        case 2:
                            outtextxy(x+10,y-5, "B");
                            break;
                        case 3:
                            outtextxy(x+10,y-5, "C");
                            break;
                        case 4:
                            outtextxy(x+10,y-5, "D");
                            break;
                        case 5:
                            outtextxy(x+10,y-5, "E");
                            break;
                        case 6:
                            outtextxy(x+10,y-5, "F");
                            break;
                        case 7:
                            outtextxy(x+10,y-5, "G");
                            break;
                        case 8:
                            outtextxy(x+10,y-5, "H");
                            break;
                        case 9:
                            outtextxy(x+10,y-5, "I");
                            break;
                        case 10:
                            outtextxy(x+10,y-5, "J");
                            break;
                    }
                }
                eje();
                system("pause");
                closegraph();
                break;
            case 9:
                Pueblo variable, taller, smaller;
                hallarCiudadMasBajaYMasAlta();
				ejercicio11(encontrarCiudad(baja.nombre), encontrarCiudad(alta.nombre));
                initwindow(1910,1000);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                marco();
                taller = encontrarCiudad(alta.nombre);
                smaller = encontrarCiudad(baja.nombre);
                grupoA.push_back(smaller.id);
                grupoH.push_back(taller.id);
                for(int i = 0; i < grupoA.size(); i ++){
                    setcolor(RED);
                    x = 210;
                    y = 860;
                    variable = encontrarCiudad(grupoA[i]);
                    for(int i = 0; i < variable.xCoord; i++){
                        x += 10;
                    }
                    for(int i = 0; i < variable.yCoord; i++){
                        y -= 10;
                    }
                    line( x- 3, y-3, x+3, y+3);
                    line( x+ 3, y-3, x-3, y+3);

                    switch(variable.id){
                        case 1:
                            outtextxy(x+10,y-5, "A");
                            break;
                        case 2:
                            outtextxy(x+10,y-5, "B");
                            break;
                        case 3:
                            outtextxy(x+10,y-5, "C");
                            break;
                        case 4:
                            outtextxy(x+10,y-5, "D");
                            break;
                        case 5:
                            outtextxy(x+10,y-5, "E");
                            break;
                        case 6:
                            outtextxy(x+10,y-5, "F");
                            break;
                        case 7:
                            outtextxy(x+10,y-5, "G");
                            break;
                        case 8:
                            outtextxy(x+10,y-5, "H");
                            break;
                        case 9:
                            outtextxy(x+10,y-5, "I");
                            break;
                        case 10:
                            outtextxy(x+10,y-5, "J");
                            break;
                    }
                }

                for(int i = 0; i < grupoH.size(); i ++){
                    setcolor(BLUE);
                    x = 210;
                    y = 860;
                    variable = encontrarCiudad(grupoH[i]);
                    for(int i = 0; i < variable.xCoord; i++){
                        x += 10;
                    }
                    for(int i = 0; i < variable.yCoord; i++){
                        y -= 10;
                    }
                    line( x- 3, y-3, x+3, y+3);
                    line( x+ 3, y-3, x-3, y+3);

                    switch(variable.id){
                        case 1:
                            outtextxy(x+10,y-5, "A");
                            break;
                        case 2:
                            outtextxy(x+10,y-5, "B");
                            break;
                        case 3:
                            outtextxy(x+10,y-5, "C");
                            break;
                        case 4:
                            outtextxy(x+10,y-5, "D");
                            break;
                        case 5:
                            outtextxy(x+10,y-5, "E");
                            break;
                        case 6:
                            outtextxy(x+10,y-5, "F");
                            break;
                        case 7:
                            outtextxy(x+10,y-5, "G");
                            break;
                        case 8:
                            outtextxy(x+10,y-5, "H");
                            break;
                        case 9:
                            outtextxy(x+10,y-5, "I");
                            break;
                        case 10:
                            outtextxy(x+10,y-5, "J");
                            break;
                    }
                }

                eje();
                for(int i = 0; i < 10; i++){

                }
                break;
		}

	}

	return 0;
}
void mostrarColumnas(){
	cout<<"========================================================================="<<endl;
	cout<<"|"<<"ID"<<" "
	<<"|"<<"NOMBRE"<<" "
	<<"|"<<"COORD X"<<" "
	<<"|"<<"COORD Y"<<" "
	<<"|"<<"HOMBRES"<<""
	<<"|"<<"MUJERES"<<""
	<<"|"<<"POBLACION"<<""
	<<"|"<<"PER CAPITA"<<""
	<<"|"<<"ELEVACION"<<""
	<<endl;
}

float calcularCiudadesDistantes(Pueblo pueblo, Pueblo pueblo1){
	distancia = ((pueblo.xCoord-pueblo1.xCoord)*(pueblo.xCoord-pueblo1.xCoord) + (pueblo.yCoord-pueblo1.yCoord)*(pueblo.yCoord-pueblo1.yCoord));
	distancia = sqrt(distancia);
	return distancia;
}

//Ejercicio 1-3
void agruparDistantes30km(Pueblo pueblo1, Pueblo pueblo2){
	if(calcularCiudadesDistantes(pueblo1, pueblo2)==30 && (pueblo1.nombre != pueblo2.nombre)){
		vectID.push_back(pueblo2.id);
	}
}

/*
Desarrollar una función que en un arreglo almacene los identificadores todas las ciudades que disten en 50 km de una ciudad ingresada siempre y
cuando su altura sea menor a 800msnm, luego con ellos muestre los datos del resto de la población
*/

void almacenarIdDistantes50(Pueblo pueblo){
	for(int i = 0; i < 10; i++){
		if(((calcularCiudadesDistantes(pueblo, pueblos[i])) == 50) && (pueblos[i].elevacion < 800) && pueblo.nombre != pueblos[i].nombre){
			vectID.push_back(pueblos[i].id);
		}
	}
}
/*
Desarrollar una función que sume cual es la población total de todas las ciudades que disten en 50 km de una ciudad ingresada siempre y cuando
su ingreso sea mayor a 1500, luego con ellos muestre los datos del resto de la población
*/

void calcularPoblacion(Pueblo pueblo){
	pueblo.poblacion = pueblo.hombres + pueblo.mujeres;
	mostrarTabla(pueblo);
}
Pueblo encontrarCiudad(char nombre){
	for(int i = 0; i < 10; i++){
		if(nombre==pueblos[i].nombre){
			return pueblos[i];
			i=10;
		}
	}
}
Pueblo encontrarCiudad(int id){
	for(int i = 0; i < 10; i++){
		if(id==pueblos[i].id){
			return pueblos[i];
			i=10;
		}
	}
}

void mostrarTabla(Pueblo pueblo){
	cout<<endl<<"========================================================================="<<endl;
	cout<<"|"<<pueblo.id<<"\t"
	<<"|"<<pueblo.nombre<<"\t"
	<<"|"<<pueblo.xCoord<<"\t"
	<<"|"<<pueblo.yCoord<<"\t"
	<<"|"<<pueblo.hombres<<"\t"
	<<"|"<<pueblo.mujeres<<"\t"
	<<"|"<<pueblo.poblacion<<"\t"
	<<"|"<<pueblo.perCapita<<"\t"
	<<"|"<<pueblo.elevacion<<"\t"
	<<"|"<<endl;
}

//para sumar la poblacion
int sumarPoblacion(Pueblo pueblo1){
	suma = suma + pueblo1.hombres + pueblo1.mujeres;
}

//para sumar la cantidad de varones
int sumarCantidadVarones(Pueblo pueblo){
	suma = pueblo.hombres;
	for(int i = 0; i < 10; i++){
		if(((calcularCiudadesDistantes(pueblos[i], pueblo)) == 50) && (pueblos[i].elevacion < 800)){
			//mostrarTabla(pueblos[i]);
			suma += pueblos[i].hombres;
			vectID.push_back(pueblos[i].id);
		}
	}
	return suma;
}

/*
Dadas las ciudades A y H formas dos grupos de poblaciones según la cercanía de las ciudades a estas poblaciones.
Calcular la distancia a ambas ciudades y ubicarla en el grupo según este mas cerca a alguna de las 2 ciudades. Sume cuanto es la población de estos pueblos
*/
void ejercicio11(Pueblo pueblo1, Pueblo pueblo2){
	for(int i = 1; i < 9; i++){
		//calcular la cistancia:
		/*distancia = calcularCiudadesDistantes(pueblo1, pueblos[i]);
		cout<<"La distancia de la ciudad "<<pueblo1.nombre<<" a la ciudad "<<pueblos[i].nombre<<" es: "<<distancia<<endl;
		distancia1 = calcularCiudadesDistantes(pueblo2, conjunto[i]);
		cout<<"La distancia de la ciudad "<<pueblo2.nombre<<" a la ciudad "<<pueblos[i].nombre<<" es: "<<distancia1<<endl;
		*/
		if((calcularCiudadesDistantes(pueblo1, pueblos[i]))<(calcularCiudadesDistantes(pueblo2, pueblos[i]))){
			grupoA.push_back(pueblos[i].id);
		}
		else{
			grupoH.push_back(pueblos[i].id);
		}
	}
	cout<<endl;
}
/*
Dadas dos ciudades ingresadas formar dos grupos de poblaciones según la cercanía de las ciudades a estas poblaciones.
Calcular la distancia a ambas ciudades y ubicarla en el grupo según este más cerca a alguna de las 2 ciudades. Calcule el promedio precipita de cada grupo
*/

void ejercicio13(Pueblo pueblo1, Pueblo pueblo2){
	for(int i = 0; i < 10; i++){
		//calcular la cistancia:
		/*distancia = calcularCiudadesDistantes(pueblo1, pueblos[i]);
		cout<<"La distancia de la ciudad "<<pueblo1.nombre<<" a la ciudad "<<pueblos[i].nombre<<" es: "<<distancia<<endl;
		distancia1 = calcularCiudadesDistantes(pueblo2, pueblos[i]);
		cout<<"La distancia de la ciudad "<<pueblo2.nombre<<" a la ciudad "<<pueblos[i].nombre<<" es: "<<distancia1<<endl;
		*/
		if((calcularCiudadesDistantes(pueblo1, pueblos[i]))<(calcularCiudadesDistantes(pueblo2, pueblos[i])) && pueblo1.nombre != pueblos[i].nombre){
			grupoA.push_back(pueblos[i].id);
		}
		else{
			grupoH.push_back(pueblos[i].id);
		}
	}
	cout<<endl;
}

//Halle las dos ciudades más pobladas, luego agrupe en 2 grupos con las ciudades más cercanas a estas 2 ciudades más pobladas.

Poblado hallarDosCiudadesMasPobladas(){
	poblado1.poblacion = 0;
	poblado2.poblacion = 0;
	for(int i = 0; i < 10; i++){
		suma = pueblos[i].hombres +pueblos[i].mujeres;
		if((suma > poblado2.poblacion) && (poblado2.poblacion < poblado1.poblacion)){
	 		poblado2.poblacion = suma;
	 		poblado2.nombre = pueblos[i].nombre;
		}
		else if(suma > poblado1.poblacion){
		 	poblado1.poblacion = suma;
		 	poblado1.nombre = pueblos[i].nombre;
		}
	}
	return poblado1, poblado2;
}

Ciudad hallarCiudadMasBajaYMasAlta(){
	alta.altura = 0;
	baja.altura = 10000;
	for(int i = 0; i < 10; i++){
		if(alta.altura < pueblos[i].elevacion){
			alta.altura = pueblos[i].elevacion;
			alta.nombre = pueblos[i].nombre;
		}
		if( baja.altura > pueblos[i].elevacion){
			baja.altura = pueblos[i].elevacion;
			baja.nombre = pueblos[i].nombre;
		}

	}
	return alta,baja;
}

