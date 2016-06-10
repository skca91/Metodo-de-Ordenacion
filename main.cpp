#include <cstdlib>
#include <iostream>

using namespace std;
/*Stephanie Correa C.I 19.598.574
  seccion 2*/
  
class alumnos{
      public:
             alumnos(){}
             long ced;
             char nombre[30];
             int edad;
      };
class notas{
      public:
             notas(){}
             long ced;
             char materia[30];
             int nota;
             char periodo[10];
      };
class mejor{
      public:
             mejor(){}
             char materia[30];
             int nota;
             
      }; 
class reporte{
      public:
             reporte(){}
             
             char materia[30];
             long ced;
             char nombre[30];
             int nota;
             char periodo[10];
      }; 
                        
int main(int argc, char *argv[])
{   
    int na,nn,a,b;
    
    reporte *t;
    t=(reporte*)malloc(sizeof(reporte)*100);
    
    FILE *x,*y;
    x = fopen("Alumnos.dat","rb");
    y = fopen("Notas.dat","rb");
    
    if(!x||!y){
               cout<<"Error de apertura"<<endl;
               fclose(x);fclose(y);
               } 
      else{
           alumnos o;
           fseek(x,0,2);
           na = ftell(x)/sizeof(alumnos);
           
          // cout<<na;
           alumnos *v;
           v = new alumnos[na];
           rewind(x);
           a=0;
             
             fread(&o,sizeof(alumnos),1,x);
             while(!feof(x)){
                             v[a]=o;
                            // cout<<" "<<v[a].nombre<<endl;
                             a++;
                             fread(&o,sizeof(alumnos),1,x);
                             }
            notas g;
            fseek(y,0,2);
            nn = ftell(y)/sizeof(notas);
            //cout<<nn;                 
              notas *w;
              w = new notas[nn];
              rewind(y);
              b=0;
              
              fread(&g,sizeof(notas),1,y);
               while(!feof(y)){
                               w[b]=g;
                              //cout<<" "<<w[b].materia<<" "<<w[b].nota<<endl;
                               b++;
                               fread(&g,sizeof(notas),1,y);
                               }
                               
            fclose(x);
            fclose(y);
            
            float *vector;
            vector = new float[a];
            float acum=0,prom=0;
            int n=0,l=0,pos=0,band=0;
            
               for(int i=0;i<a;i++){
                     vector[i]=0; 
                 //cout<<"\n\tEstudiante #"<<i+1<<endl;
                 //cout<<"\n\tCedula: "<<v[i].ced<<" Nombre: "<<v[i].nombre<<" Edad: "<<v[i].edad<<endl;
                       acum=0;
                       prom=0;
                       n=0;
                       
                      for(int j=0;j<b;j++){
                               if(v[i].ced==w[j].ced){
                                     acum+=w[j].nota;
                                     pos=i;
                                     n++;
                                      } 
                                                                    
                               }
                     
                          prom=acum/n; 
                          vector[pos]=prom;
                          l=0;
                          pos=0;
                          band=0;
                          
                          while(l<b && band){
                                     if(v[i].ced!=w[l].ced){
                                          pos=i; 
                                          band=1;                 
                                                            }
                                      l++;                      
                                     }
                          
                          if(band){
                             vector[pos]=0;
                             }
                             
                       }
                       //vector de promedios
                    /*  for(int i=0;i<a;i++){
                               cout<<" "<<vector[i]<<endl;
                               }
                    */
//Mejor estudiante y peor estudiante por promedio

      float mayor=-1,menor=9.9999;
      int p,p1;
      
      for(int i=0;i<a;i++){
              
              if(vector[i] < menor){
                menor = vector[i];
                p=i;           
                           }
              if(vector[i] > mayor){
                mayor = vector[i];
                p1=i;
                 }             
              }
              cout<<"\n***************** Mejor Estudiante y Peor Estudiante ***************"<<endl;
              cout<<"\n\tEl mejor estudiante es "<<v[p1].nombre<<" Cedula: "<<v[p1].ced<<" Edad: "<<v[p1].edad<<endl;
              cout<<"\tPromedio: "<<vector[p1]<<endl; 
              cout<<"\n\tEl peor estudiante es "<<v[p].nombre<<" Cedula: "<<v[p].ced<<" Edad: "<<v[p].edad<<endl;
              cout<<"\tPromedio: "<<vector[p]<<endl; 

//Imprimir un reporte con las notas del mejor estudiante
         
         n=0;
         for(int i=0;i<b;i++){
               if(v[p1].ced==w[i].ced){
                   n++;                    
                                       }
               }
         
         mejor *r;
         r = new mejor[n];
         n=0;
         cout<<"\n**** Mejor estudiante con sus respectivas materias en orden con sus notas ****"<<endl;
         cout<<"\n\t "<<v[p1].ced<<" "<<v[p1].nombre<<endl;
          for(int j=0;j<b;j++){
                  if(v[p1].ced==w[j].ced){
                     strcpy(r[n].materia,w[j].materia);
                     r[n].nota = w[j].nota;
                     n++;                     
                                          }
                  } 
              
            mejor elem;
            int k;
            for(int i=1;i<n;i++){
                    k = i-1;
                    elem = r[i];
                    while(k>=0 && strcmpi(elem.materia,r[k].materia)<0){
                          r[k+1] = r[k];
                          k--;                                            
                                                                      }
                       r[k+1] = elem;                                               
                    }
                
                for(int i=0;i<n;i++){
                        cout<<"\t "<<r[i].materia<<" "<<r[i].nota<<endl;
                        }                                     
                  cout<<endl;
                  
//Generar reporte con el mejor estudiante de cada materia

    FILE *h;
    h=fopen("Reporte.txt","w");
            
            int may=-1,posi=0,q=0;
            int mayo=-1;
             for(int i=0;i<b;i++){
                    
                     for(int j=i+1;j<b;j++)
                       if(strcmpi(w[i].materia,w[j].materia)==0)
                               q++;                                      
                        
                     }
                     
              
                 t = new reporte[q];
                 int s=0,band1=0;
                 int gj=0;
                  for(int i=0;i<b;i++){
                      band1=0;
                      gj=0;
                      while(gj < b){
                              if(strcmpi(t[gj].materia,w[i].materia)==0){
                                       band1=1;                                  
                                                                         } 
                              gj++;
                              }
                       if(!band1){       
                          for(int j=i+1;j<b;j++){
                                 
                                  if(strcmpi(w[i].materia,w[j].materia)==0){
                                       if(w[i].nota < w[j].nota){
                                            may=w[j].nota;
                                             t[s].nota=may;
                                             strcpy(t[s].materia,w[j].materia);
                                             strcpy(t[s].periodo,w[j].periodo);
                                              for(int k=0;k<a;k++){
                                                  if(v[k].ced==w[j].ced)
                                                     strcpy(t[s].nombre,v[k].nombre);                
                                                    }//for
                                                s++;              
                                       }//if
                                       if(w[i].nota > w[j].nota){
                                             may=w[i].nota;
                                             t[s].nota=may;
                                             strcpy(t[s].materia,w[i].materia);
                                             strcpy(t[s].periodo,w[i].periodo);
                                              for(int k=0;k<a;k++){
                                                  if(v[k].ced==w[i].ced)
                                                     strcpy(t[s].nombre,v[k].nombre);                
                                                    }//for
                                                s++;   
                                                    }//if
                                               
                                        if(w[i].nota==w[j].nota){
                                             
                                              for(int k=0;k<a;k++){
                                                  if(v[k].ced==w[i].ced){
                                                     if(vector[k] > vector[k+1])
                                                          may =(int) vector[k];
                                                          strcpy(t[s].nombre,v[k].nombre);
                                                                           
                                                      }//if
                                                                
                                                    }//for
                                                 t[s].nota=may;
                                                 strcpy(t[s].materia,w[i].materia);
                                                 strcpy(t[s].periodo,w[i].periodo);
                                                 s++;   
                                                    }//if              
                                        }  //if grande          
                                     }    
                                  } //for
                                       
                          }  //for
                 
                 
 //insercion binaria  
               
                 reporte yp;
                 int ult,pri,central;
                 for(int i=1;i<s;i++){
                       yp=t[i];
                       pri=0;
                       ult=i-1;
                       //busqueda binaria de la posicion de insercion
                       while(pri<=ult){
                          central=(int)((pri+ult)/2);
                          if(strcmpi(yp.nombre,t[central].nombre)<0){
                                ult=central-1;
                               }
                            else{
                                 pri=central+1;
                                 }
                       //se desplaza a la derecha  los elementos ordenados para insertar de nuevo
                          for(int j=i-1;j>=pri;j--){
                                  t[j+1]=t[j];
                                  }
                            t[pri]=yp;                        
                                   }
                       }
                        char nombre[30];
                        long ced;
                        char materia[30];
                        char periodo[10];
                        int nota;
                        
                        for(int o=0;o<s;o++){
                           strcpy(nombre,t[o].nombre);
                           strcpy(materia,t[o].materia);
                           strcpy(periodo,t[o].periodo);
                           nota=t[o].nota;
                           ced=t[o].ced;
                           fprintf(h,"%s,%s,%s,%d\n",nombre,materia,periodo,nota);
                                           }
                             
                           fclose(h); 
                                     
           }         
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
