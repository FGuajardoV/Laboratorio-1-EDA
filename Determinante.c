#include <stdlib.h>
#include <stdio.h>

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
  char fileName[ 256 ];
  long int determinant;

  printf("\n\n************************ Inicio Programa ************************\n\n");
  printf("Ingrese nombre del archivo contenedor de la matriz: "); scanf("%s", fileName);

  matrixFile = fopen ( fileName, "r" ); // read mode

  if ( matrixFile == NULL)
  {
    perror ( "Error al intentar de abrir el archivo... " );
    exit ( EXIT_FAILURE );
  }

  matrixSize = obtainMatrixSize ( matrixFile );

  //idea de codigo rescatada desde StackOverflow: ------------------------------------------------------------
  // https://stackoverflow.com/questions/18215325/how-to-read-from-text-file-and-store-in-matrix-in-c --------

  int** matrix;
  matrix = malloc ( matrixSize * sizeof ( int * ) );

  for ( i = 0; i < matrixSize; i++ )
    matrix[i] = malloc ( matrixSize * sizeof ( int ) );

  for ( i = 0; i < matrixSize; i++ )
  {
    for ( j = 0; j < matrixSize; j++ )
    {
      if ( !fscanf ( matrixFile, "%d", &matrix[i][j] ) ) 
        break;
    }
  }
  // fin de codigo rescatado ----------------------------------------------------------------------------------

  if ( matrixSize == 1 ) determinant = matrix[0][0]; 

  if ( matrixSize == 2 ) determinant = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

  printf ( "\nEl determinante de la matriz del archivo '%s' es: %ld\n",fileName, determinant );

  fclose ( matrixFile );
  printf("\n\n************************** Fin Programa *************************\n\n");
}