#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<conio.h>
#include <windows.h> 

//Paz Exequiel 1k5 Leg 53382

/*Una empresa tiene dos empleados los cuales reciben en sus cuentas de correos diferentes email con
frases de una longitud no superior a 80 caracteres cada frase. Cada cierto número de frases estas deben ser
guardadas en un archivo de texto sin perder lo que se tenía ya guardado en el archivo.
Se Pide: que por medio de un menú se pueda realizar lo siguiente

a- Al abrir el sistema (programa) se deben crear los archivos “Archivo1.txt” y “Archivo2.txt”

b- Crear y Guardar la/s frase/s recibida por el empleado José Luis en el fichero “Archivo1.txt”. La/s
frase/s son ingresada por teclado.

c- Crear y Guardar las frases recibida por la empleada María Emilia en el fichero “Archivo2.txt”.
La/s frase/s son ingresada por teclado.

d- Al final del día ambos archivos son guardados en un único fichero. 
Deberá combinar ambos archivos mezclados, en un nuevo fichero “Frases.txt”. 
Es decir, una frase del Archivo1.txt y una del Archivo2.txt, otra del archivo1 otra del archivo2 y así sucesivamente.

e- Mostrar las frases del archivo de José Luis en minúscula.

f- Mostrar las frases del archivo de María Emilia en Mayúscula.

g- Mostrar las frases del Archivo combinado. Donde cada palabra deberá comenzar en mayúscula y el
resto de cada palabra en minúscula.

h- Al salir del sistema, Los archivos, Archivo1.txt y Archivo2.txt, creados deberán ser eliminados físicamente.

Nota: Tener en cuenta que para los ítems d, e, f existen funciones que realizan tales operaciones. También
se puede hacer de manera secuencial, analizando cada palabra. Deberán elegir que aplicar. */

struct registro
{
	char frase1[81],frase2[81];	
};

void gotoxy(int x,int y);
void ingresarFraseJLf(FILE *txt1, int&caracteresJL);
void ingresarFraseMEf(FILE *txt2, int &caracteresME);
void combinarGuardarf(FILE *txt1,FILE *txt2,FILE *FRASES,int caracteresJL,int caracteresME);
void frasesJLmin(FILE*txt1);
void frasesMEMay(FILE*txt2);
void frasesCombPrimMf(FILE*FRASES);

main()
{
	FILE *txt1,*txt2,*FRASES;
	char Archivo[161],frasesJoseLuis[81],frasesMariaEmilia[81];
	int option;
	int caracteresJL=0,caracteresME=0;
	
	//a- Al abrir el sistema (programa) se deben crear los archivos “Archivo1.txt” y “Archivo2.txt”
	txt1=fopen("Archivo1.txt","r+");
	txt2=fopen("Archivo2.txt","r+");
	if(txt1==NULL && txt2==NULL)
	{
		fclose(txt1);
		fclose(txt2);
		txt1=fopen("Archivo1.txt","w+");
		txt2=fopen("Archivo2.txt","w+");
	}
	FRASES=fopen("Frases.txt","r+");
	if(FRASES==NULL)
	{
		fclose(FRASES);
		FRASES=fopen("Frases.txt","w+");
	}
	
	do
	{
		gotoxy(18,0);
		printf("Menu");
		printf("\n========================================");
		printf("\n========================================");
		printf("\n1) Ingresar la frase de Jose Luis.");
		printf("\n2) Ingresar la frase de Maria Emilia.");
		printf("\n3) Guardar archivos en un fichero.");
		printf("\n4) Frases del archivo de Jose Luis en minuscula.");
		printf("\n5) Frases del archivo de Maria Emilia en Mayuscula.");
		printf("\n6) Frases del Archivo combinado, \nprimera letra de palabras en Mayuscula.");
		printf("\n0) Salir del programa.\n(NOTA, AL SALIR DEL PROGRAMA SE ELIMINAN \"Archivo1.txt\" y \"Archivo2.txt\".");
		printf("\n========================================");
		printf("\n========================================");
		printf("\nOpcion: ");
		scanf("%d",&option);
		system("cls");
		switch(option)
		{
			case 1:
				{
					ingresarFraseJLf(txt1,caracteresJL);
					break;
					
				}
			case 2:
				{
					ingresarFraseMEf(txt2,caracteresME);
					break;
				}
			case 3:
				{
					if(caracteresJL==0 || caracteresME==0)
					{
						printf("\nNo se ingresaron frases para combinar.");
						getch();
						system("cls");
					}
					else
					{
						combinarGuardarf(txt1,txt2,FRASES,caracteresJL,caracteresME);
					}
					
					break;
				}
			case 4:
				{
					frasesJLmin(txt1);
					break;
				}
			case 5:
				{
					frasesMEMay(txt2);
					break;
				}
			case 6:
				{
					frasesCombPrimMf(FRASES);
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
	fclose(txt1);
	fclose(txt2);
	fclose(FRASES);
	remove("Archivo1.txt");
	remove("Archivo2.txt");
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

void ingresarFraseJLf(FILE *txt1, int&caracteresJL)
{
	registro archivo;
	char agregar;
	
	gotoxy(7,0);
	printf("Ingreso de frases Jose Luis");
	printf("\n========================================");
	
	do
	{
		printf("\nIngrese frase: \n");
		_flushall();
		gets(archivo.frase1);
		caracteresJL=caracteresJL+strlen(archivo.frase1);
		printf("\nDesea agregar otra frase? S/N: ");
		agregar=getch();
		if(agregar=='s' || agregar=='S')
		{
			fprintf(txt1, strcat(archivo.frase1,"\n"));
			printf("\n");
		}
		else
		{
			fprintf(txt1,archivo.frase1);
		}
	}
	while(agregar=='s' || agregar=='S');
	system("cls");
}

void ingresarFraseMEf(FILE *txt2, int &caracteresME)
{
	registro archivo;
	char agregar;
	
	gotoxy(7,0);
	printf("Ingreso de frases Maria Emilia");
	printf("\n========================================");
	
	do
	{
		printf("\nIngrese frase: \n");
		_flushall();
		gets(archivo.frase2);
		caracteresME=caracteresME+strlen(archivo.frase2);
		printf("\nDesea agregar otra frase? S/N: ");
		agregar=getch();
		if(agregar=='s' || agregar=='S')
		{
			fprintf(txt2, strcat(archivo.frase2,"\n"));
			printf("\n");
		}
		else
		{
			fprintf(txt2,archivo.frase2);
		}
	}
	while(agregar=='s' || agregar=='S');

	system("cls");
}

void combinarGuardarf(FILE *txt1,FILE *txt2,FILE *FRASES,int caracteresJL,int caracteresME)
{
	registro archivo;
	
	gotoxy(7,0);
	printf("Combinar y Guardar JL y ME");
	printf("\n========================================\n");
	rewind(txt1);
	rewind(txt2);
	while (!feof(txt1) && !feof(txt2))
	{
		fgets(archivo.frase1,caracteresJL,txt1);
		printf ("%s", archivo.frase1);
		getch();
		fprintf(FRASES, strcat(archivo.frase1,"\n"));
		fgets(archivo.frase2,caracteresME,txt2);
		printf ("%s", archivo.frase2);
		getch();
		fprintf(FRASES, strcat(archivo.frase2,"\n"));
	}
	getch();
	system("cls");	
}

void frasesJLmin(FILE*txt1)
{
	registro archivo;
	rewind(txt1);
	while(!feof(txt1))
	{
		fgets(archivo.frase1,100,txt1);
		printf("%s",strlwr(archivo.frase1));
	}
	getch();
	system("cls");
}

void frasesMEMay(FILE*txt2)
{
	registro archivo;
	rewind(txt2);
	while(!feof(txt2))
	{
		fgets(archivo.frase2,100,txt2);
		printf("%s",strupr(archivo.frase2));
	}
	getch();
	system("cls");
}

void frasesCombPrimMf(FILE*FRASES)
{
	char c[300];
	int i=0,n;
	
	rewind(FRASES);
	do
	{
		c[i]=getc(FRASES);
		i++;	
	}while(!feof(FRASES));
	n=i;
	for(i=0;i<n;i++)
	{
		printf("%c",c[i]);
	}
	getch();
	for(i=0;i<n;i++)
	{
		if(i==0)
		{
			if(c[i]>='a' && c[i]<='z')
			{
				c[i]=c[i]-'a'+'A';
			}
		}
		else
		{
			if(c[i]=='\n' || c[i]==' ')
			{
				if(isalpha(c[i+1]))
				{
					if(c[i+1]>='a' && c[i+1]<='z')c[i+1]=c[i+1]-'a'+'A';
				}			
			}
		}
	}
	for(i=0;i<n;i++)
	{
		printf("%c",c[i]);
	}
	getch();
	system("cls");
}




