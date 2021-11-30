#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<conio.h>
#include <windows.h> 

//Paz Exequiel 1k5 Leg 53382

/*Una empresa dedicada a las ventas de productos por mayor registra en un archivo binario solo los
totales de ventas que se van realizando durante el día. 
Las cargas de los datos se realizan en cualquier momento, por lo que el archivo no debe perder la información con una nueva carga.
El dueño de la empresa solicita, al centro de cómputos, le confeccione un sistema qué por medio
de un menú se pueda realizar lo siguiente:
	
? Permitir registrar en cualquier momento los montos totales de venta.

? Saber cuál es la mayor venta guardada y la cantidad de veces que se registró el mismo
monto.

? Visualizar los datos en pantallas, donde cada fila deberá tener 10 datos separados por un
guion y visualizar 6 dígitos por cada valor. En caso de que la cantidad sea menor a 6 dígitos
rellenar con ceros a la izquierda hasta completar los 6 dígitos.

? Saber cuál es el monto total de las ventas realizadas en el momento de la consulta.

? Permitir al final del día borrar el archivo.

NOTA:
Utilizar para todas las opciones del menú funciones. Cada función deberá recibir cómo uno
sus parámetros el archivo.
El archivo debe ser abierto al inicio del programa y cerrarlo al final del programa. 
*/


void gotoxy(int x,int y);

void cargarVentasf(FILE *arch);

void mayorContarf(FILE *arch);

void mostrarVentasf(FILE *arch);

void sumarVentasf(FILE *arch);

void eliminarArchivof(FILE*arch, int &option);

main()
{
	FILE *arch;
	int option;
	
	arch = fopen("ventas.dat","a+b");
	if(arch==NULL)
	{
		printf("\n\n Ocorrió un error al intentar abrir el archivo.....\n");
		system("PAUSE");
		exit(1);
	}
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	system("color 1A");	
	
	do
	{
		gotoxy(18,0);
		printf("Menu");
		printf("\n----------------------------------------");
		printf("\n----------------------------------------");
		printf("\n1) Registrar venta.");
		printf("\n2) Ver y contar mayor venta.");
		printf("\n3) Ver las ventas realizadas.");
		printf("\n4) Monto total de ventas.");
		printf("\n5) Borrar el archivo.");
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
					cargarVentasf(arch);
					break;					
				}
			case 2:
				{
					mayorContarf(arch);
					getch();
					system("cls");
					break;	
				}
			case 3:
				{
					mostrarVentasf(arch);
					getch();
					system("cls");
					break;
				}
			case 4:
				{
					sumarVentasf(arch);
					getch();
					system("cls");
					break;
				}
			case 5:
				{
					eliminarArchivof(arch,option);
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
	fclose(arch);	
}

void gotoxy(int x,int y)
{
	HANDLE hcon;
	hcon=GetStdHandle (STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void cargarVentasf(FILE *arch)
{
	float venta;
	char b;
	
	do
	{
		gotoxy(11,0);
		printf("Cargar venta");
		printf("\n----------------------------------------");
		printf("\nMonto de la venta: ");
		scanf("%f",&venta);
		fwrite(&venta,sizeof(float),1,arch);
		_flushall();
		do
		{
			printf("\nIngresar otra venta? S/N\n");
			b=getch();
			if (b >= 'a' && b <= 'z')
       		b = b - 'a' + 'A';
			if(b!='S' && b!='N')
			{
				printf("\nOpcion no valida!!\n\n");
				getch();
			}
			system("cls");
		}
		while(b!='S' && b!='N');
	}
	while(b=='S');
		
	system("cls");
}

void mayorContarf(FILE *arch)
{
	float mayor=0.0;
	float venta;
	int c=0;
	rewind(arch);
	fread(&venta,sizeof(float),1,arch);
	while(!feof(arch))
	{
		if(venta>mayor)
		{
			mayor=venta;
		}
		fread(&venta,sizeof(float),1,arch);
	}
	rewind(arch);
	fread(&venta,sizeof(float),1,arch);
	while(!feof(arch))
	{
		if(mayor==venta)c++;
		fread(&venta,sizeof(float),1,arch);
	}
	printf("La mayor venta ingresada es %.2f y se registro %d veces",mayor,c);
}

void mostrarVentasf(FILE *arch)
{
	float ventas;
	int c=0;
	rewind(arch);
	fread(&ventas,sizeof(float),1,arch);
	while(!feof(arch))
	{
		if(c<10)
		{
			printf("%09.2f",ventas);			
			c++;
			if(c<10)printf("-");
		}
		else
		{
			printf("\n");
			c=0;
		}
		fread(&ventas,sizeof(float),1,arch);
	}
}

void sumarVentasf(FILE *arch)
{
	float ventas, sumar=0.0;
	rewind(arch);
	fread(&ventas,sizeof(float),1,arch);
	while(!feof(arch))
	{
		sumar=sumar+ventas;
		fread(&ventas,sizeof(float),1,arch);
	}
	printf("Monto total de ventas: %09.2f",sumar);
}

void eliminarArchivof(FILE*arch, int &option)
{
	char b;
	do
	{
		printf("\nEsta por eliminar el archivo y salir del programa, desea continuar? S/N\n");
		b=getch();
		if (b >= 'a' && b <= 'z')
   		b = b - 'a' + 'A';
		if(b!='S' && b!='N')
		{
			printf("\nOpcion no valida!!\n\n");
			getch();
		}
	}
	while(b!='S' && b!='N');
	if(b=='S')
	{
		fclose(arch);
		remove("ventas.dat");
		printf("\nArchivo eliminado correctamente.");
		option=0;
	}
	else
	{
		printf("\nVolviendo al menu principal...");
	}
}
