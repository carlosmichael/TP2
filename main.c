#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
//#include "misFunciones.h"

#define A 10
typedef struct
{
	int id;
	char apellido[51];
	char nombre[51];
	float salario;
	int sector;
}empleado;


char menu(void);
void alta(empleado*);
void listar(empleado*);
void modificar(empleado*);
void baja(empleado*);
void mayorSalario(empleado*);
int buscaId(empleado*, int leg);
int buscarLibre(empleado*);
void toString(empleado*);
int guardarEnArchivo(empleado *);
int cargarDesdeArchivo(empleado *);
void crearTxt(empleado *);


int main()
{
	empleado empleados[A];
	char seguir='s';
	char guardar= 's';
	int i;

		for( i=0; i<A; i++)
		empleados[i].id=0;

	if(cargarDesdeArchivo(empleados))
	{
		printf("No se pudo abrir el fichero");
	}
	else
	{
		printf("Se cargaron las estructuras con exito\n");
	}

	system("pause");


	system("cls");
	do
	{
		switch(menu())
		{
			case '1':
				system("cls");
				alta(empleados);
				break;
			case '2':
				system("cls");
				listar(empleados);
				break;
			case '3':
				system("cls");
				baja(empleados);
				break;
			case '4':
				system("cls");
				modificar(empleados);
				break;
			case '5':
				system("cls");
				mayorSalario(empleados);
				break;
			case '6':
                system("cls");
                crearTxt(empleados);
                break;
			case '7':

				printf("\nGuardar cambios S/N ?: ");
				guardar = tolower(getche());

				if(guardar == 's')
				{
					if(guardarEnArchivo(empleados))
					{
						printf("\nNo se pudo abrir el fichero\n");
					}
					else
					{
						printf("\nSe guardo la informacion con exito\n");
					}
				}

				seguir='n';
				break;

		}
	}while(seguir=='s');
	printf("\n");
	system("pause");
}
//Desarrollo de Funciones//

char menu()
{       char c;
	system("cls");
	printf("***Menu de Opciones***\n1. Alta de Empleado\n2. Listar a los Empleados\n3. Dar de baja a un empleado\n4. Modificar un Empleado\n5. MAYOR SALARIO\n6. LISTADO DE EMPLEADOS\n7. Salir\n");
	printf("Elija una opcion: ");
	c=getche();
	return c;
}

int buscarLibre(empleado losEmpleados[])
{
	int index=-1;
	int i;
	for( i=0; i < A; i++)
	   if(losEmpleados[i].id==0){
		index=i;
		break;
	   }
	return index;
}

void alta(empleado losEmpleados[])
{
	int index, i, sector;
	float salario;
	int id;
	int encontro=0;
	/*Buscamos cual es el primer indice libre dentro del array*/
	index=buscarLibre(losEmpleados);
	if(index!=-1)//si hay lugar:
	{
		printf("INGRESO DE DATOS:\n");
		/*Buscamos si el id ya existe*/


			losEmpleados[index].id=index+1;
			printf("Ingrese apellido: ");
			fflush(stdin);
			gets(losEmpleados[index].apellido);
			printf("Ingrese nombre: ");
			fflush(stdin);
			gets(losEmpleados[index].nombre);
			printf("Ingrese salario: ");
			scanf("%f", &salario);
			losEmpleados[index].salario=salario;
			printf("Ingrese sector: ");
			scanf("%d", &sector);
			losEmpleados[index].sector=sector;
			system("cls");
	}
	else
	{
		printf("No queda espacio");
		getch();
	}
}

void toString(empleado* unEmpleado)
{
	printf("%d\t\t%s\t\t%s\t\t%.2f\t%d\t\n", unEmpleado->id, unEmpleado->apellido, unEmpleado->nombre, unEmpleado->salario, unEmpleado->sector);
}

void listar(empleado *losEmpleados)
{
	int i,j;
	empleado auxEmpleado;

	for(i=0; i<A-1;i++)
	{
		for(j=i+1; j<A; j++)
		{
			if(strcmp(losEmpleados[i].apellido,losEmpleados[j].apellido)>0)
			{
				auxEmpleado=losEmpleados[i];
				losEmpleados[i]=losEmpleados[j];
				losEmpleados[j]=auxEmpleado;
			}
			else if (strcmp(losEmpleados[i].apellido,losEmpleados[j].apellido)==0 && losEmpleados[i].sector > losEmpleados[j].sector)
            {
                auxEmpleado=losEmpleados[i];
				losEmpleados[i]=losEmpleados[j];
				losEmpleados[j]=auxEmpleado;
            }
		}
	}

	printf("Id\tApellido\tNombre\t\tSalario\t\tSector\n");
	for(i=0; i<A; i++)
	{
		if(losEmpleados[i].id!=0)
		   toString((losEmpleados + i));

	}
	getch();
}
void baja(empleado* losEmpleados)
{
	int id, flag=0,i;
	char opcion;
	printf("Ingrese id a dar de baja: ");
	scanf("%d", &id);
	for(i=0; i<A; i++)
	{
		if(id==losEmpleados[i].id)
		{
			printf("Datos a eliminar:\n");

			toString((losEmpleados + i));

			printf("\nId encontrado. ¨Seguro desea dar de baja?");
			opcion=getche();
			if(opcion=='s')
			{
				losEmpleados[i].id=0;
				printf("­­Registro eliminado!!");
			}
			else
			{
				printf("El registro no fue eliminado!");
			}
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		printf("Id inexistente");
		getch();
	}
}
void modificar(empleado* losEmpleados)
{
	int id, flag=0,i, sector;
	float salario;
	char opcion;
	system("cls");
	printf("Ingrese id a modificar: ");
	scanf("%d",& id);
	for( i=0; i<A; i++)
	{
		if(id==losEmpleados[i].id)
		{
			printf("Datos encontrados:\n");

			toString((losEmpleados + i));

			printf("\nIngrese el nuevo salario: ");
			scanf("%f", &salario);
			printf("\nIngrese el nuevo sector: ");
			scanf("%f", &sector);
			printf("¿Esta seguro que desea modificar? (s) ");
			opcion=getche();
			if(opcion=='s')
			{
				losEmpleados[i].salario=salario;
				losEmpleados[i].sector=sector;
				printf("Registro modificado");
			}
			else
			{
				printf("El registro no fue modificado");
			}
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		printf("Id inexistente");
		getch();
	}
}
void mayorSalario(empleado* losEmpleados)
{
	int i, flag=0;
	float maxSal;
	for(i=0; i<A; i++)
	{
		if(losEmpleados[i].id!=0)
		  if(flag==0 || losEmpleados[i].salario>maxSal)
		  {
			maxSal=losEmpleados[i].salario;
			flag=1;
		  }
	}
	printf("El o los Empleados con mayor salario (%.2f) son:\n", maxSal);
	for(i=0; i<A; i++)
	{
		if(losEmpleados[i].id!=0)
		  if(losEmpleados[i].salario==maxSal)
		  {

			toString((losEmpleados + i));
		  }
	}
	getch();
}

int guardarEnArchivo(empleado * x)
{

	FILE *f;

		f=fopen("bin.dat","wb");
		if(f == NULL)
		{
			return 1;
		}

	fwrite(x,sizeof(empleado),A,f);

	fclose(f);

	return 0;
}

int cargarDesdeArchivo(empleado *x)
{
	int flag = 0;
	FILE *f;

	f=fopen("bin.dat", "rb");
	if(f==NULL)
	{
		f= fopen("bin.dat", "wb");
		if(f==NULL)
		{
			return 1;
		}

		flag=1;

	}

	if(flag ==0)
	{
	fread(x,sizeof(empleado),A,f);
    }

	fclose(f);
	return 0;

}

void crearTxt(empleado *x)
{
     int i;
     FILE *f;
     f=fopen("Lista de Precios.txt", "w");

     if(f == NULL)
     {
          printf("No se pudo abrir el archivo\n");
     }
     else
     {
         fprintf(f,"Listado de Empleados\n\n\n");
         fprintf(f,"Id    Nombre     Salario \n");

         for(i=0; i<A; i++)
         {
                  if(x[i].id != 0)
                  {
                  fprintf(f,"%d\t\%s %s\t\%.2f\n", x[i].id, x[i].apellido, x[i].nombre, x[i].salario);
                  }
         }
      }

      fclose(f);

      printf("Listado creado con exito\n");
      system("pause");
}
