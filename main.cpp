#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
typedef int element;

vector<vector<element>> dilatacion(vector<vector<element>> image,vector<vector<element>> elementoEstructurante);
vector<vector<element>> erosion(vector<vector<element>> image,vector<vector<element>> elementoEstructurante);
element maximo(vector<element> elements);
element minimo(vector<element> elements);

int main(int argc, char** argv ){
    vector<vector<int>> data
                {
                    {425, 21, 13, 100, 210, 40, 50},
                    {55, 4, 86, 110, 250, 30, 56},
                    {89, 8, 69, 140, 190, 20, 14},
                    {95, 2, 35, 160, 120, 60, 60},
                    {5, 5, 98, 10, 250, 70, 78},
                    {7, 89, 45, 40, 225, 80, 72}
                };
    //creando elemento estructurante
    vector<vector<element>> elementoEstructurante{{ 0, 1, 0 },
                                                  { 1, 1, 1},
                                                  { 0, 1, 0}};;

    data = erosion(data, elementoEstructurante);
    //data = dilatacion(data, elementoEstructurante);
    cout << "Filas:"<<data.size()<<"; Columnas:"<<data[0].size() << endl;
    return 0;
}

/*METODOS*/
//   MAXIMO y MINIMO calculation
//     elements - input elements
//     N        - number of input elements
element maximo(vector<element> elements)
{
   element max=-1;
   //   Order elements (only half of them)
   for (int i = 0; i < elements.size() ; ++i)
   {
      if(elements[i]>max){
          max=elements[i];
      }
   }
   return max;
}

element minimo(vector<element> elements)
{
   element min=1000000;
   //   Order elements (only half of them)
   for (int i = 0; i < elements.size(); ++i)
   {
      if(elements[i]<min){
          min=elements[i];
      }
   }
   return min;
}

vector<vector<element>> dilatacion(vector<vector<element>> image,vector<vector<element>> elementoEstructurante)
{
    vector<vector<element>> img_result = image;
    //N width, M height
    element N = image[0].size();
    element M = image.size();
    element Nestructurante = elementoEstructurante[0].size();
    element Mestructurante = elementoEstructurante.size();

    int x,y,i,j;

    //m y n de estructurante, es decir, del kernel cuanto vale M y N
    int m = Mestructurante/2;
    int n = Nestructurante/2;

   //   Move window through all elements of the image
   for (y = m; y < M - m ; ++y)
      for (x = n; x < N - n; ++x)
      {
        //cout<<y<<" "<<x<<endl;
         vector<element> window;
         int xx = x-n; int yy= y-m;
         for(i=0; i<Mestructurante; i++){
            for(j=0; j<Nestructurante; j++){
                if(elementoEstructurante[i][j] == 1){
                    window.push_back(image[yy][xx]);
                }
                xx++;
            }
            xx = x-n;
            yy++;
         }
         img_result[y][x] = maximo(window);
      }
   return img_result;
}

vector<vector<element>> erosion(vector<vector<element>> image,vector<vector<element>> elementoEstructurante)
{
    vector<vector<element>> img_result = image;
    //N width, M height
    element N = image[0].size();
    element M = image.size();
    element Nestructurante = elementoEstructurante[0].size();
    element Mestructurante = elementoEstructurante.size();
    //tamano de los elementos de la ventana
    int tW = Nestructurante * Mestructurante;

    int x,y,i,j;

    //m y n de estructurante, es decir, del kernel cuanto vale M y N
    int m = Mestructurante/2;
    int n = Nestructurante/2;

   //   Move window through all elements of the image
   for (y = m; y < M - m ; ++y)
      for (x = n; x < N - n; ++x)
      {
        //cout<<y<<" "<<x<<endl;
         vector<element> window;
         int xx = x-n; int yy= y-m;
         for(i=0; i<Mestructurante; i++){
            for(j=0; j<Nestructurante; j++){
                if(elementoEstructurante[i][j] == 1){
                    window.push_back(image[yy][xx]);
                }
                xx++;
            }
            xx = x-n;
            yy++;
         }

         img_result[y][x] = minimo(window);
      }
   return img_result;
}
