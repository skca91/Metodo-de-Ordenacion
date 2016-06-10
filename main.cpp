//---------------------------------------------------------------------------


#include <stdio.h>
#include<iostream>
using namespace std;
#include "conio.h"
#include "stdlib.h"
//---------------------------------------------------------------------------
/*Stephanie Correa 19598574
  Yohan Villamizar 17876465*/
#pragma argsused
///////////////////////////////////////////////////////////........DATA
class data{
	public:
		int tipoVehiculo;
                float pesoPromedio;
		data(){ suc=NULL; pre=NULL;
                }
                data *suc, *pre;
};
//////////////////////////////////////////////////////////.......PESOS
class pesos{
        public:
                pesos(){suc=NULL; pre=NULL;}
                char placaVehiculo[7];
                int tipoVehiculo;
                float pesoBruto;
                pesos *suc, *pre;
};
////////////////////////////////////////////////////////.........LISTA
class lista{
        public:
                lista(){cab=NULL; cabe = NULL;}
                void insercionData(data);
                void insercionPesos(pesos);
                void imprimirData();
                void imprimirPesos();
                void imprimirPromedios();
                void eliminarPesos(pesos *);
                data *cab;
                pesos *cabe;
};

void lista::insercionPesos(pesos pes){
        pesos *nuevo, *antes, *recor;
        int enc = 0;
        nuevo = new pesos;
        if(nuevo)
        {
                (*nuevo)=pes;
                recor = cabe;
                antes = NULL;
                while (recor&&!enc)
                {
                        if (recor->pesoBruto<nuevo->pesoBruto)
                        {
                                enc = 1;
                        }else{
                                antes = recor;
                                recor = recor->suc;
                        }
                }
                nuevo->pre = antes;
                nuevo->suc = recor;
                if (recor)
                        recor->pre = nuevo;
                if (antes)
                        antes->suc = nuevo;
                else
                        cabe = nuevo;
        }
        else
                cout<<"NO HAY MEMORIA";
}

void lista::eliminarPesos(pesos *pes)
{
        pesos *antes, *recor, *aux;
        recor = cabe;
        if(recor)
        {
                antes = NULL;
                while (recor)
                {
                        if (strcmpi(pes->placaVehiculo,recor->placaVehiculo)==0)
                        {
                                aux = recor;
                                recor = recor->suc;
                                aux->suc = NULL;
                                if(antes==NULL)
                                        recor->pre = NULL;

                                if(antes!=NULL){
                                        aux->pre = NULL;
                                        if(recor==NULL)
                                                antes->suc = NULL;
                                        else{
                                                recor->pre = antes;
                                                antes->suc = recor;
                                        }
                                }
                                delete(aux);
                                break;
                        }else{
                                antes = recor;
                                recor = recor->suc;
                        }
                }
        }
        else
                cout<<"NO HAY MEMORIA";
}

void lista::insercionData(data dat)
{
        data *nuevo, *antes, *recor;
        int enc = 0;
        nuevo = new data;
        if(nuevo)
        {
                (*nuevo)=dat;
                recor = cab;
                antes = NULL;
                while (recor&&!enc)
                {
                        if (recor->tipoVehiculo<nuevo->tipoVehiculo)
                                enc=1;
                        else{
                                antes = recor;
                                recor = recor->suc;
                        }
                }
                nuevo->pre = antes;
                nuevo->suc = recor;
                if (recor)
                        recor->pre = nuevo;
                if (antes)
                        antes->suc = nuevo;
                else
                        cab = nuevo;
        }
        else
                cout<<"NO HAY MEMORIA";
};

void lista::imprimirData()
{
        data *record;
        record = cab;
        while (record)
        {
                cout<<record->tipoVehiculo<<" "<<record->pesoPromedio<<endl;
                record = record->suc;
        }
}

void lista::imprimirPesos(){
        pesos *recor;
        recor = cabe;
        while (recor)
        {
                cout<<recor->placaVehiculo<<" "<<recor->tipoVehiculo<<" "<<recor->pesoBruto<<endl;
                recor = recor->suc;
        }
}

/*void lista::imprimirPromedios()
{
        pesos *recor;
        recor = cabe;
        while (recor)
        {
                cout<<recor->
                recor = recor->suc;
        }
} */
////////////////////////////////////////////////////////////////.......ARCHIVO
class archivo{
        public:
                archivo(){}
                lista cargarData(lista);
                lista cargarPesos(lista,lista);
                data dat;
                pesos pes;
};

lista archivo::cargarData(lista lista)
{
        char cadd[150];
        char *sed;

        FILE *fpd;
        fpd=fopen("data.txt","r");

        if(!fpd){
                cout<<"error de apertura"<<endl;
                return lista;
        }
        else{
                int y=0;
                fgets(cadd,150,fpd);
                while(!feof(fpd))
                {
                        sed=strtok(cadd,",");
                        dat.tipoVehiculo=atoi(sed);
                        sed=strtok(NULL,",");
                        dat.pesoPromedio = atof(sed);
                        lista.insercionData(dat);
                        fgets(cadd,150,fpd);
                        y++;
                }//fin del while
        }//fin del else
        fclose(fpd);
        return lista;
}

lista archivo::cargarPesos(lista listado, lista lista){
        char cad[150];
        char *se;
        data *recor;
        pesos *recorp, peso;
        int enc =0;

        FILE *fp;
        fp=fopen("pesos.txt","r");

        if(!fp){
                cout<<"error de apertura pesos.txt"<<endl;
                return listado;
        }
        else{
                int y=0;
                while(!feof(fp))
                {
                        fgets(cad,150,fp);
                        se=strtok(cad,",");
                        strcpy(pes.placaVehiculo,se);
                        se=strtok(NULL,",");
                        pes.tipoVehiculo=atoi(se);
                        se=strtok(NULL,",");
                        pes.pesoBruto = atof(se);
                        recor = lista.cab;
                        while (recor)
                        {
                                if (pes.tipoVehiculo==recor->tipoVehiculo)
                                {
                                        recorp = listado.cabe;
                                        if(recorp==NULL){
                                                if(pes.pesoBruto>recor->pesoPromedio){
                                                        listado.insercionPesos(pes);
                                                        break;
                                                }
                                        }
                                        else{
                                                while (recorp)
                                                {
                                                        if (strcmpi(recorp->placaVehiculo,pes.placaVehiculo)==0)
                                                        {
                                                                if (pes.pesoBruto>recorp->pesoBruto)
                                                                {
                                                                        listado.eliminarPesos(recorp);
                                                                        listado.insercionPesos(pes);
                                                                }
                                                                enc = 1;
                                                                break;
                                                        }
                                                        recorp = recorp->suc;
                                                }
                                                if(recorp==NULL){
                                                        if(pes.pesoBruto>recor->pesoPromedio)
                                                                listado.insercionPesos(pes);
                                                        enc = 1;
                                                }
                                        }
                                }
                                if(enc == 1){
                                        enc = 0;
                                        break;
                                }else
                                recor=recor->suc;
                        }
                        y++;
                }//fin del while
        }//fin del else
        fclose(fp);
        return listado;
}

///////////////////////////////////////////////////////////////.......MAIN
int Menu()
{
	int opc;
	cout<<"---------------MENU DE OPCIONES------------------"<<endl;
	cout<<"1-.GENERAR LA ESTRUCTURA DE DATOS DE REFERENCIA"<<endl;
	cout<<"2-.GENERAR LA ESTRUCTURA DE DATOS RESUMEN"<<endl;
	cout<<"3-.PROMEDIO DE PESOS"<<endl;
	cout<<"4-.MOSTRAR ESTRUCTURA DE REFERENCIA Y ESTRUCTURA DE RESUMEN"<<endl;
	cout<<"5-.SALIR"<<endl;
	cin>>opc;
	return opc;
}

int main(int argc, char* argv[])
{
        archivo arch;
        lista lista, listado;

        int n;
	n = Menu();


	while(n!=5){

		switch (n)
		{
		case 1: system("cls");
                        cout<<"LISTA DE DATOS GENERADO"<<endl;
                        lista = arch.cargarData(lista);
			getch();
			break;
		case 2:
			system("cls");
                        cout<<"LISTA DE PESOS GENERADO"<<endl;
                        listado = arch.cargarPesos(listado, lista);
			getch();
			break;
		case 3:
			system("cls");
                        cout<<"PESOS PROMEDIOS"<<endl;

			getch();
			break;
		case 4:
			system("cls");
                        cout<<"DATA: "<<endl;
                        lista.imprimirData();
                        cout<<"\nPESOS: "<<endl;
                        listado.imprimirPesos();
			getch();
			break;
        case 5:
			system("cls");
                        cout<<"Hasta luego =D"<<endl;
			break;	
		default: cout<<"Opcion incorrecta"<<endl;
		}
		system("cls");
        		n = Menu();
	}
        getch();
 

        return 0;
}
//---------------------------------------------------------------------------

 
