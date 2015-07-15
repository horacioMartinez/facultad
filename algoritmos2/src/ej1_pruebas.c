#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/*	Escribir una función que reciba un arreglo de n números enteros e informe 
	los índices de dos números que estén entre sí a mínima distancia. 
	El orden de la función debe ser O(n log n). Justificar el orden de la 
	solución propuesta.
 	Aclaración: se considera distancia entre a y b como |b - a|.	*/


/*	Función auxiliar para imprimir si la prueba se ejecutó con éxito. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}


/*	Estructura en la que se van a guardar los índices de la solución.	*/
struct dos_posiciones
{
	size_t uno;
	size_t dos;
};


int positivo(int a, int b){
	if (a<b)
		return (b-a);
	else
		return(a-b);
}


int merge(int arr[],int l,int m,int h)
{
  int arr1[10],arr2[10]; // Two temporary arrays to hold the two arrays to be merged
  int n1,n2,i,j,k;
  n1=m-l+1;
  n2=h-m;

  for(i=0; i<n1; i++)
    arr1[i]=arr[l+i];
  for(j=0; j<n2; j++)
    arr2[j]=arr[m+j+1];

  arr1[i]=9999; // To mark the end of each temporary array
  arr2[j]=9999;

  i=0;
  j=0;
  for(k=l; k<=h; k++) { //process of combining two sorted arrays
    if(arr1[i]<=arr2[j])
      arr[k]=arr1[i++];
    else
      arr[k]=arr2[j++];
  }

  return 0;
}


int merge_sort(int arr[],int low,int high)
{
  int mid;
  if(low<high) {
    mid=(low+high)/2;
    // Divide and Conquer
    merge_sort(arr,low,mid);
    merge_sort(arr,mid+1,high);
    // Combine
    merge(arr,low,mid,high);
  }

  return 0;
}



/*	Función que devuelve una estructura dos_posiciones indicando los
	índices de los elementos del arreglo cuya distancia sea la mínima.
	Devuelve una estructura con dos posiciones inválidas en caso de
	que el largo del vector sea menor a 2.	*/
struct dos_posiciones buscar_minima_distancia(int v[], double n)
{
	struct dos_posiciones str;
	merge_sort(v,0,n-1);
	int k;
	for (k=0;k<n;k++)
		printf("%i",v[k]);
	int resi=0,resj=1,i=0,j=1;
	int min=positivo(v[i],v[j]);
	for (i=1;i<n;i++){
		if (positivo(v[i],v[i+1])<min){
				min=positivo(v[i],v[i+1]);
				resi=i;
				resj=i+1;
		}
	}
	printf("       %i , %i",resi,resj);
	str.uno=resi;
	str.dos=resj;
	return str;
}

/*	Pruebas.	*/
int main()
{
	int v1[1000] = {-1, 6, 7, 2, 9};
	struct dos_posiciones res = buscar_minima_distancia(v1, 5);
	print_test("Prueba mínima distancia", 
		(res.uno == 1 && res.dos == 2) || (res.uno == 2 && res.dos == 1));
	
	int v2[5] = {-1, 7, 6, 2, 9};
	res = buscar_minima_distancia(v2, 5);
	print_test("Prueba con valores invertidos", 
		(res.uno == 1 && res.dos == 2) || (res.uno == 2 && res.dos == 1));

	int v3[4] = {-1, 7, 6, -1};
	res = buscar_minima_distancia(v3, 4);
	print_test("Prueba con valores iguales 1", 
		(res.uno == 0 && res.dos == 3) || (res.uno == 3 && res.dos == 0));

	int v4[6] = {-1, 9, 6, 4, 6, 0};
	res = buscar_minima_distancia(v4, 6);
	print_test("Prueba con valores iguales 2", 
		(res.uno == 2 && res.dos == 4) || (res.uno == 4 && res.dos == 2));
	
	int v5[8] = {-1, 9, -1, 4, 9, 6, 2, 0};
	res = buscar_minima_distancia(v5, 8);
	print_test("Prueba con dos pares de valores iguales", 
		(res.uno == 1 && res.dos == 4) || (res.uno == 4 && res.dos == 1) ||
		(res.uno == 0 && res.dos == 2) || (res.uno == 2 && res.dos == 0));

	int v6[5] = {2, 7, 7, 4, 7};
	res = buscar_minima_distancia(v6, 5);
	print_test("Prueba con tres valores iguales", 
		(res.uno == 1 && res.dos == 2) || (res.uno == 2 && res.dos == 1) ||
		(res.uno == 1 && res.dos == 4) || (res.uno == 4 && res.dos == 1) ||
		(res.uno == 2 && res.dos == 4) || (res.uno == 4 && res.dos == 2));

	int v7[2] = {-1, 9};
	res = buscar_minima_distancia(v7, 2);
	print_test("Prueba con vector mínimo", 
		(res.uno == 0 && res.dos == 1) || (res.uno == 1 && res.dos == 0));

	int v8[1] = {4};
	res = buscar_minima_distancia(v8, 1);
	print_test("Prueba con un vector de tamaño 1", res.uno < 0 && res.dos < 0);

	res.uno=5;
	res.dos=7;
	printf("           %i %i",res.uno,res.dos);
	return 0;
}


