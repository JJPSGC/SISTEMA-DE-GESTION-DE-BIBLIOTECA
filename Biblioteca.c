#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declarativa de Enumerar asigna un valor
enum estadoLibro //En un Enumerador son constantes con valores asignados, asi que no cambian pero no son texto.
{
  DISPONIBLE, //Esto vale 0
  PRESTADO //esto vale 1
};

//Bloque Declarativa de Estructura del Libro
struct libro
{
  //BLoque Declarativo de Variables
  char titulo[80]; //Nombre del Libro con su tamaño
  char autor[80]; //Nombre del Autor con su tamaño
  int añoPublicacion; //variable de fecha de publicacion
  enum estadoLibro estado; //Disponibilidad con las constantes del enum
};

//Bloque Declarativa de Funciones
void agregarLibro(struct libro estante[], int *cuenta)
/* *cuenta es un puntero que le indica a la computadora que tiene que observar o tomar la informacion del main para obtener tener
un valor de la cuenta. Por eso mismo al realizar la cuenta hacia arriva con *cuenta++ se incluye el puntero porque le indica a la 
computadora donde va a ir ese dato o informacion.*/
{
  //Declarativa de Instrucciones
  getchar(); 
  //getchar limpia nuestro input stream si un \n queda de lecturas anteriores y evita que se lea ese\ \n, causando problemas
  printf("Ingrese el titulo del Libro:\n");
  fgets(estante[*cuenta].titulo,sizeof(estante[*cuenta].titulo),stdin); 
  /*El Maravilloso fgets esta hecho para colocar las cadenas en los arreglos de caracteres que hice anteriormente. 
  Y para de leer cuando lee una cosa que no es un caracter. Le indica al la computadora en donde y que tamaño
  de informacion va a ser ocupada por la cadena.*/ 
  estante[*cuenta].titulo[strcspn(estante[*cuenta].titulo, "\n")] = '\0';
  /*el strcspn se encarga de comparar las posiciones de los arreglos que esten en un arreglo
  y actua dependiendo que le indiquemos. En este caso le decimos que para la posicion de titulo
  en donde nuestro primer titulo se encuentra. Compare el titulo y encuentre la posicion donde
  \n se encuentro, una vez encontrada la hago nula para que no moleste mas adelante.*/
  printf("Ingrese el nombre del Autor:\n");
  fgets(estante[*cuenta].autor,sizeof(estante[*cuenta].autor),stdin); // Asi en adelante se leen strings con espacios.
  estante[*cuenta].autor[strcspn(estante[*cuenta].autor, "\n")] = '\0';
  /*Este uso del strcspn se dedica a eliminar el \n que se queda en el input de la computadora.
  Lo hace sustituyendo la posicion de ese \n por un \0 que es un nulo. Nada.*/
  printf("Ingrese el nombre del Año de Publicacion:\n");
  scanf("%d",&estante[*cuenta].añoPublicacion); //Los Enteros no tienen problemas para leer.
  estante[*cuenta].estado = DISPONIBLE; //Cada Libro Nuevo se asgina como disponible, obvio.
  (*cuenta)++; //Sumamos uno a la cuenta para que la posicion del siguiente libro sea diferente.
}

void buscarLibro(struct libro estante[], int cuenta, int i) 
//Se define las variables que van a ser utilizadas, ya no se usa el puntero porque no vamos a escribir en la variable cuenta.
{
  //Declarativa de Instrucciones
  getchar();
  int encontrado = 0; //Variable para asginar si encuentra el libro
  char buscado[80]; //Variable para el libro buscado (mimso tamaño que titulo)
  printf("Ingrese el titulo del Libro buscado:\n");
  fgets(buscado,sizeof(buscado),stdin); //Lee lo introducido a la variable buscado
  buscado[strcspn(buscado, "\n")] = '\0'; //Elimina los /n no deseados
  for (i = 0; i < cuenta; i++) 
  /*Este Para se dedica a recorrer el arreglo estante y realizar las instruccion que se encuentran adentro de este para*/
  {
    //Declarativa de Instrucciones
    if (strcmp(estante[i].titulo, buscado) == 0) 
    /*En C se compara con strcmp este revisa las diferencias en ASCII del dos cadenas. 
    Si no hay diferencia entonces los ASCII van a ser iguales asi que hay cero diferencia.
    Por eso se produce un cero.*/ 
    {
      //Declarativa de Instrucciones
      printf("\n Su libro esta en nuestra Biblioteca, aqui su informacion:");
      printf("\n \'%s\' de %d por %s \n",estante[i].titulo,estante[i].añoPublicacion,estante[i].autor);
      encontrado = 1; //Se asigna un numbero distinto a 0 al encontrar el libro.
      break; // Para el if si encuentra que es igual.
    } 
  }
  if (encontrado == 0) //Si encontrado no cambia a un 1 entonces significa que el libro no esta.
  {
    //Declarativa de Instrucciones
    printf("\nSu libro no esta en nuestra Biblioteca\n"); //Mensaje de No encontrado
  }
}

void prestarlibro(struct libro estante[], int cuenta, int i)
{
  //Declarativa de Instrucciones
  getchar(); //Limpiea el input stream, evitando que algun newline se quede flotanto y cause problemas.
  int tomado = 0; //Esta variable sirve como marcador. Indicara si la condiciones fueron encontradas de la busqueda.
  char prestado[80]; //Variable para el libro buscado (mimso tamaño que titulo)
  printf("Ingrese el titulo del Libro a prestar\n");
  fgets(prestado,sizeof(prestado),stdin); //Lectura de la cadena. 
  prestado[strcspn(prestado, "\n")] = '\0';// Limpieza de la cadena para evitar fallos al seguir la secuencia.
  for (i = 0; i < cuenta; i++)
  {
    if (strcmp(estante[i].titulo, prestado) == 0 && estante[i].estado == DISPONIBLE)
    /*Al igual que las otras secuencias dedicadas a encontrar libros dentro del sistema de gestion, este se le añade
    que la varaible estado tiene que ser DISPONIBLE para poder prestar un libro. Por eso se uso &&.*/
    {
      //Declarativa de Instrucciones
      printf("\n Usted a tomado prestado el libro \'%s\' de %d por %s \n",estante[i].titulo,estante[i].añoPublicacion,estante[i].autor);
      estante[i].estado = PRESTADO; //Cuando se encuentra el lbro se marca con la constante PRESTADO. Indicando su disponibilidad.
      tomado = 1; //Aqui el marcador hace su trabajo y marca que la posicion fue encontrada. Confirmando que hubo un resultado positivo
      break; //Termina el if/si cuando se cumple las condiciones.
    } 
  }
  if (tomado == 0) //Aqui, si, el marcador se mantiene igual tras el primer if/si entonces mostrara este mensaje.
  {
    //Declarativa de Instrucciones
    printf("\nEse libro no esta en nuestro sistema o Ya fue prestado\n");
  }
}

void devolverLibro(struct libro estante[], int cuenta, int i)
{
  //Declarativa de Instrucciones
  getchar(); //Limpiea el input stream, evitando que algun newline se quede flotanto y cause problemas.
  int dado = 0; //Esta variable sirve como marcador. Indicara si la condiciones fueron encontradas de la busqueda.
  char devuelto[80];//Variable para el libro buscado (mismo tamaño que titulo)
  printf("Ingrese el titulo del Libro a devolver\n");
  fgets(devuelto,sizeof(devuelto),stdin); //Lectura de la cadena. 
  devuelto[strcspn(devuelto, "\n")] = '\0';// Limpieza de la cadena para evitar fallos al seguir la secuencia.
  for (i = 0; i < cuenta; i++)
  {
    //Declarativa de Instrucciones
    if (strcmp(estante[i].titulo, devuelto) == 0 && estante[i].estado == PRESTADO) 
    {
      //Declarativa de Instrucciones
      printf("\n Usted a devuelto el libro \'%s\' de %d por %s \n",estante[i].titulo,estante[i].añoPublicacion,estante[i].autor);
      estante[i].estado = DISPONIBLE; //Cuando se encuentra el lbro se marca con la constante DISPONIBLE. Indicando su disponibilidad.
      dado = 1; //Marca la posicion como encontrada y no mostrara el mensaje si se mantiene igual.
      break; //Termina el if/si cuando se cumple las condiciones.
    }
  }
  if (dado == 0) //Aqui, si, el marcador se mantiene igual tras el primer if/si entonces mostrara este mensaje.
  {
    //Declarativa de Instrucciones
    printf("\nEse libro no esta en nuestro sistema o Ya fue devuelto\n");
  }
}

void mostrarLibros(struct libro estante[], int cuenta, int i)
{
  //Declarativa de Instrucciones
  for ( i = 0; i < cuenta; i++) //Loop para hacer display de todo lo disponibles.
  {
    if (estante[i].estado == DISPONIBLE) //Para todo aquello que tenga marcado disponible se efectua el print
    {
      printf("\n Esta disponible \'%s\' de %d por %s \n",estante[i].titulo,estante[i].añoPublicacion,estante[i].autor); 
      //Imprime cada posicion registrada del estante si se cumple la condicion
    }    
  }
}

//Estructura Principal
int main()
{
  //Declarativa de Variables 
  struct libro estante[101]; //Arreglo del libros, o sea una estanteria
  int i, sele = 0, cuenta = 0; // Declaracion de Variables y posicion.
  //Declarativa de Instrucciones
  while (sele!=6) //Este mientras asegura que el programa se mantenga corriendo excepto al ser seleccionado el 6.
  {
    printf("\nSistema de Gestion de Biblioteca\n");
    printf("\n1. Agregar un Libro a la coleccion.\n");
    printf("2. Buscar un Libro dentro de la collecion.\n");
    printf("3. Prestar un Libro de la coleccion.\n");
    printf("4. Devolver un Libro a la coleccion.\n");
    printf("5. Muestra todos los libros disponibles.\n");
    printf("6. Salir.\n");
    scanf("%d", &sele); //se lee el dato de seleccion en su variable
    switch (sele)
    {
    case 1:
    //Declarativa de Instrucciones
    agregarLibro(estante, &cuenta); //LLamada de funcion para agregar libros nuevos. Se toman todos los datos.
    break;

    case 2:
    //Declarativa de Instrucciones
    buscarLibro(estante, cuenta, i); //Llamada de funcion para buscar un libro (segun su titulo). Hace vista de los datos del libro.
    break;
  
    case 3:
    //Declarativa de Instrucciones
    prestarlibro(estante, cuenta, i); //Llamada de funcion para tomar prestado un libro, mostrandolo como prestado.
    break;
  
    case 4:
    //Declarativa de Instrucciones
    devolverLibro(estante, cuenta, i); //Llamada de funcion para devolver un libros y mostrarlo nuevamente disponible.
    break;
  
    case 5:
    //Declarativa de Instrucciones
    mostrarLibros(estante, cuenta, i); //Llamada de funcion para hacer vista de todos los libros disponibles.
    break;

    case 6:
    //Vacio para matar el programa.
    break;
  
    default:
    //Declarativa de Instrucciones
    printf("Error de Seleccion..."); //Cuando la seleccion no es ningun otro numero pues pasa esto, aunque hay que cambiarlo para que vaya para el menu.
    break;
    }
  }
  return 0;
}