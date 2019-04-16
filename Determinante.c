#include <stdlib.h>
#include <stdio.h>

void freeMemory(long int **array, int arraySize)
{
  for ( int i = 0; i < arraySize; i++)
    free ( array[i] );

  free ( array );
}


void getCofactorMatrix(long int **matrix, long int **temporal, int p, int q, int matrixSize)
{
  int i = 0, j = 0;

  for (int row = 0; row < matrixSize; row++) 
  { 
    for (int col = 0; col < matrixSize; col++) 
    { 
      if (row != p && col != q) 
      { 
        temporal[i][j++] = matrix[row][col]; 

        if (j == matrixSize - 1) 
        { 
          j = 0; 
          i++; 
        }
      } 
    }
  } 
}

long int detMatrix ( long int **matrix, int matrixSize )
{
  long int determinant = 0, i;
  long int **temporal;
  int sign = 1;

  temporal = malloc ( matrixSize * sizeof ( long int * ) );
  for ( i = 0; i < matrixSize; i++ )
    temporal[i] = malloc ( matrixSize * sizeof ( long int ) );

  if ( matrixSize == 1 ) 
    return matrix[0][0];

  else if ( matrixSize == 2 )
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

  for ( i = 0; i < matrixSize; i++)
  {
    getCofactorMatrix(matrix, temporal, 0, i, matrixSize);
    determinant = determinant + sign * matrix[0][i] * detMatrix (temporal, matrixSize - 1);
    sign = -sign; 
  }

  freeMemory( temporal, matrixSize );
  return determinant;
}

void displayMatrix ( long int **matrix, int matrixSize ) 
{ 
  printf ( "\n" );
  int i,j;
  for ( i = 0; i < matrixSize; i++ ) 
  { 
    for ( j = 0; j < matrixSize; j++ ) 
      printf ( "  %ld", matrix[i][j] ); 
    printf ( "\n" ); 
  } 
}

int obtainMatrixSize ( FILE *matrixFile )   
{
  int matrixSize;
  char size [ 256 ];

  fscanf ( matrixFile, "%s", size );
  matrixSize = atoi ( size ); // se guarda el tamanio de la matriz en una variable

  return matrixSize;
}

int main ()
{
  FILE *matrixFile;
  int i, j, matrixSize;
  char fileName[ 256 ];
  long int determinant;
  long int** matrix;

  printf ( "\n\n************************ Inicio Programa ************************\n\n" );
  printf ( "Ingrese nombre del archivo contenedor de la matriz: "); scanf("%s", fileName );

  matrixFile = fopen ( fileName, "r" ); // se abre el archivo en modo lectura

  if ( matrixFile == NULL)
  {
    perror ( "Error al intentar de abrir el archivo... " );
    exit ( EXIT_FAILURE );
  }

  matrixSize = obtainMatrixSize ( matrixFile );
  matrix = malloc ( matrixSize * sizeof ( long int * ) );

  for ( i = 0; i < matrixSize; i++ )
    matrix[i] = malloc ( matrixSize * sizeof ( long int ) );

  for ( i = 0; i < matrixSize; i++ )
  {
    for ( j = 0; j < matrixSize; j++ )
    {
      if ( !fscanf ( matrixFile, "%ld", &matrix[i][j] ) ) 
        break;
    }
  }

  //displayMatrix ( matrix,matrixSize );

  determinant = detMatrix ( matrix, matrixSize );

  printf ( "\nEl determinante de la matriz es: %ld\n", determinant );
  freeMemory ( matrix, matrixSize );
  fclose ( matrixFile );

  printf ( "\n\n************************** Fin Programa *************************\n\n" );
}