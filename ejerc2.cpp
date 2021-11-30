#include<conio.h>
#include<time.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

//Paz Exequiel 1K5 Legajo 53382

/*Al iniciar el programa el sistema deberá abrir para su escritura, sin perder los datos ya guardado, el
archivo numeros.dat, en caso de que no exista el archivo deberá crear el archivo numero.dat y almacenar
(guardar) la cantidad de 276 números enteros comprendido entre el rango de valores [125…789] los cuales
serán generados de manera aleatoria.

Creado o abierto el archivo, realizar un menú que permita mostrar en la función mail la siguiente
información:
	
? Determinar cuántos valores pares e impares están guardado en el archivo.

? Listar el archivo.

? Agregar un número no determinado de nuevos Datos. Verificando que el valor ingresado
sea un entero.

? Ingresar por teclado un valor y determinar si está almacenado (guardado) en el archivo.
Enviar un mensaje en pantalla indicando si fue encontrado o no el valor.

? Determinar cuántos valores están en el rango [125…500] y (500…789].

NOTA:
para cada una de las opciones deberá usar una función.
al ingresar a la función se deberá abrir el archivo.
Al salir de la función se debe cerrar el archivo.*/

void contarParImpar(FILE *num);
void listarf(FILE*num);
void agregarEnterof(FILE*num);
void buscarValorf(FILE*num);
void contarRango(FILE*num);
main()
{
	FILE *num;
	int option;
	const int limite_inferior=125, limite_superior=789,n=276;
	srand(time(NULL));
	time(NULL);
	int var;
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	system("color 1A");
	num=fopen("numeros.dat","a+b");
	if(num==NULL)
	{
		printf("Error el archivo no pudo ser abiero!");
		system("PAUSE");
		exit(1);
	}
	for(int i=0;i<n;i++)
	{
		var = limite_inferior + rand() % (limite_superior+1 - limite_inferior);
		fwrite(&var,sizeof(int),1,num);
	}
		

	do
	{
		
		printf("Menu");
		printf("\n----------------------------------------");
		printf("\n----------------------------------------");
		printf("\n1) Contar Pares/Impares.");
		printf("\n2) Listar Archivo.");
		printf("\n3) Agregar un nuevo entero.");
		printf("\n4) Buscar un valor en el Archivo.");
		printf("\n5) Contar valores dentro de rangos.");
		printf("\n0) Salir del programa.");
		printf("\n----------------------------------------");
		printf("\n----------------------------------------");
		printf("\nOpcion: ");
		scanf("%d",&option);
		system("cls");
		switch(option)
		{
			case 1:
				{
					contarParImpar(num);
					getch();
					system("cls");
					break;					
				}
			case 2:
				{
					listarf(num);
					getch();
					system("cls");
					break;	
				}
			case 3:
				{
					agregarEnterof(num);
					getch();
					system("cls");
					break;
				}
			case 4:
				{
					buscarValorf(num);
					getch();
					system("cls");
					break;
				}
			case 5:
				{
					contarRango(num);
					getch();
					system("cls");
					break;
				}
			default:
				{
					if(option!=0)
					{
						printf("\nOpcion no valida");
					}
					else
					{
						printf("\nSaliendo del programa...");
					}
					getch();
					system("cls");
				}	
		}	
	}
	while(option!=0);	
	fclose(num);
}

void contarParImpar(FILE*num)
{
	int par=0, impar=0,div,var;
	rewind(num);
	do
	{
		fread(&var,sizeof(int),1,num);
		div=var%2;
		if(div==0){par++;
		}
		else{impar++;
		}
	}while(!feof(num));
	printf("La cantidad de numeros enteros pares es: %d",par);
	printf("\nLa cantidad de numeros enteros impares es: %d",impar);
}

void listarf(FILE*num)
{
	int var;
	rewind(num);
	do
	{
		fread(&var,sizeof(int),1,num);
		if(!feof(num))
		{
			printf("%d\n",var);
		}
			
	}while(!feof(num));
}

void agregarEnterof(FILE*num)
{
	int var, numEntero=0;
	float numero=0, dif=0;
	do
	{
		printf("Ingresar el valor entero que quiere agregar al archivo: ");
		scanf("%f",&numero);
		numEntero=trunc(numero);
		dif=numero-numEntero;
		if(dif==0)
		{
			var=(int)numero;
			fseek (num,sizeof(int),SEEK_END);
			fwrite(&var,sizeof(int),1,num);
			printf("\nNumero %d ingresado correctamente", numEntero);
		
		}
		else
		{
			printf("\nEl numero ingresado no es un numero entero\n");
			getch();
			system("cls");
		}
	}
	while(dif!=0);	
}

void buscarValorf(FILE*num)
{
	int var, numero,b=0;
	rewind(num);
	printf("Ingrese el valor que desea buscar: ");
	scanf("%d",&numero);
	do
	{
		fread(&var,sizeof(int),1,num);
		if(var==numero)
		{
			printf("\nEl numero %d fue encontrado",numero);
			b=1;
		}
		
	}
	while(!feof(num));
	if(b==0)
	{
		printf("\nEl numero %d no fue encontrado",numero);
	}
}

void contarRango(FILE*num)
{
	int var,contadorInf=0,contadorSup=0; //[125…500] y (500…789].
	rewind(num);
	do
	{
		fread(&var,sizeof(int),1,num);
		if(var>=125 && var <=500)contadorInf++;
		if(var>500 && var <=789)contadorSup++;
	}
	while(!feof(num));	
	printf("\nLa cantidad de valores entre [125,500] es %d",contadorInf);
	printf("\nLa cantidad de valores entre (500,789] es %d",contadorSup);
}
