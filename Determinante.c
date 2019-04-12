#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int obtainMatrixSize(FILE *matrixFile)   
{
  int matrixSize;
  char size [ 256 ];

  fscanf ( matrixFile, "%s", size ); // save matrix size from the file
  matrixSize = atoi ( size );

  return matrixSize;
}

int main ()
{
  FILE *matrixFile;
  int i, j, matrixSize;
  int** matrix;
  char fileName[ 256 ];

  printf("Ingrese nombre del archivo contenedor de la matriz: "); scanf("%s", fileName);

  matrixFile = fopen ( fileName, "r" ); // read mode

  if ( matrixFile == NULL)
  {
    perror ( "Error al intentar de abrir el archivo... " );
    exit ( EXIT_FAILURE );
  }

  matrixSize = obtainMatrixSize ( matrixFile );

  matrix = malloc ( matrixSize * sizeof ( int * ) );
  for ( i = 0; i < matrixSize; i++ )
    matrix[i] = malloc ( 4 * sizeof ( int ) );

  fclose ( matrixFile );
}