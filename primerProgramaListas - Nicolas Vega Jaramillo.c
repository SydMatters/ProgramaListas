#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#define CLS system("cls");
#define PAUSE system("pause");
#define NUM_EMP 5
#define FLUSH fflush(stdin);
struct datosEmpresa{
    char empresa[50];
    char cargo[25];
    char retiro[5];
    short ageLab;
};

typedef struct datosPersona{
    char id [11];
    char name [50];
    char fijo [10];
    char cel [12];
    struct datosEmpresa emp [NUM_EMP];
    short age;
    struct datosPersona *sigPer;
}persona;

persona *head = NULL;

char menu ();
void salir();
short cantidadNod ();
void newNod();
void listaList();
void intercambioNod();
void edades();
void eliminar ();

int main()
{
    setlocale(LC_ALL,"");
    char op;
    do
    {
        op = menu();
        switch (op)
        {
        case 'a':
            CLS
            newNod();
            PAUSE
            CLS
            break;
        case 'b':
            CLS
            intercambioNod();
            PAUSE;
            CLS;
            break;
        case 'c':
            CLS
            edades();
            PAUSE
            CLS
            break;
        case 'd':
            CLS
            eliminar();
            PAUSE
            CLS
            break;
        case 'e':
            CLS
            listaList();
            PAUSE
            CLS
            break;
        case 'f':
            CLS
            printf("%hd",cantidadNod());
            PAUSE
            CLS
            break;
        case 'z':
            CLS
            salir();
            PAUSE
            CLS
            break;
        default:
            printf("OPCION NO VALIDA!!!");
            PAUSE
            CLS
            break;

        }
    }while(op != 'z');
    return 0;
}

char menu ()
{
    char resp;
    printf("------------------------------------------\n");
    printf("------------Datos Personales en Lista------\n");
    printf("------------------------------------------\n\n");
    printf("\na) Ingresar una persona a la lista.");
    printf("\nb) Intercambio de dos personas de la lista.");
    printf("\nc) Indicaciones de edades.");
    printf("\nd) Eliminar a una persona de la lista");
    printf("\nz) Salir.");
    printf("\n\nA continuación digite la opción deseada:  ");
    scanf("%c",&resp);

    return resp;
    FLUSH;
}
void salir()
{
    CLS;
    printf("*********************************************************");
    printf("\n*                                                       *");
    printf("\n*                     VUELVA PRONTO                     *");
    printf("\n*                                                       *\n");
    printf("*********************************************************\n");
}

short cantidadNod ()
{
    if(head == NULL)
        return 0;
    else
    {
        short cant = 0;
        persona *tmp = head;
        while (tmp != NULL)
        {
            cant++;
            tmp = tmp->sigPer;
        }
        return cant;
    }
}

void listaList ()
{
    persona *nodoList = head;
    if(cantidadNod() != 0)
    {
        printf("-----------------------------------------------------\n");
        printf("--------------------------LISTA----------------------\n");
        printf("-----------------------------------------------------\n\n");

        while(nodoList != NULL)
        {
            printf("--------------------------------------------\n");
            printf("| %s\n",nodoList->name);
            printf("| Edad: %hd\n",nodoList->age);
            printf("| ID: %s\n",nodoList->id);
            printf("| Celular: %s\n",nodoList->cel);
            printf("| Fijo: %s\n",nodoList->fijo);
            printf("---------------DATOS LABORALES--------------\n");
            for(short i= 0; i < NUM_EMP;i++)
            {
                if(strcmp(nodoList->emp[i].empresa,"") != 0)
                {
                    printf("| Empresa No.%hd : %s\n",i+1,nodoList->emp[i].empresa);
                    printf("| Años trabajados: %hd\n",nodoList->emp[i].ageLab);
                    printf("| Cargo: %s\n",nodoList->emp[i].cargo);
                    printf("| Fecha de retiro: %s\n\n",nodoList->emp[i].retiro);
                    printf("--------------------------------------------\n");
                }
            }
            printf("--------------------------------------------\n");
            printf("--------------------------------------------\n");
            nodoList = nodoList->sigPer;
        }

    }


}
void newNod ()
{
    char o;
    short pos;
    persona *nuevoNod, *nodTmp = head;
    nuevoNod = malloc(sizeof(persona));
    FLUSH
    printf("\nDigite el id: ");gets(nuevoNod->id);FLUSH
    printf("\nDigite el nombre: ");gets(nuevoNod->name);FLUSH
    printf("\nDigite la edad: ");scanf("%hd",&(nuevoNod->age));FLUSH
    printf("\nDigite el telefono fijo: ");gets(nuevoNod->fijo);FLUSH
    printf("\nDigite el telefono celular: ");gets(nuevoNod->cel);FLUSH
    printf("\n\nAhora por favor ingrese la información laboral.\n");
    PAUSE
    CLS
    char o2;short j = 0;
    do{
        FLUSH
        printf("\nDigite el nombre de la empresa No %hd: ",j+1);gets(nuevoNod->emp[j].empresa);FLUSH
        printf("\nDigite el cargo que %s desempeñaba:  ",nuevoNod->name);gets(nuevoNod->emp[j].cargo);FLUSH
        printf("\nDigite el año en el que %s se retiró: ",nuevoNod->name);gets(nuevoNod->emp[j].retiro);FLUSH
        printf("\nDigite los años que la persona laboró en la empresa: ");scanf("%hd",&(nuevoNod->emp[j].ageLab));FLUSH

        printf("\nDesea seguir registrando datos laborales? Digite S para si y N para no.\n");FLUSH;scanf("%c",&o2);
        j++;
    }while(o2!='N' && j<NUM_EMP);
    CLS
    FLUSH
    pos = cantidadNod();
    printf("Agregar el nodo al final? Digite S para SI o N para NO.");scanf("%c",&o);
    if(o == 'N')
    {
      FLUSH
        printf("Digite la posicion en la que desea agregar el nodo: ");scanf("%hd",&pos);
        if(pos > 0 && pos <= cantidadNod + 1)
        {
            CLS
            for(short i= 1; i <= pos - 2; i++)
            {
                nodTmp = nodTmp->sigPer;
            }
            nuevoNod->sigPer = nodTmp->sigPer;
            nodTmp->sigPer = nuevoNod;
        }
        else
            printf("Posición no valida!!!");
    }
    else if (o == 'S')
    {
        if (pos == 0)
        {
            printf("\n\nEste nodo será la cabeza de la lista...\n");
            nuevoNod->sigPer = head;
            head = nuevoNod;
        }
        else
        {
            printf("\n\nEste nodo se agregará al final de la lista...\n");
            while (nodTmp->sigPer != NULL)
                nodTmp = nodTmp->sigPer;
            nuevoNod->sigPer = NULL;
            nodTmp->sigPer = nuevoNod;
        }
    }
    else
        printf("OPCION NO VALIDA!!!");

}
void intercambioNod ()
{
    FLUSH
    short pos1,pos2,op;
    persona *tempo1 = head, *tempo2 = head, *trian;
    char tempID1[11], tempID2[11];
    printf("¿Qué datos desea ingresar para realizar el intercambio?\n");
    printf("1) Posición.\n");
    printf("2) ID.\n");
    printf("Digite la opcion: ");scanf("%hd",&op);

    if(op == 1)
    {
        CLS
        FLUSH
        printf("Ingrese las posiciones que desea cambiar:\n1: ");scanf("%hd",&pos1);printf("\n2: ");scanf("%hd",&pos2);

        if(pos1 <= cantidadNod() && pos2 <= cantidadNod())
        {
            for(short i=1; i < pos1 - 1; i++)
                tempo1 = tempo1->sigPer;
            for(short i=1; i < pos1 - 1; i++)
                tempo2 = tempo2->sigPer;

            trian = tempo1;
            trian->sigPer = tempo1->sigPer;
            trian->sigPer->sigPer = tempo1->sigPer->sigPer;

            tempo1->sigPer = tempo2->sigPer;
            tempo1->sigPer->sigPer = tempo2->sigPer->sigPer;

            tempo2->sigPer = trian->sigPer;
            tempo2->sigPer->sigPer = trian->sigPer->sigPer;

        }
        else
            printf("Posiciones no validas para intercambio (No están dentro del intervalo de la cantidad de nodos)");
    }
    else if(op == 2)
    {
        printf("Ingrese los Id de los nodos que desea cambiar:\n1: ");FLUSH;gets(tempID1);FLUSH;printf("\n2: ");gets(tempID2);

        while(strcmp(tempo1->id,tempID1) != 0)
        {
            tempo1 = tempo1->sigPer;
        }

        while(strcmp(tempo2->id,tempID1) != 0)
        {
            tempo2 = tempo2->sigPer;
        }
        trian = tempo1;
        tempo1 = tempo2;
        tempo2 = trian;
    }
    else
        printf("Opcion no valida!!!");

}
void edades ()
{
    short o;
    persona *tempnNod = head;
    printf("Desea conocer la mayor o la menor de las personas?\n");
    printf("1) Mayor.\n");
    printf("2) Menor.\n");
    printf("Digite la opcion: ");scanf("%hd",&o);
    if(o == 1)
    {
        short may = tempnNod->age;

        while(tempnNod == NULL)
        {
            if(may < tempnNod->age)
                may = tempnNod->age;
            tempnNod = tempnNod->sigPer;
        }
        CLS
        printf ("La persona con mayor edad es: %s.", tempnNod->name);
    }
    else if(o == 2)
    {
        short min = tempnNod->age;

        while(tempnNod == NULL)
        {
            if(min > tempnNod->age);
                min = tempnNod->age;
            tempnNod = tempnNod->sigPer;
        }
        CLS
        printf ("La persona con menor edad es: %s.", tempnNod->name);
    }
    else
        printf("Posición no valida!!!");
}
void eliminar()
{
    short o,pos;
    char tempID[11];
    persona *tempnNod = head;
    printf("Digite que dato del nodo desea ingresar para eliminar el nodo: \n");
    printf("1) Posición.\n");
    printf("2) ID.\n");
    printf("Digite la opcion: ");scanf("%hd",&o);
    if (o == 1)
    {
        printf("Digite la posición: ");scanf("%hd",&pos);

        if(pos == 1)
            head = head->sigPer;

        else if(pos > 0 && pos <= cantidadNod + 1)
        {

            CLS
            for(short i= 1; i <= pos - 2; i++)
                tempnNod = tempnNod->sigPer;
            persona *otroNod = tempnNod->sigPer;
            tempnNod->sigPer = otroNod->sigPer;
            tempnNod = otroNod;

        }
        else
            printf("Posición no valida!!!");
    }
    else if (o == 2)
    {
        printf("Ingrese el Id del nodo que desea eliminar:\n1: ");FLUSH;gets(tempID);

        while(strcmp(tempnNod->id,tempID) != 0)
        {
            tempnNod = tempnNod->sigPer;
        }

    }
}

