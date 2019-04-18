#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Funcion que libera los arreglos creados por malloc.
void freeMemory ( long int **array, int arraySize )
{
  for ( int i = 0; i < arraySize; i++ )
    free ( array[i] );

  free ( array );
}

//Funcion para obtener la matriz de cofactores de matrix, almacenandose en una
//matriz temporal, siendo matrixSize el tamano actual del arreglo.
//p (fila), q (columna) son los indices de donde se quieren obtener los cofactores.
//Pero como siempre se ingresara la busqueda de la primera fila, por lo general p ingresara como 0.
void getCofactorMatrix ( long int **matrix, long int **temporal, int p, int q, int matrixSize )
{
  int i, j;

  i = 0; //Indice filas.
  j = 0; //Indice columnas.

  //Recorremos todos los elementos de la matriz.
  //row = fila, col = columna.
  for ( int row = 0; row < matrixSize; row++ ) 
  { 
    for ( int col = 0; col < matrixSize; col++ ) 
    { 
      //Se copian los elementos de la matriz en la temporal. Que no corresponden a las actuales 
      //filas y columnas (p y q).
      if ( row != p && col != q ) 
      { 
        temporal[ i ][ j ] = matrix[ row ][ col ];
        j++; 

        //Se llena la fila, asi que se incrementa el index de la fila y se resetea
        //el index de la columna.
        if ( j == matrixSize - 1 ) 
        { 
          j = 0; 
          i++; 
        }
      } 
    }
  } 
}

//Funcion que obtiene el valor del determinante de una matriz de NxN usando el siguiente proceso:
//Para cada elemento de la primera fila x columna, primero se obtiene la matriz de  cofactores de esos elementos 
//y después multiplicamos el elemento con el determinante del cofactor correspondiente, y finalmente 
//añadimos todos los elementos con signos alternantes. 
//Como caso base, el valor determinante de una matriz 1 * 1 es el único valor en sí mismo.
//El cofactor de un elemento, es una matriz que podemos obtener al eliminar la fila y la columna de ese
//elemento de la matriz.
long int detMatrix ( long int **matrix, int matrixSize )
{
  long int determinant;
  long int **temporal;
  int sign, i;

  //Almacenar el signo para la suma final del determinante.
  sign = 1; 

  //Valor inicial del resultado.
  determinant = 0; 

  //Esta matriz se crea para almacenar los cofactores.
  temporal = malloc ( matrixSize * sizeof ( long int * ) );
  for ( i = 0; i < matrixSize; i++ )
    temporal[ i ] = malloc ( matrixSize * sizeof ( long int ) );

  //Caso base matriz 1 * 1.
  if ( matrixSize == 1 ) 
    return matrix[ 0 ][ 0 ];

  //Caso base matriz 2 * 2. Para simplificar el desarrollo del algoritmo
  else if ( matrixSize == 2 )
    return matrix[ 0 ][ 0 ] * matrix[ 1 ][ 1 ] - matrix[ 1 ][ 0 ] * matrix[ 0 ][ 1 ];

  //Se itera para cada elemento de la primera fila.
  for ( i = 0; i < matrixSize; i++)
  {
    //Se obtiene la matriz de cofactores de matriz[0][i].
    getCofactorMatrix ( matrix, temporal, 0, i, matrixSize );
    determinant = determinant + sign * matrix[ 0 ][ i ] * detMatrix ( temporal, matrixSize - 1 );

    //Los terminos se agregaran con signos alternados.
    sign = -sign; 
  }
  //Luego de usar la matriz temporal, procedemos a liberar el espacio usado en los bloques de memoria
  freeMemory( temporal, matrixSize ); 
  return determinant;
}

//Funcion para mostrar la matriz almacenada.
void displayMatrix ( long int **matrix, int matrixSize ) 
{ 
  printf ( "\n" );
  int i,j;

  //Se recorre para mostrar cada elemento.
  for ( i = 0; i < matrixSize; i++ ) 
  { 
    for ( j = 0; j < matrixSize; j++ ) 
      printf ( "  %ld", matrix[i][j] ); 
    printf ( "\n" ); 
  } 
}

//Retorna el tamano de la matriz rescatado desde el archivo.
int obtainMatrixSize ( FILE *matrixFile )   
{
  int matrixSize;
  char size [ 256 ];

  fscanf ( matrixFile, "%s", size );
  
  // se guarda el tamanio de la matriz en una variable
  matrixSize = atoi ( size ); 

  return matrixSize;
}

//Funcion principal del programa.
int main ()
{
  FILE *matrixFile;
  int i, j, matrixSize;
  char fileName[ 256 ];
  long int determinant;
  long int** matrix;

  printf ( "\n\n************************ Inicio Programa ************************\n\n" );
  printf ( "Ingrese nombre del archivo contenedor de la matriz: "); 
  scanf("%s", fileName );

  // se abre el archivo en modo lectura
  matrixFile = fopen ( fileName, "r" ); 

  //Se verifica si es que el archivo existe dentro del directorio, si es que este no se
  //encuentra mostrara un mensaje de error en pantalla para guiar al usuario.
  if ( matrixFile == NULL)
  {
    perror ( "Error al intentar de abrir el archivo... " );
    exit ( EXIT_FAILURE );
  }

  //Se crea con memoria dinamica el arreglo para almacenar la matriz
  matrixSize = obtainMatrixSize ( matrixFile );
  matrix = malloc ( matrixSize * sizeof ( long int * ) );

  //Se crean los 'subarreglos' de la matriz
  for ( i = 0; i < matrixSize; i++ )
    matrix[ i ] = malloc ( matrixSize * sizeof ( long int ) );

  //Se lee el archivo para rescatar los numeros de este
  for ( i = 0; i < matrixSize; i++ )
  {
    for ( j = 0; j < matrixSize; j++ )
    {
      //Se almacenan en long integer, si no encuentra un int sale del for por el break.
      //Pero el puntero del archivo se sigue moviendo.
      if ( !fscanf ( matrixFile, "%ld", &matrix[ i ][ j ] ) ) 
        break;
    }
  }
  //displayMatrix ( matrix,matrixSize );

  //llamada de la funcion que nos entregara el determinante
  determinant = detMatrix ( matrix, matrixSize );

  printf ( "\nEl determinante de la matriz es: %ld\n", determinant );

  //Liberamiento de memoria, tanto del arreglo como del archivo.
  freeMemory ( matrix, matrixSize );
  fclose ( matrixFile );

  printf ( "\n\n************************** Fin Programa *************************\n\n" );
}