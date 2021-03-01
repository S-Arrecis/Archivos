
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const char *nombre_archivo = "archivo.dat";
const char *nombre2 = "temporal.dat";

struct Estudiante{

	int codigo;

	char nombres[50];

	char apellidos[50];

	int telefono;

};

void ingresar();
void menu();
void abrir();
void buscar_id();
void buscar_codigo();
void eliminar();
void modificar_estudiante();

main(){
    system("title Steven Arrecis");
	menu();
}

void menu(){
    system("cls");
    int opc;
    do{
        cout<<"\n\t\t.:BIENVENIDO:.\n\n"<<endl;
        cout<<"\n1. Ingresar."<<endl;
        cout<<"2. Ver Registros."<<endl;
        cout<<"3. Buscar Codigo."<<endl;
        cout<<"4. Eliminar."<<endl;
        cout<<"5. Editar Dato."<<endl;
        cout<<"6. Salir."<<endl;
        cout<<"Digite una opcion: ";
        cin>>opc;

        switch(opc){
            case 1: ingresar(); break;
            case 2: abrir(); break;
            case 3: buscar_codigo(); break;
            case 4: eliminar(); break;
            case 5: modificar_estudiante(); break;
            case 6: exit(1); break;
        }

    }while(opc !=5);

}

void abrir(){

	system("cls");

    cout<<"\n\t\t\t.:REGISTROS:.\n\n"<<endl;

	FILE* archivo = fopen(nombre_archivo,"rb");

	if (!archivo){

		archivo = fopen(nombre_archivo,"w+b");

	}

	Estudiante estudiante;

	int id= 0;

	fread(&estudiante,sizeof(Estudiante),1,archivo);

	cout<<"id |"<<"Codigo |"<<"Nombres   |"<<"Apellidos   |"<<"Telefono"<<endl;

	do{

	cout<<id<<" |"<<estudiante.codigo<<" |"<<estudiante.nombres<<"  |"<<estudiante.apellidos<<"  |"<<estudiante.telefono<<endl;

	fread(&estudiante,sizeof(Estudiante),1,archivo);

		id+=1;

	} while(feof(archivo) ==0);

	fclose(archivo);

    cout<<"\n\n";
    system("pause");
    menu();

}



void ingresar(){
    system("cls");
	char continuar;
    cout<<"\n\t\t\t.:Agregando Datos\n\n"<<endl;

	FILE* archivo = fopen(nombre_archivo,"ab");

	Estudiante estudiante;

	string nombre,apellido;

	do{

		fflush(stdin);

		cout<<"Ingrese el Codigo:";

		cin>>estudiante.codigo;

		cin.ignore();

		

		cout<<"Ingrese Los Nombres: ";

		getline(cin,nombre);

		strcpy(estudiante.nombres,nombre.c_str());

		cout<<"Ingrese Los Apellidos: ";

		getline(cin,apellido);

		strcpy(estudiante.apellidos,apellido.c_str());

		cout<<"Ingrese el Telefono:";

		cin>>estudiante.telefono;

		fwrite(&estudiante,sizeof(Estudiante),1,archivo);

		cout<<"Desea ingresar otro dato (s/n):";

		cin>>continuar;

	} while (continuar=='s' || continuar=='S');

	fclose(archivo);

	cout<<"\n\n\t\t\tDATOS AGREGADOS...\n\n";
    system("pause");
    menu();

}




void buscar_id(){

	FILE* archivo = fopen(nombre_archivo,"rb");	

	int id;

	cout<<"Ingrese el ID que desea ver: ";

	cin>>id;

	fseek(archivo,id*sizeof(Estudiante),SEEK_SET);

	Estudiante estudiante;

	fread(&estudiante,sizeof(Estudiante),1,archivo);

	cout<<"Codigo: "<<estudiante.codigo<<endl;

	cout<<"Nombres: "<<estudiante.nombres<<endl;

	cout<<"Apellidos: "<<estudiante.apellidos<<endl;

	cout<<"Telefono: "<<estudiante.telefono<<endl;

	fclose(archivo);

}




void buscar_codigo(){

    system("cls");
    cout<<"\n\t\t\t.: Buscar Persona:.\n\n"<<endl;

	FILE* archivo = fopen(nombre_archivo,"rb");	

	int codigo;

	cout<<"Ingrese el Codigo: ";

	cin>>codigo;

	

	Estudiante estudiante;

	fread(&estudiante,sizeof(Estudiante),1,archivo);

	do{

		if(estudiante.codigo == codigo){

			cout<<"______________________"<<endl;

			cout<<"Codigo: "<<estudiante.codigo<<endl;

			cout<<"Nombres: "<<estudiante.nombres<<endl;

			cout<<"Apellidos: "<<estudiante.apellidos<<endl;

			cout<<"Telefono: "<<estudiante.telefono<<endl;

		}

		fread(&estudiante,sizeof(Estudiante),1,archivo);

	} while (feof(archivo)==0);

	

	

	fclose(archivo);

    cout<<"\n\n";
    system("pause");
    menu();

}

void modificar_estudiante(){
	
	FILE* archivo = fopen(nombre_archivo, "r+b");
	
		int id;
		string nombre,apellido;	
    	Estudiante estudiante;
        
    
		cout <<"\n\nIngrese el ID que desea Modificar: ";
    		cin >> id;
    		fseek ( archivo, id * sizeof(Estudiante), SEEK_SET );  // esto es lo que permite modificar en la pocision
	
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(estudiante.nombres, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(estudiante.apellidos, apellido.c_str()); 
		
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		
		fwrite( &estudiante, sizeof(Estudiante), 1, archivo );
		
	fclose(archivo);
		system("PAUSE");
}


void eliminar(){
    system("cls");
    cout<<"\n\t\t.:Eliminar Registro:.\n"<<endl;
	FILE* archivo = fopen(nombre_archivo,"rb");
    FILE* archivo2 = fopen(nombre2,"w+b");
	if (!archivo){

		archivo = fopen(nombre_archivo,"w+b");

	}

	int id= 0, codigo;
    string nombre,apellido;

	cout<<"Ingrese el Codigo para eliminar: ";

	cin>>codigo;

	Estudiante estudiante;

	fread(&estudiante,sizeof(Estudiante),1,archivo);

	do{
        
		if(estudiante.codigo == codigo){
            cout<<"Datos eliminados..\n\n"<<endl;
            system("pause");
            fread(&estudiante,sizeof(Estudiante),1,archivo);
        }

        else{
            
            fwrite(&estudiante,sizeof(Estudiante),1,archivo2);
            fread(&estudiante,sizeof(Estudiante),1,archivo);
            id+=1;
        }

	} while (feof(archivo)==0);

	fclose(archivo);
    fclose(archivo2);
    remove("archivo.dat");
    rename("temporal.dat","archivo.dat");

    cout<<"\n\n";
    system("pause");
    menu();
    

}