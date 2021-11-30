#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>

//Paz Exequiel 1K5 Legajo 53382

/*En un archivo se tienen registradas las ventas que realiza un comercio. 
Cada registro contiene los siguientes datos:
	
- Numero de vendedor (Son tres los vendedores 1, 2, 3)
- Apellido y Nombre del vendedor
- Numero Factura.
- Importe facturado por esa venta.
- Forma de venta (1: Contado, 2: Crédito)
- Fecha de Venta (DD MM AAAA) (Año se registra 4 dígitos) campo jerarquizado.

Desarrolle un programa que permita realizar, al encargado del negocio, por medio de un menú las
siguientes operaciones que deben ser realizadas en función diferente:
	
a. Carga de los datos al archivo, tener en cuenta que cada vez
que se habrá el archivo o se realice una nueva carga NO debe perder lo que ya se tiene registrado.
Y verificar que se ingresen valores válidos para los miembros número de vendedor y forma
de venta.

b.Cantidad total de venta registrada en un mes determinado. (El mes debe ser solicitado por teclado).

c. Mostrar cuantas ventas se realizaron de Contado y cuantas ventas se realizaron a Crédito, de un
determinado mes. (El mes se solicita por teclado).

d.Importe total realizado en el mes por un vendedor. (El apellido y nombre del vendedor, deberá ser
solicitado por teclado).

e. Listar todos los datos que contiene el archivo.
-----------------------------------------------------
f. Realizar la modificación del campo “forma de venta” de una determinada factura, la búsqueda para
modificar será por su número de factura. Nota: mostrar el valor anterior y pedir el nuevo valor del
contenido del campo forma de venta.

g. Realizar baja lógica a una determinada factura. La búsqueda se realiza por número de factura. Una
vez encontrado mostrar sus datos y solicitar confirmación antes de realizar el borrado lógico. En el
caso de no encontrarse mostrar un mensaje de error.

h.Listar todos los registros que hayan sido marcado como borrado lógico.

i. Realizar el borrado físico de los registros marcados con borrado lógico. Para ingresar a esta opción
se debe solicitar una clave de ingreso.

j. Ordenar el archivo por número de factura y listar los datos ordenados.
*/

typedef char cadena[50];

struct fecha
{
	int dia,mes,anio;
};

struct registro
{
	int numero;
	cadena apeNom;
	int factura;
	float venta;
	int formaVenta;
	fecha fechaVenta;
	bool borrado;
};

void gotoxy(int x,int y);
void cargarDatosVendedores(FILE*arch, registro vendedores,FILE*cont);
void ventasMensuales(FILE*arch, registro vendedores);
void contarVentas(FILE*arch, registro vendedores);
void ventasVendedor(FILE*arch, registro vendedores);
void listarVendedoresf(FILE*arch,registro vendedores);
void modificarFormaVentaf(FILE*arch,registro vendedores);
void borradoLogico(FILE*arch,registro vendedores);
void mostrarBorradoLogico(FILE*arch,registro vendedores);
void borradoFisicof(FILE*arch,registro vendedores);
void ordenarPorFacturaf(FILE*arch,registro vendedores);

main()
{
	FILE *arch,*cont;
	int option;
	registro vendedores;
	
	arch = fopen("vendedores.dat","r+b");
	cont = fopen("contador.dat","r+b");
	if(arch==NULL)
	{
		fclose(arch);
		fclose(cont);
		arch = fopen("vendedores.dat","w+b");
		cont = fopen("contador.dat","w+b");
	}
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	system("color F1");	
	
	do
	{
		gotoxy(18,0);
		printf("Menu");
		printf("\n========================================");
		printf("\n========================================");
		printf("\n1) Registrar Ventas");
		printf("\n2) Cantidad total de ventas por mes.");
		printf("\n3) Contar ventas de Contado/Cred de un mes.");
		printf("\n4) Ventas mensual por vendedor.");
		printf("\n5) Listar Datos.");
		printf("\n6) Modificar Forma de Venta.");
		printf("\n7) Borrado Logico.");
		printf("\n8) Listar Borrado Logico.");
		printf("\n9) Borrado Fisico.");
		printf("\n10) Ordenar por Nro de factura.");
		printf("\n0) Salir del programa.");
		printf("\n========================================");
		printf("\n========================================");
		printf("\nOpcion: ");
		gotoxy(70,1);
		printf("************\n");
		gotoxy(70,2);
		printf("******  T.**\n");
		gotoxy(70,3);
		printf("***  A.**  *\n");
		gotoxy(70,4);
		printf("* C.**  *  *\n");
		gotoxy(70,5);
		printf(" **  *  * *\n");
		gotoxy(70,6);
		printf("  *  *  **\n");
		gotoxy(70,7);
		printf("    ***\n");
		gotoxy(0,17);
		scanf("%d",&option);
		
		system("cls");
		switch(option)
		{
			case 1:
				{
					cargarDatosVendedores(arch,vendedores,cont);
					break;					
				}
			case 2:
				{
					ventasMensuales(arch,vendedores);
					getch();
					system("cls");
					break;	
				}
			case 3:
				{
					contarVentas(arch,vendedores);
					getch();
					system("cls");
					break;
				}
			case 4:
				{
					ventasVendedor(arch,vendedores);
					getch();
					system("cls");
					break;
				}
			case 5:
				{
					listarVendedoresf(arch,vendedores);
					getch();
					system("cls");
					break;
				}
			case 6:
				{
					modificarFormaVentaf(arch,vendedores);
					system("cls");
					break;
				}
			case 7:
				{
					borradoLogico(arch,vendedores);
					system("cls");
					break;
				}
			case 8:
				{
					mostrarBorradoLogico(arch,vendedores);
					system("cls");
					break;
				}
			case 9:
				{
					borradoFisicof(arch,vendedores);
					system("cls");
					break;
				}		
			case 10:
				{
					ordenarPorFacturaf(arch,vendedores);
					listarVendedoresf(arch,vendedores);
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
	fclose(cont);
		
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

void cargarDatosVendedores(FILE*arch, registro vendedores,FILE*cont)
{
	float vendedor, dif;
	int vendedorInt, contador=0;
	cadena nombre;
	int comparar, compararVentaNueva;
	bool b=false;
	
	rewind(cont);
	do
	{
		fread(&contador,sizeof(int),1,cont);
	}while(!feof(cont));
	
	if(contador<3)
	{
		do
		{
			do
			{
				gotoxy(13,0);
				printf("Carga de Datos");
				printf("\n========================================");
				printf("\n========================================");
				printf("\nIngrese numero de vendedor (1, 2 o 3): ");
				scanf("%f",&vendedor);
				vendedorInt=trunc(vendedor);
				dif=vendedor-vendedorInt;
				if(dif!=0 || vendedorInt<1 || vendedorInt>3)
				{
					printf("\nEL valor ingresado no es correcto");
					getch();
					system("cls");
				}
			}while(dif!=0 || vendedorInt<1 || vendedorInt>3);
			vendedores.numero=vendedorInt;
			printf("\nIngrese Apellido y Nombre de vendedor: ");
			_flushall();
			gets(vendedores.apeNom);
			printf("\nIngrese Numero de factura: ");
			scanf("%d",&vendedores.factura);
			printf("\nIngrese monto de la venta: ");
			scanf("%f",&vendedores.venta);
			do
			{
				printf("\nIngrese forma de venta (1 contado/2 credito): ");
				scanf("%d",&vendedores.formaVenta);
				if(vendedores.formaVenta>2 || vendedores.formaVenta<1)
				{
					printf("\nEl valor ingresado es incorrecto");
					printf("\nIngrese forma de venta (1 contado/2 credito): ");
					scanf("%d",&vendedores.formaVenta);
				}
			}
			while(vendedores.formaVenta>2 || vendedores.formaVenta<1);
			
			printf("\nIngrese fecha de la venta dd/mm/aaaa");
			printf("\nDia: ");
			scanf("%d",&vendedores.fechaVenta.dia);
			printf("Mes: ");
			scanf("%d",&vendedores.fechaVenta.mes);
			printf("Anio: ");
			scanf("%d",&vendedores.fechaVenta.anio);
			vendedores.borrado=false;
			fwrite(&vendedores,sizeof(registro),1,arch);
			system("cls");
			contador++;
			fseek(cont,sizeof(contador),2);
			fwrite(&contador,sizeof(int),1,cont);
		}while(contador<3);	
	}
	else
	{
		fclose(arch);
		fopen("vendedores.dat","a+b");
		gotoxy(13,0);
		printf("Nueva Venta");
		printf("\n========================================");
		printf("\n========================================\n");
		printf("Ingrese el Apellido y Nombre del vendedor: ");
		_flushall();
		gets(nombre);
		rewind(arch);
		
		while(!feof(arch)&& b==false)
		{
			fread(&vendedores,sizeof(registro),1,arch);
			compararVentaNueva=strcmp(nombre,vendedores.apeNom);
			if(compararVentaNueva==0)
			{
				b=true;			
			}	
		}
		if(b==true)
		{
			printf("\nIngrese Numero de factura: ");
				scanf("%d",&vendedores.factura);
				printf("\nIngrese monto de la venta: ");
				scanf("%f",&vendedores.venta);
				do
				{
					printf("\nIngrese forma de venta (1 contado/2 credito): ");
					scanf("%d",&vendedores.formaVenta);
					if(vendedores.formaVenta>2 || vendedores.formaVenta<1)
					{
						printf("\nEl valor ingresado es incorrecto");
						printf("\nIngrese forma de venta (1 contado/2 credito): ");
						scanf("%d",&vendedores.formaVenta);
					}
				}
				while(vendedores.formaVenta>2 || vendedores.formaVenta<1);
				printf("\nIngrese fecha de la venta dd/mm/aaaa");
				printf("\nDia: ");
				scanf("%d",&vendedores.fechaVenta.dia);
				printf("Mes: ");
				scanf("%d",&vendedores.fechaVenta.mes);
				printf("Anio: ");
				scanf("%d",&vendedores.fechaVenta.anio);
				vendedores.borrado=false;
				fseek(arch,sizeof(registro),2);
				fwrite(&vendedores,sizeof(registro),1,arch);
				getch();
				system("cls");
		}
		if(b==false)
		{
			printf("\nEl nombre del vendedor no se encontro");
			getch();
		}
		fclose(arch);
		fopen("vendedores.dat","r+b");			
	}
	system("cls");		
}

void ventasMensuales(FILE*arch, registro vendedores)
{
	float ventas=0;
	int mes,anio,b=0,i=1;
	rewind(arch);
	gotoxy(10,0);
	printf("Monto Ventas Mensual");
	printf("\n========================================");
	printf("\n========================================\n");
	printf("Ingrese el mes: ");
	scanf("%d",&mes);
	printf("Ingrese el anio: ");
	scanf("%d",&anio);
	
	while(!feof(arch))
	{
		fread(&vendedores,sizeof(registro),1,arch);
		if(mes==vendedores.fechaVenta.mes && anio==vendedores.fechaVenta.anio)
		{
			if(!feof(arch))
			ventas=ventas+vendedores.venta;
			b=1;
		}
		i++;
		
	}
	if(b==1)
	{
		printf("\nEl total de ventas del %02d/%d es: $ %010.2f",mes,anio,ventas);
	}
	if(b==0)printf("\nNo hubo ventas en el mes ingresado");
}

void contarVentas(FILE*arch, registro vendedores)
{
	int ventasCont=0,ventasCred=0;
	int mes,anio,b=0;
	rewind(arch);
	gotoxy(6,0);
	printf("Cantidad de Ventas Mensual");
	printf("\n========================================");
	printf("\n========================================\n");
	printf("Ingrese el mes: ");
	scanf("%d",&mes);
	printf("Ingrese el anio: ");
	scanf("%d",&anio);
	while(!feof(arch))
	{
		fread(&vendedores,sizeof(registro),1,arch);
		if(mes==vendedores.fechaVenta.mes && anio==vendedores.fechaVenta.anio)
		{
			if(!feof(arch))
			{
				if(vendedores.formaVenta==1)ventasCont++;
				if(vendedores.formaVenta==2)ventasCred++;
			}
			
			b=1;
		}
		
	}
	if(b==1)
	{
		printf("\nLa cantidad de ventas de contado del %02d/%d es: %d",mes,anio,ventasCont);
		printf("\nLa cantidad de ventas en credito del %02d/%d es: %d",mes,anio,ventasCred);
	}
	if(b==0)printf("\nNo hubo ventas en el mes ingresado");
}

void ventasVendedor(FILE*arch, registro vendedores)
{
	cadena vendedor;
	int mes,anio, comparar;
	float ventas=0.0;
	bool b,bandMes,bandAnio;
	
	rewind(arch);
	gotoxy(4,0);
	printf("Monto Ventas Mensual por vendedor");
	printf("\n========================================");
	printf("\n========================================\n");
	printf("Ingrese el nombre del vendedor: ");
	_flushall();
	gets(vendedor);
	printf("Ingrese el mes: ");
	scanf("%d",&mes);
	printf("Ingrese el anio: ");
	scanf("%d",&anio);
	while(!feof(arch))
	{
		fread(&vendedores,sizeof(registro),1,arch);
		comparar=strcmp(vendedores.apeNom,vendedor);
		if(comparar==0 && vendedores.fechaVenta.mes==mes && vendedores.fechaVenta.anio==anio)
		{
			if(!feof(arch))
			{
				ventas=ventas+vendedores.venta;
			}
			b=true;
			bandMes=true;
		} 
					
	}
	if(bandMes!=true)
	{
		printf("\nEl vendedor no tiene ventas en el mes %d anio %d",mes,anio);
	}
	if(b!=true)
	{
		printf("\n\nEl nombre ingresado no es correcto.");
	}
	if(b==true && bandMes==true)
	{
		printf("\nEl monto de ventas del mes %02d/%d del vendedor %s es: $ %010.2f",mes,anio,vendedor,ventas);	
	}
}
void listarVendedoresf(FILE*arch,registro vendedores)
{
	int x=0,y=0;
	
	rewind(arch);
	gotoxy(0,0);
	printf("Nro vendedor");
	gotoxy(17,0);
	printf("Vendedor");
	gotoxy(35,0);
	printf("Nro de factura");
	gotoxy(54,0);
	printf("Monto Venta");
	gotoxy(69,0);
	printf("Forma de Venta");
	gotoxy(88,0);
	printf("Fecha de venta");			
	printf("\n==============================================================================================================\n");
	printf("==============================================================================================================\n");
	y=2;
	fread(&vendedores,sizeof(registro),1,arch);
	while(!feof(arch))
	{
		
		if(!feof(arch) && vendedores.borrado==false)
		{
			y++;
			gotoxy(0,y);
			printf("%d",vendedores.numero);
			gotoxy(17,y);
			printf("%s",vendedores.apeNom);
			gotoxy(35,y);
			printf("%d",vendedores.factura);
			gotoxy(54,y);
			printf("$ %010.2f",vendedores.venta);
			gotoxy(69,y);
			if(vendedores.formaVenta==1)printf("Contado");
			if(vendedores.formaVenta==2)printf("Credito");
			gotoxy(88,y);
			printf("%02d/%02d/%d",vendedores.fechaVenta.dia,vendedores.fechaVenta.mes,vendedores.fechaVenta.anio);	
		}
		fread(&vendedores,sizeof(registro),1,arch);
	}
	printf("\n==============================================================================================================\n");

}

void modificarFormaVentaf(FILE*arch,registro vendedores)
{
	int factura;
	bool b=false;
	gotoxy(5,0);
	printf("Modificacion de forma de venta");
	printf("\n========================================\n");
	printf("Ingrese el numero de factura: ");
	scanf("%d",&factura);
	rewind(arch);
	
	while(!feof(arch) && b==false)
	{
		fread(&vendedores,sizeof(registro),1,arch);
		if(vendedores.factura==factura)
		{
			printf("\nForma de venta actual: ");
			if(vendedores.formaVenta==1)printf("Contado (1)");
			if(vendedores.formaVenta==2)printf("Credito (2)");
			do
			{
				printf("\nIngrese la nueva forma de venta (1 contado/2 credito): ");
				scanf("%d",&vendedores.formaVenta);
				if(vendedores.formaVenta>2 || vendedores.formaVenta<1)
				{
					printf("\nEl valor ingresado es incorrecto");
					printf("\nIngrese forma de venta (1 contado/2 credito): ");
					scanf("%d",&vendedores.formaVenta);
				}
			}
			while(vendedores.formaVenta>2 || vendedores.formaVenta<1);
			fseek(arch,- sizeof(registro),SEEK_CUR);
			fwrite(&vendedores,sizeof(registro),1,arch);
			b=true;
		}
		
	}
	if(b==true)
	{
		printf("\nForma de venta modificada correctamente");
		getch();
	}
	else
	{
		printf("\nNo se realizo ningun cambio");
		getch();
	}	
}

void borradoLogico(FILE*arch,registro vendedores)
{
	int factura;
	bool b=false;
	char eleccion;
	
	gotoxy(10,0);
	printf("Baja Logica");
	printf("\n========================================\n");
	printf("Ingrese el numero de factura: ");
	scanf("%d",&factura);
	rewind(arch);
	fread(&vendedores,sizeof(registro),1,arch);	
	while(feof(arch)==0  && b==false)
	{
		
		if(!feof(arch) && vendedores.factura==factura)
		{
			printf("\nNumero de vendedor: %d",vendedores.numero);
			printf("\nVendedor : %s",vendedores.apeNom);
			printf("\nMonto de venta : %.2f",vendedores.venta);
			printf("\nNumero de factura: %d",vendedores.factura);
			printf("\nForma de venta: ");
			if(vendedores.formaVenta==1)printf("Contado (1)");
			if(vendedores.formaVenta==2)printf("Credito (2)");
			printf("\n========================================\n");
			printf("\nBorrar la venta? S/N: ");
			eleccion=getch();					
			if(eleccion=='S' || eleccion=='s')
			{
				vendedores.borrado=true;
				fseek(arch,- sizeof(registro),SEEK_CUR);
				fwrite(&vendedores,sizeof(registro),1,arch);
				printf("\nVenta Borrada Logicamente");
				b=true;
			}
			else
			{
				printf("\nNo se borro la venta");
				b=true;
			}
			
		}
		fread(&vendedores,sizeof(registro),1,arch);
			
	}
	if(b==false)printf("\nError! el numero de factura no fue encontrado");
	getch();
}

void mostrarBorradoLogico(FILE*arch,registro vendedores)
{
	int x=0,y=0;
	
	rewind(arch);
	gotoxy(0,0);
	printf("Nro vendedor");
	gotoxy(17,0);
	printf("Vendedor");
	gotoxy(30,0);
	printf("Nro de factura");
	gotoxy(49,0);
	printf("Monto Venta");
	gotoxy(65,0);
	printf("Forma de Venta");
	gotoxy(84,0);
	printf("Fecha de venta");			
	printf("\n==============================================================================================================\n");
	printf("==============================================================================================================\n");
	y=2;
	fread(&vendedores,sizeof(registro),1,arch);
	while(!feof(arch))
	{
		
		if(!feof(arch) && vendedores.numero!=0 && vendedores.borrado==true)
		{
			y++;
			gotoxy(0,y);
			printf("%d",vendedores.numero);
			gotoxy(17,y);
			printf("%s",vendedores.apeNom);
			gotoxy(30,y);
			printf("%d",vendedores.factura);
			gotoxy(49,y);
			printf("$ %010.2f",vendedores.venta);
			gotoxy(65,y);
			if(vendedores.formaVenta==1)printf("Contado");
			if(vendedores.formaVenta==2)printf("Credito");
			gotoxy(84,y);
			printf("%02d/%02d/%d",vendedores.fechaVenta.dia,vendedores.fechaVenta.mes,vendedores.fechaVenta.anio);			
		}
		fread(&vendedores,sizeof(registro),1,arch);
	}
	printf("\n==============================================================================================================\n");
	getch();
}
/*Realizar el borrado físico de los registros marcados con borrado lógico. Para ingresar a esta opción
se debe solicitar una clave de ingreso.*/
void borradoFisicof(FILE*arch,registro vendedores)
{
	FILE *aux;
	bool b=false;
	cadena clave;
	int comparar,compararBorrados;
	int salir;
	
	
	gotoxy(10,0);
	printf("Baja Fisica");
	printf("\n========================================\n");	
	do
	{
		
		printf("Para borrar fisicamente los archivos que fueron \nborrados logicamente ingrese la clave (borrar456): ");
		_flushall();
		gets(clave);
		comparar=strcmp(clave,"borrar456");
		if(comparar==0)
		{
			fclose(arch);
			aux=fopen("auxiliar.dat","w+b");
			arch = fopen("vendedores.dat","a+b");
			fread(&vendedores,sizeof(registro),1,arch);
			while(feof(arch)==0 || b==false)
			{
				
				if(!feof(arch) && vendedores.borrado==false && vendedores.numero!=0)
				{
					printf("\nNumero de vendedor: %d",vendedores.numero);
					printf("\nVendedor : %s",vendedores.apeNom);
					printf("\nMonto de venta : %.2f",vendedores.venta);
					printf("\nNumero de factura: %d",vendedores.factura);
					printf("\nForma de venta: ");
					if(vendedores.formaVenta==1)printf("Contado (1)");
					if(vendedores.formaVenta==2)printf("Credito (2)");
					printf("\nEstado :");
					if(vendedores.borrado==true)printf("True");		
					if(vendedores.borrado==false)printf("False");
					getch();
					fwrite(&vendedores,sizeof(registro),1,aux);
					b=true;
				}
				fread(&vendedores,sizeof(registro),1,arch);
			}
			
		}
		else
		{
			printf("\nLa clave no es correcta");
			salir=1;			
		}		
	}
	while(comparar!=0 && salir!=1);
	if(b==true)
	{
		fclose(aux);
		fclose(arch);
		remove("vendedores.dat");
		printf("\nBorrado vendedores.dat");
		getch();
		rename("auxiliar.dat","vendedores.dat");
		printf("\nRenombrado auxiliar.dat por vendedores.dat");
		getch();
		printf("\nBorrado Exitoso!");
		
	}
	else
	{
		printf("\n\nNo se realizo el borrado");
	}	
	arch = fopen("vendedores.dat","r+b");
	getch();
}

void ordenarPorFacturaf(FILE*arch,registro vendedores)
{
	
	bool b=false;

	int comparar;
	int i=0,n;
	registro array[100], aux;
	
	gotoxy(10,0);
	printf("Ordenado por factura");
	printf("\n========================================\n");	
	fclose(arch);

	arch = fopen("vendedores.dat","r+b");
	fread(&vendedores,sizeof(registro),1,arch);
	//pasar los registros al array aux.
	while(feof(arch)==0)
	{
		array[i]=vendedores;
       	i++;
    	fread(&vendedores,sizeof(registro),1,arch);
	}
	n=i;
	//ordenar los registros en el array

	for (int j=0;j<n-1;j++)
	{
		for (i=0;i<n-1;i++)
		{
			if (array[i].factura>array[i+1].factura)
		    {
		    	aux=array[i];
	            array[i]=array[i+1];
	            array[i+1]=aux;
	            b=true;
			}
			else
			{
				b=false;
			}
		}
    }
    
    fclose(arch);
    //pasar los registros del array al archivo
	arch = fopen("vendedores.dat","w+b");
	for (i=0;i<n;i++)
    {     
       vendedores=array[i];
       fwrite(&vendedores,sizeof(registro),1,arch);           
    }  
    fclose(arch);    
  
    printf("\nYa se encuentra ordenado");
    printf("\nPara continuar y mostrar ordenado presione cualquier tecla... ");
    getch();
    system("cls");
    arch=fopen("vendedores.dat","r+b"); 
    
}
