#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<conio.h>
#include <windows.h> 

//Paz Exequiel 1k5 Leg 53382

/*Crear un archivo de texto en donde se guardaran los siguientes de N estudiante, cada dato (campo)
que se almacenan en el archivo son los siguientes
Nombre.
Apellidos.
Carrera que estudia.
Nota promedio.
1) Realizar la carga de los N estudiantes, tenga en cuenta que cada uno de los 
datos estará separado por un punto y coma “;” y los datos de cada estudiante debe ocupar una línea en el
archivo.

2) Realizar el listado de los datos guardados.

3) Contar la cantidad de apellidos iguales que tiene el archivo.

4) Contar cuantos estudiantes cursan la misma carrera.

5) Ingresar el apellido y nombre de un estudiante y mostrar la carrera que estudia y su nota
promedio. Tenga en cuenta que los datos se pueden ingresar de diferente forma ej: todo en
mayúscula, minúscula, alguna mayúscula.*/

typedef char cadena[50];

struct registro
{
	char Nombre[50];
	char Apellidos[50];
	char Carrera[50];
	float NotaPromedio;
};

void gotoxy(int x,int y);
void cargarEstudiantesf(FILE *alu,registro alumnos,int&n);
void listarf(FILE *alu);
void contarApellidosIgualesf(FILE *alu);
void contarMismaCarrera(FILE *alu);
void mostrarCarreraProm(FILE *alu);

main()
{
	
	int n,option;
	registro alumnos;
	FILE *alu;
	
	alu=fopen("alumnos.txt","r+");
	if(alu==NULL)
	{
		fclose(alu);
		alu=fopen("alumnos.txt","w+");
	}
	do
	{
		gotoxy(18,0);
		printf("Menu");
		printf("\n========================================");
		printf("\n========================================");
		printf("\n1) Ingresar la carga de los estudiantes.");
		printf("\n2) Listar Datos de Alumnos.");
		printf("\n3) Contar Apellidos Iguales.");
		printf("\n4) Contar cuantos alumnos cursan la misma carrera.");
		printf("\n5) Mostrar Carrera y Promedio de alumno.");
		printf("\n0) Salir.");
		printf("\n========================================");
		printf("\n========================================");
		printf("\nOpcion: ");
		scanf("%d",&option);
		system("cls");
		switch(option)
		{
			case 1:
				{
					cargarEstudiantesf(alu,alumnos,n);
					break;
					
				}
			case 2:
				{
					listarf(alu);
					break;
				}
			case 3:
				{
					contarApellidosIgualesf(alu);
					break;
				}
			case 4:
				{
					contarMismaCarrera(alu);
					break;
				}
			case 5:
				{
					mostrarCarreraProm(alu);
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
	}while(option!=0);
	
	fclose(alu);
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


void cargarEstudiantesf(FILE *alu,registro alumnos,int&n)//carga de datos
{
	
	char NotaPromedio[10];
	
	gotoxy(13,0);
	printf("Carga de datos");
	printf("\n========================================");
	printf("\nIngrese la cantidad de alumnos: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("\nIngrese los datos del alumno %d",i);
		printf("\nNombre: ");
		_flushall();
		gets(alumnos.Nombre);
		fprintf(alu,strcat(alumnos.Nombre,"; "));
		printf("\napellido: ");
		gets(alumnos.Apellidos);
		fprintf(alu,strcat(alumnos.Apellidos,"; "));
		printf("\nCarrera que estudia: ");		
		gets(alumnos.Carrera);
		fprintf(alu,strcat(alumnos.Carrera,"; "));
		printf("\nNota Promedio: ");
		scanf("%f",&alumnos.NotaPromedio);
		sprintf(NotaPromedio,"%.2f",alumnos.NotaPromedio);
		fprintf(alu,strcat(NotaPromedio,"\n"));
	}
	getch();
	system("cls");	
}

void listarf(FILE *alu)
{
	char NotaPromedio[10];
	registro alumnos;
	gotoxy(13,0);
	printf("Datos Alumnos");
	printf("\n========================================\n");
	
	rewind(alu);
	
	while(!feof(alu))
	{
		if(!feof(alu))
		{
			fscanf(alu,"%s",&alumnos.Nombre);
			printf("Nombre: %s\n",alumnos.Nombre);
			fscanf(alu,"%s",&alumnos.Apellidos);
			printf("Apellido: %s\n",alumnos.Apellidos);
			fscanf(alu,"%s",&alumnos.Carrera);
			printf("Carrera: %s\n",alumnos.Carrera);
			fscanf(alu,"%s",&NotaPromedio);
			printf("Promedio: %s\n",NotaPromedio);
			printf("\n\n");	
		}			
	}
	
	getch();
	system("cls");
}

void contarApellidosIgualesf(FILE *alu)
{
	cadena NotaPromedio[50];
	registro alumnos[50],aux;
	int i=0,comparar,contar=0,n;
	gotoxy(8,0);
	printf("Contar apellidos iguales");
	printf("\n========================================\n");
	rewind(alu);	
	while(!feof(alu))
	{
		if(!feof(alu))
		{
			fscanf(alu,"%s",&alumnos[i].Nombre);
			fscanf(alu,"%s",&alumnos[i].Apellidos);
			fscanf(alu,"%s",&alumnos[i].Carrera);
			fscanf(alu,"%s",&NotaPromedio[i]);		
		}		
		i++;	
	}
	n=i;
	for(i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			comparar=strcmp(alumnos[i].Apellidos,alumnos[i+1].Apellidos);
			if(comparar>0)
			{
				strcpy(aux.Apellidos,alumnos[i].Apellidos);
				strcpy(alumnos[i].Apellidos,alumnos[i+1].Apellidos);
				strcpy(alumnos[i+1].Apellidos,aux.Apellidos);
			}
		}
	}
	for(i=0;i<n;i++)
	{
		comparar=strcmp(alumnos[i].Apellidos,alumnos[i+1].Apellidos);
		if(comparar==0)
		{
			contar++;
		}
	}
	printf("La Cantidad de Apellidos Iguales es: %d",contar);
	getch();
	system("cls");
	
}

void contarMismaCarrera(FILE *alu)
{
	cadena NotaPromedio[50],NotaPromedioAux[50];
	registro alumnos[50],aux;
	int i=0,comparar,contar=1,n;
	gotoxy(3,0);
	printf("Contar alumnos con la misma carrera");
	printf("\n========================================\n");
	rewind(alu);	
	while(!feof(alu))
	{
		if(!feof(alu))
		{
			fscanf(alu,"%s",&alumnos[i].Nombre);
			fscanf(alu,"%s",&alumnos[i].Apellidos);
			fscanf(alu,"%s",&alumnos[i].Carrera);
			fscanf(alu,"%s",&NotaPromedio[i]);		
		}		
		i++;	
	}
	n=i;
	for(i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			comparar=strcmp(alumnos[i].Carrera,alumnos[i+1].Carrera);
			if(comparar>0)
			{
				strcpy(aux.Carrera,alumnos[i].Carrera);
				strcpy(alumnos[i].Carrera,alumnos[i+1].Carrera);
				strcpy(alumnos[i+1].Carrera,aux.Carrera);
			}
		}
	}
	for(i=0;i<n;i++)
	{
		comparar=strcmp(alumnos[i].Carrera,alumnos[i+1].Carrera);
		if(comparar==0)
		{
			contar++;
		}
	}
	if(contar==1)
	{
		printf("No hay alumnos que cursen la misma carrera");
	}
	else
	{
		printf("La Cantidad de alumnos que cursan la misma carrera son: %d",contar);
	}
	
	getch();
	system("cls");
	
}
/*Ingresar el apellido y nombre de un estudiante y mostrar la carrera que estudia y su nota
promedio. Tenga en cuenta que los datos se pueden ingresar de diferente forma ej: todo en
mayúscula, minúscula, alguna mayúscula.*/

void mostrarCarreraProm(FILE *alu)
{
	char apellido[20],nombre[50];
	cadena NotaPromedio[50];
	registro alumnos[50],aux[50];
	int i=0,compararAp,compararNom,n, pos;
	bool b=false;
	gotoxy(11,0);
	printf("Carrera y Promedio");
	printf("\n========================================\n");
	rewind(alu);	
	while(!feof(alu))//
	{
		if(!feof(alu))
		{
			fscanf(alu,"%s",&alumnos[i].Nombre);
			fscanf(alu,"%s",&alumnos[i].Apellidos);
			fscanf(alu,"%s",&alumnos[i].Carrera);
			fscanf(alu,"%s",&NotaPromedio[i]);
			alumnos[i].NotaPromedio=atof(NotaPromedio[i]);		
		}		
		i++;	
	}
	n=i;
	for(int i=0;i<n;i++)
	{
		strcpy(aux[i].Nombre,alumnos[i].Nombre);
		strupr(aux[i].Nombre);
		strcpy(aux[i].Apellidos,alumnos[i].Apellidos);
		strupr(aux[i].Apellidos);
		strcpy(aux[i].Carrera,alumnos[i].Carrera);
		strcpy(aux[i].Carrera,alumnos[i].Carrera);
		aux[i].NotaPromedio=alumnos[i].NotaPromedio;
	}
	printf("Ingrese los datos del alumno que desea buscar y mostrar: ");
	printf("\nApellido: ");
	_flushall();
	gets(apellido);
	strupr(apellido);
	strcat(apellido,";");
	printf("Nombre: ");
	gets(nombre);
	strupr(nombre);
	strcat(nombre,";");
	for(int i=0;i<n;i++)
	{
		compararAp=strcmp(aux[i].Apellidos,apellido);
		compararNom=strcmp(aux[i].Nombre,nombre);
		if(compararAp==0 && compararNom==0)
		{
			pos=i;
			b=true;
		}
	}
	if(b==true)
	{
		printf("\nDatos del Alumno: ");
		printf("\nNombre: %s",alumnos[pos].Nombre);
		printf("\nApellido: %s",alumnos[pos].Apellidos);
		printf("\nNota Promedio: %.2f", alumnos[pos].NotaPromedio);
		printf("\nCarrera: %s",alumnos[pos].Carrera);
	}
	else
	{
		printf("\nNo se encontró el Nombre y Apellido ingresado");
	}	
	getch();
	system("cls");
	
}
