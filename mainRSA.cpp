#include <iostream> 
#include <windows.h> // Agregado para cambiar el color.
#include <cmath> // Funciones matematicas.
#include <string> // Encriptar palabras.

/*
 * Programar un encriptador de palabras mediante el metodo RSA,
 * o dos metodos de unsigned long long simples (en caso de no querer usar RSA);
 * donde dado un programa se muestre el mismo encriptado, con la opcion
 * de recuperar el mensaje original
 * */

using namespace std; 
using std::string; 

//Esta variable se utiliza para poder asignarle un valor numerico a cada caracter
string alfabeto( "&&ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 0123456789" ); 

//Cambiar el color de las letras
void color( int X ){ 
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X); 
	/* 
		0 = Negro 
		1 = Azul 
		2 = Verde 
		3 = Aguamarina 
		4 = Rojo 
		5 = Purpura 
		6 = Amarillo 
		7 = Blanco 
		8 = Gris 
		9 = Azul claro 
	*/
}

//Se hace uso del algoritmo de Euclides para averiguar el MCD de dos numeros. Este metodo fue creado por el matematico griego Euclides.
//https://es.wikipedia.org/wiki/Algoritmo_de_Euclides
long mcdEuclides( long n1, long n2 ){
	long maximo, minimo, resto;
	
	if( n1 >= n2 ){
		maximo = n1;
		minimo = n2;
	}else{
		maximo = n2;
		minimo = n1;
	}
	
	while( minimo != 0 ){
		resto = ( maximo % minimo );
		maximo = minimo;
		minimo = resto;
	}
	
	return maximo;
}

//Retorna true si el numero que le pasamos es par.
bool esPar( long numero ){
	if( ( numero % 2 ) == 0 ){
		return true;
	}else{
		return false;
	}
}

//Por tentativa http://es.wikihow.com/saber-si-un-n%C3%BAmero-es-primo
bool esPrimo( long n1 ){
	//TODOS los numeros pares a excepcion del dos son compuestos.
	if( esPar( n1 ) && n1 != 2 ){
		return false;
	}else{
		/*
		 * ceil "redondea" hacia arriba.
		 * sqrt retorna la raiz cuadrada.
		 * Se divide hasta la raiz cuadrada del numero ya que dividir por los numeros siguientes seria redundante. Ejemplo:
		 * Analizar 100:
		 * 1 x 100 = 100  -  2 x 50 = 100  -  4 x 25 = 100  -  5 x 20 = 100  
		 * 10 x 10 = 100 ( 10 es raiz de 100 )
		 * 20 x 5 = 100  -  25 x 4 = 100  -  50 x 2 = 100  -  100 x 1 = 100
		 * Como se puede ver a partir de la raiz (10) en adelante los factores se reinvierten y por eso se divide hasta la raiz cuadrada del numero en cuestion.
		 * */
		for( int i = 3; i < ceil( sqrt( n1 ) ); i++ ){
			//Si no es par
			if( !esPar( i ) ){
				//Si el resto de dividir n1 por el iterador es 0 significa que n1 es un numero compuesto.
				if( ( n1 % i ) == 0 ){
					return false;
				}
			}
		}
		return true;
	}
}

//Retorna un numero primo mayor que el parametro pasado
long damePrimo( long mayorQue ){
	long numeroPrimo = 0, numero = mayorQue;
	do{
		//Con cada repeticion al numero le sumo 1 para ir probando hasta encontrar el primo
		numero++;
		if( esPrimo( numero ) ){
			numeroPrimo = numero;
		}
	}while( numeroPrimo == 0 );
	 
	return numeroPrimo;
}
 
//Obtener numero aleatorio entre dos rangos definidos
long numeroAleatorioEntre( long minimo, long maximo ){
	return ( minimo + ( rand() % ( ( maximo + 1 ) - minimo ) ) );
}

//Algoritmo de euclides extendido
long* algEucExtendido( long n1, long n2 ){   
	long array[3], x = 0, y = 0, d = 0, x2 = 1, x1 = 0, y2 = 0, y1 = 1, q = 0, r = 0;
	if( n2 == 0 ){
		array[0] = n1;
		array[1] = 1; 
		array[2] = 0;  
	}else{
		while( n2 > 0 ){
			q = ( n1 / n2 ); 
			r = n1 - q * n2; 
			x = x2 - q * x1; 
			y = y2 - q * y1; 
			n1 = n2; 
			n2 = r; 
			x2 = x1; 
			x1 = x; 
			y2 = y1;             
			y1 = y; 
		}
		array[0] = n1;   // mcd ( n1, n2 )
		array[1] = x2;   // x
		array[2] = y2;   // y
	}
	return array;
}

/*
	Dados los numeros enteros a y n > 0, el inverso multiplicativo de "a" modulo "n" 
	esta dado por el numero entero "y" que pertenece a Zn, tal que a x y = 1(mod n).
*/
long Inverso_Zn( long a, long n ){
	long* ptr, array[3];
	ptr = algEucExtendido( n, a );
 
	array[0] = *ptr;
	array[1] = *( ptr + 1 );
	array[2] = *( ptr + 2 );
   
	if( array[0] != 1 ){
		return -1;
	}else{
		if( array[2] < 0 ){
			array[2] += n;
		}
		return array[2];
	}  
}

/*
	Exponenciacion modular
	Emplea una representacion binaria de un numero entero "K".
*/
unsigned long long  Exponenciacion_Zn(unsigned long long  a,unsigned long long  k,unsigned long long  n){
	// convertimos "k" a binario
	unsigned long long numero = k;
 
	unsigned long long bin[300];
	unsigned long long  ind = 0;
	while( numero >= 2 ){
		bin[ind++] = numero % 2;
		numero /= 2;      
	}     
	bin[ind] = numero;
	unsigned long long  tam = ind + 1;
	// for(unsigned long long i=0;i<tam;i++)
	// cout<<bin[i]<<endl;     
	/////////////////////////////   
      
	unsigned long long  b = 1;
	if( k == 0 ){
		return b;
	}
   
	unsigned long long  A = a;   
	for( long i = ( tam - 1 ); i >= 0; i-- ){
		b = ( b * b ) % n;
		if( bin[i] == 1 ){
			b=(A*b)%n; 
		}
	// cout<<"b :"<<b<<endl;   
	}
	return b;
}

// Retorna el numero de posicion donde se encuentra un caracter en una variable del tipo string
int get_pos( string texto, char elemento ){
	//Recorro tantas veces como caracteres en el string
	for( int i = 0; i < texto.size(); i++ ){
		//Si el ( caracter [i] == elemento ) => retornarmos [i] que seria la posicion donde se encontro.
  		if( texto.at( i ) == elemento ){
      		return i;
	  	}
  	}
   	return -1;
}

/*  
	Las funciones encriptar() y desencriptar(), hacen uso de distintas funciones que se encuentran declaradas mas arriba.
*/
void encriptar(string mensaje){
	long cifrado=0, productoPrimos=0, exponenteClavePrivada=0, e=0;
	long clavePublica = 0;
	do{
		//Generacion del par de claves
		//Paso 1: Generar dos numeros primos aleatorios GRANDES con el mismo tama�o.
		long primoUno = damePrimo( numeroAleatorioEntre( 50000, 99999 )	);
		long primoDos = damePrimo( numeroAleatorioEntre( 10000, 49999 )	);
		
		//Paso 2: Se calcula el producto entre los dos numeros
		productoPrimos = ( primoUno * primoDos );
		
		//Paso 3: Creacion de la clave publica.
		clavePublica = ( ( primoUno - 1 ) * ( primoDos - 1 ) );
		
		//Paso 4: Seleccionamos un entero aleatorio 'e' tal que mcd('e',clavePublica) = 1   y   1 < 'e' < clavePublica
		do{
			e = numeroAleatorioEntre( 2, clavePublica );
		}while( mcdEuclides( e, clavePublica ) != 1 );
		
		//Inverso Multiplicativo de "a" modulo "n"
		exponenteClavePrivada = Inverso_Zn(e,clavePublica);
		
		//Exponenciacion Modular
		//cifrado=Exponenciacion_Zn(mensaje,e,productoPrimos);
	}while(productoPrimos < 0 || exponenteClavePrivada < 0 );
	
	cout << " Clave Publica: "; color(9); 
	cout << productoPrimos << endl; color(3);
	
	cout << " Clave Privada: "; color(9);
	cout << exponenteClavePrivada << endl; color(3);
	
	//Representamos numericamente el mensaje
	unsigned long long mensaje_int[ mensaje.size() ]; //Creamos un array con la misma cantidad de espacios que caracteres en nuestro mensaje.
    
    for ( int i = 0; i < mensaje.size(); i++ ){
    	//Guardamos en cada posicion del array un numero en base a la posicion del caracter en una variable.
    	mensaje_int[i] = get_pos( alfabeto, mensaje.at( i ) ); 
    }
    
    cout <<"\n Lo que usted ingreso, posee: ["; color(9);  
		cout << mensaje.size(); color(3); 
			cout << "] caracteres\n"<<endl;
    	
    // Mostramos en la consola	
	for ( int i = 0; i < mensaje.size(); i++){
		cout << "\t ["; color(9); cout << mensaje.at(i); color(3); cout << "]: " << Exponenciacion_Zn( mensaje_int[i],e,productoPrimos) << endl;
	}
	cout<<"\n Fin de la encriptacion."<<endl;
}

void desencriptar(){
	long clavePublica, clavePrivada;
	int cantidadCaracteres;
	
	cout << " Ingrese la Clave Publica: ";color(4);
	cin >> clavePublica;color(5);
	
	cout << " Ingrese la Clave Privada: ";color(4);
	cin >> clavePrivada;color(5);
	
	//En base a este dato sera la cantidad de veces que pidamos algun caracter encriptado.
	cout << "\n Cuantos caracteres tiene el texto que ingreso?: ";color(4);
	cin >> cantidadCaracteres;color(5);
	
	/*
		Se hace uso del unsigned long long porque se ingresaran numeros que representan caracteres encriptados y pueden tenes tama�os grandes.
		int corto; // Entero de 32 bits 
		unsigned long long largo; // Entero de 64 bits 
	*/
	unsigned long long textoEncriptado[cantidadCaracteres];
	
	cout << "\n A continuacion ingrese los caracteres encriptados: "<<endl;
	
	// Repetimos tantas veces como cantidad de caracteres tenga la palabra / oracion y guardamos en un array.
	for (int i = 0; i < cantidadCaracteres; i++){
		cout << "\t[";
		if( ( i + 1 ) < 10){
			cout << "0";
		}
		cout << ( i + 1 ) << "]: ";
		color(4);
		cin>>textoEncriptado[i];
		color(5);
	}
	
	cout << "\n-----------------------\n";
	cout << " Mensaje desencriptado:\n";
	cout << "-----------------------\n";
	
	// Repetimos tantas veces como cantidad de caracteres tenga la palabra / oracion y a medida que mostramos, desencriptamos.
	for ( int i = 0; i < cantidadCaracteres; i++ ){
		cout << "\t" << textoEncriptado[i] << ": \t[" << alfabeto.at( Exponenciacion_Zn( textoEncriptado[i], clavePrivada, clavePublica ) ) << "] "<< endl;
	}
	
	cout << "\n------------------\n";
	cout << " Mensaje completo: ";
	
	// Mostramos todo el mensaje carcter al lado de caracter sin saltos de linea ni nada. 
	color(6);
	for ( int i = 0; i < cantidadCaracteres; i++){
		cout << alfabeto.at( Exponenciacion_Zn( textoEncriptado[i], clavePrivada, clavePublica ) );
	}
	color(5);
	cout << "\n------------------\t";
	
	cout << "\n\n Fin de la desencriptacion.\n\n";
}

int main(){
	color(8);
	cout<<"\t Encriptacion y Desencriptacion de un mensaje con RSA\n";
	cout<<"\t ----------------------------------------------------\n\n";
	cout<<"Consigna:\n";
	cout<<"---------\n";
	cout<<"\t*************************************************************************\n";
	cout<<"\t* Programar un encriptador de palabras mediante el metodo RSA,          *\n";
 	cout<<"\t* o dos metodos de encriptacion simples (en caso de no querer usar RSA).*\n";
 	cout<<"\t* donde dado un programa se muestre el mismo encriptado, con la opcion  *\n";
 	cout<<"\t* de recuperar el mensaje original                                      *\n";
 	cout<<"\t*************************************************************************\n\n";
 		
	long* clavesEncriptacion=0, clavePublica=0, clavePrivada=0, cifrado=0;
	
	long mensaje=0;
	int respuesta=0;
	
	char mensajeAux[300];
	string mensajeString;
	
	//Este ciclo se va a repetir constantemente hasta que el usuario selecione salir del programa.
	do{
			color(7);
			cout<<"\t\t Que desea realizar?\n";
			cout<<"\t\t -------------------\n\n";
			cout<<"\t\t [1] -> Encriptar un mensaje."<<endl;
			cout<<"\t\t [2] -> Desencriptar un mensaje."<<endl;
			cout<<"\t\t [0] -> Salir del programa."<<endl<<endl;
			cout<<"Quiero: ";
			cin>>respuesta;
			cout<<endl;
			
			if(respuesta==1){
				color(3);
				cout<<"\tUsted eligio encriptar un mensaje\n";
				cout<<"\t---------------------------------\n";
							
			    cout << "Ingrese el mensaje que desea encriptar: "; color(9);
			    //El cin.getLine "se confunde" ya que queda "colgado" un newLine y no lo ejecuta sin la llamada a esta funcion.
			    //Link de problemas comunes usando cin. ...: http://www.augustcouncil.com/~tgibson/tutorial/iotips.html#problems
			    cin.ignore(); 
			    //El "cin>>variable" no es util para leer cadenas de caracteres que contienen espacio entonces se utiliza getline.
				cin.getline(mensajeAux, 300, '\n');
			    
				color(3);
				
				//Almaceno toda la cadena de caracteres en un string
				mensajeString = mensajeAux;
				
				encriptar(mensajeString);

			}else if(respuesta==2){
				color(5);
				cout<<"\tUsted eligio desencriptar un mensaje\n";
				cout<<"\t------------------------------------\n";
				
				desencriptar();			
			}
	}while(respuesta!=0);
	
	cout<<"Adios"<<endl;
	
	//Final de los programas
    return 0;
	system("pause");
}
