#include <iostream> 
#include <windows.h> //Agregado para cambiar el color
#include <conio.h> //Para el getch...
#include <cmath> //Funciones matematicas: sqrt

using namespace std;

//Se hace uso del algoritmo de Euclides para averiguar el MCD de dos numeros. Este metodo fue creado por el matematico griego Euclides.
//https://es.wikipedia.org/wiki/Algoritmo_de_Euclides
int mcdEuclides(int n1, int n2){
	int maximo, minimo, resto;
	
	//Identificamos el maximo y el minimo de los parametros.
	if(n1>=n2){
		maximo=n1;
		minimo=n2;
	}else{
		maximo=n2;
		minimo=n1;
	}
	
	while(minimo!=0){
		resto=maximo%minimo;
		maximo=minimo;
		minimo=resto;
	}
	
	return maximo;
}

//Retorna true si el numero que le pasamos es par.
bool esPar(int numero){
	if(numero%2==0){
		return true;
	}else{
		return false;
	}
}

//Por tentativa http://es.wikihow.com/saber-si-un-n%C3%BAmero-es-primo
bool esPrimo(int n1){
	//TODOS los numeros pares a excepcion del dos son compuestos.
	if(esPar(n1) && n1!=2){
		return false;
	}else{
		/*
		 * ceil "redondea" hacia arriba.
		 * sqrt retorna la raiz cuadrada.
		 * Se divide hasta la raiz cuadrada del numero ya que dividir por los numeros siguientes seria redundante. Ejemplo:
		 * Analizar 100:
		 * 1x100=100  -  2x50=100  -  4x25=100  -  5x20=100  
		 * 10x10=100 (10 es raiz de 100)
		 * 20x5=100  -  25x4=100  -  50x2=100  -  100x1=100
		 * Como se puede ver a partir de la raiz en adelante los factores se reinvierten y por eso se divide hasta la raiz cuadrada del numero en cuestion.
		 * */
		for( int i = 3; i < ceil( sqrt( n1 ) ); i++ ){
			//Si no es par
			if(!esPar(i)){
				//Si el resto de dividir n1 por el iterador es 0 significa que n1 es un numero compuesto.
				if(n1%i==0){
					return false;
				}
			}
		}
		return true;
	}
}

//Retorna un numero primo mayor que el parametro pasado
 long damePrimo(long mayorQue){
	 long numeroPrimo=0, numero=mayorQue;
	 do{
		 //Con cada repeticion al numero le sumo 1 para ir probando hasta encontrar el primo
		 numero++;
		 if(esPrimo(numero)){
			 numeroPrimo=numero;
		 }
	 }while(numeroPrimo==0);
	 
	 return numeroPrimo;
 }
 
 //Obtener numero aleatorio entre dos rangos definidos
 long numeroAleatorioEntre(long minimo, long maximo){
	 return (minimo+rand()%((maximo+1)-minimo));
 }
 
 //Obtener numero aleatorio mayor que otor numero
 long numeroAleatorioMayorQue(long minimo){
	 return (minimo+rand());
 }

/*
 * Programar un encriptador de palabras mediante el metodo RSA,
 * o dos metodos de encriptacion simples (en caso de no querer usar RSA);
 * donde dado un programa se muestre el mismo encriptado, con la opcion
 * de recuperar el mensaje original
 * */

//Entrada a,b pertenecientes a los enteros positivos. Con a >= b. Retorna: D = MCD(a,b)
/*
int* euclidesExtendido( int a, int b ){
	int d, x, y;
	int x1=0, x2=1, y1=1, y2=0;
	int q, r;
	if( b == 0 ){
		d = x;
		x = 1;
		y = 0;
	}else{
		while ( b > 0 ){
			q = ( a / b );
			r = ( a - ( q * b ) );
			x = ( x2 - ( q * x1 ) );
			y = ( y2 - ( q * y1 ) );
			a = b;
			b = r;
			x2 = x1;
			x1 = x;
			y2 = y1;
			y1 = y;
		}
		d = a;
		x = x2;
		y = y2;
	}
	int arr[3];
	arr[0] = d;
	arr[1] = x;
	arr[2] = y;
	return ( arr );
}
 
int Inverso_Zn( int a, int n ){
	int* ptr, array[3];
	ptr = euclidesExtendido( n, a );
 
	array[0] = *ptr;
	array[1] = *(ptr+1);
	array[2] = *(ptr+2);
   
	if( array[0] != 1 ){
		return -1;
	}else{
		if( array[2] < 0 ){
			array[2] += n;
		}
		return array[2];
	}  
}

*/
struct testDev{
	int n1;
};
/*
testDev(int v1, int v2){
	n1=v1;

}
*/
long* alg_euc_ext( int n1, int n2 ){   
	long array[3], x = 0, y = 0, d = 0, x2 = 1, x1 = 0, y2 = 0, y1 = 1, q = 0, r = 0;
	if( n2 == 0 ){
		array[0] = n1;
		array[1] = 1; 
		array[2] = 0;  
	}else{
		while(n2>0){
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
		array[0] = n1;   // mcd (n1,n2)
		array[1] = x2;   // x
		array[2] = y2;   // y
	}
	return array;
}

long Inverso_Zn( int a, int n ){
	long* ptr,	array[3];
	ptr = alg_euc_ext( n, a );
 
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

unsigned long long  Exponenciacion_Zn(unsigned long long  a,unsigned long long  k,unsigned long long  n){
	// convertimos "k" a binario
	unsigned long long numero = k;
 
	unsigned long long bin[300];
	unsigned long long  ind = 0;
	while( numero >= 2 ){
	bin[ind++] = numero % 2;
	numero/=2;      
	}     
	bin[ind] = numero;
	unsigned long long  tam = ind + 1;
	// for(int i=0;i<tam;i++)
	// cout<<bin[i]<<endl;     
	/////////////////////////////   
      
	unsigned long long  b = 1;
	if( k == 0 ){
		return b;
	}
   
	unsigned long long  A = a;   
	for( int i = ( tam - 1 ); i >= 0; i-- ){
		b = ( b * b ) % n;
		if( bin[i] == 1 ){
			b=(A*b)%n; 
		}
	// cout<<"b :"<<b<<endl;   
	}
return b;
}

void encriptar(){
	//Generacion del par de claves
	//Paso 1: Generar dos numeros primos aleatorios GRANDES con el mismo tamaño.
	int primoUno	=	damePrimo( numeroAleatorioEntre( 50000, 99999 )	);
	int primoDos 	=	damePrimo( numeroAleatorioEntre( 10000, 49999 )	);
	
	//Paso 2: Se calcula el producto entre los dos numeros primos.
	int productoPrimos	=	( primoUno * primoDos );  // n
	
	//Paso 3: Creacion de la clave publica.
	int clavePublica	=	( ( primoUno - 1 ) * ( primoDos - 1 ) ); // d   p(n) fi
	
	//Paso 4: Seleccionamos un entero aleatorio 'e' tal que mcd('e',clavePublica) = 1   y   1 < 'e' < clavePublica
	int e;
	do{
		e = numeroAleatorioEntre( 2, clavePublica );
	}while( mcdEuclides( e, clavePublica ) != 1 );
	
	//Paso 5: se determina un 'd' tal que: (d*e) - 1 es divido exactamente por p(n)
	//		int exponenteClavePrivada = Inverso_Zn(e,clavePublica); // d
	
	//2 Cifrado del mensaje con la clave publica
	int mensaje=0, cifrado=0;
	
	cout<<"Por favor, escriba el mensaje que desea encriptar: ";
	cin>>mensaje;
	
	cifrado=Exponenciacion_Zn(mensaje,e,productoPrimos);
	
	cout<<"Encriptado el mensaje es: "<<cifrado<<endl<<endl;
}

void desencriptar(){
	//3 Desifrado del mensaje con la clave privada
	
	//cout<<"Decifrado del mensaje: "<<Exponenciacion_Zn(cifrado,exponenteClavePrivada,productoPrimos);
}

int main(){
	cout<<"\t Encriptacion y Desencriptacion de un mensaje con RSA"<<endl<<endl;
	cout<<"\t\t Que desea realizar?"<<endl;
	cout<<"\t\t [1] -> Encriptar un mensaje."<<endl;
	cout<<"\t\t [2] -> Desencriptar un mensaje."<<endl;
	cout<<"\t\t [0] -> Salir del programa."<<endl<<endl;
	
	int respuesta;
	
	do{
			cout<<"Quiero: ";
			cin>>respuesta;
			
			if(respuesta==1){
				cout<<"Usted eligio encriptar un mensaje"<<endl<<endl;
				encriptar();
			}else if(respuesta==2){
				cout<<"Usted eligio desencriptar un mensaje"<<endl<<endl;
				desencriptar();
			}else if(respuesta!=0){
				cout<<"\t\t [1] -> Encriptar un mensaje."<<endl;
				cout<<"\t\t [2] -> Desencriptar un mensaje."<<endl;
				cout<<"\t\t [0] -> Salir del programa."<<endl<<endl;
			}
	}while(respuesta!=0);
	
	cout<<"Adios"<<endl;
	
	//Final de los programas
    getch();
    return 0;
	system("pause");

}