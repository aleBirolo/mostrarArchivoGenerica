#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Estructura para txt fijo
typedef struct
{
    char cad1[10],
         cad2[15];
    int num;
}t_paraTxtFijo;

/// Estructura para txt variable
typedef struct
{
    char cad[50];
    int num;
    char car;
}t_paraTxtVar;

/// Estructura para bin
typedef struct
{
    int num;
    char car;
    float real;
}t_paraBin;

#define NOM_FILE_BIN "archivo_binario.bin"
#define NOM_FILE_TXT_FIJO_ "archivo_txt_fijo.txt"
#define NOM_FILE_TXT_VAR "archivo_txt_var.txt"

/// Funciones para el lote
void crearLote (t_paraTxtFijo *a1,t_paraTxtVar *b1, t_paraBin *c1 );
void grabarLoteArchivos (FILE *fpTxt_fijo, t_paraTxtFijo *a1,
                         FILE *fpTxt_var, t_paraTxtVar *b1,
                         FILE *fpBin, t_paraBin *c1);

/// Funciones del Ejercicio
void mostrarArchivoTxtFijo (FILE *fp);
void mostrarArchivoTxtVar (FILE *fp);
void mostrarArchivoBin (FILE *fp);
typedef void(*Mostrar)(FILE *fp);
void mostrarArchivoGenerico (FILE **fp,const char *nom, const char *modo, Mostrar mostrar );

int main()
{
    FILE *fpTxt_fijo,
         *fpTxt_var,
         *fpBin;

    t_paraTxtFijo a1[2];
    t_paraTxtVar b1[2];
    t_paraBin c1[2];

    /// Para generar lote
    fpTxt_fijo = fopen (NOM_FILE_TXT_FIJO_, "wb");
    if (!fpTxt_fijo)
        printf("\n Error %s ", NOM_FILE_TXT_FIJO_);

    fpTxt_var = fopen (NOM_FILE_TXT_VAR, "wb");
    if (!fpTxt_var)
        printf("\n Error %s ", NOM_FILE_TXT_VAR);

    fpBin = fopen (NOM_FILE_BIN, "wb");
    if (!fpBin)
        printf("\n Error %s ", NOM_FILE_BIN);

    crearLote(a1, b1, c1);
    grabarLoteArchivos (fpTxt_fijo, a1,fpTxt_var, b1,fpBin, c1  );

    fclose(fpTxt_fijo);
    fclose(fpTxt_var);
    fclose(fpBin);

    /// Comienzo del ejercicio
    printf ("\n Archivo txt de longitud fija:\n");
    mostrarArchivoGenerico(&fpTxt_fijo,NOM_FILE_TXT_FIJO_, "r", mostrarArchivoTxtFijo);

    printf ("\n Archivo txt de longitud variable:\n");
    mostrarArchivoGenerico(&fpTxt_var,NOM_FILE_TXT_VAR, "r", mostrarArchivoTxtVar);

    printf ("\n Archivo binario:\n");
    mostrarArchivoGenerico(&fpBin,NOM_FILE_BIN, "rb", mostrarArchivoBin);
    return 0;
}

/// funciones para el lote
void crearLote (t_paraTxtFijo *a1,t_paraTxtVar *b1, t_paraBin *c1 )
{

    strcpy (a1->cad1, "cadena1");
    strcpy (a1->cad2, "subcadena1");
    a1->num = 1;

    a1++;

    strcpy (a1->cad1, "cad2");
    strcpy (a1->cad2, "subcana2");
    a1->num = 2;


    strcpy (b1->cad, "supercadena");
    b1->num = 1;
    b1->car ='a';

    b1++;

    strcpy (b1->cad, "subcad");
    b1->num = 2;
    b1->car ='b';

    c1->num=99;
    c1->car='z';
    c1->real=1.1;

    c1++;

    c1->num=98;
    c1->car='x';
    c1->real=2.2;
}

void grabarLoteArchivos (FILE *fpTxt_fijo, t_paraTxtFijo *a1,
                         FILE *fpTxt_var, t_paraTxtVar *b1,
                         FILE *fpBin, t_paraBin *c1)
{
    int i;

    for (i=0 ;i < 2; i++, a1++, b1++, c1++)
    {
        fprintf(fpTxt_fijo, "%-10s %-15s %2d\n", a1->cad1, a1->cad2, a1->num);
        fprintf(fpTxt_var, "%s %d %c\n", b1->cad, b1->num, b1->car);
        fwrite (c1,sizeof(t_paraBin), 1, fpBin);
    }
}

/// funciones del ejercicio
void mostrarArchivoTxtFijo (FILE *fp)
{
    t_paraTxtFijo a1;
    char linea[5000];

    rewind(fp);

    while (fgets(linea, 5000, fp))
    {
        sscanf (linea,"%10s %15s %d", a1.cad1, a1.cad2, &a1.num);
        printf ("%-10s %-15s %2d\n", a1.cad1, a1.cad2, a1.num);
    }
}

void mostrarArchivoTxtVar (FILE *fp)
{
    t_paraTxtVar b1;
    char linea[5000],
        *aux;

    rewind(fp);

    while (fgets(linea, 5000, fp))
    {
        aux= strrchr(linea,' ');
        b1.car = *(aux+1);
        *aux='\0';

        aux= strrchr(linea,' ');
        sscanf (aux,"%d",&b1.num);
        //b1.num = atoi (aux+1);
        *aux='\0';

        strcpy(b1.cad, linea);
        printf ("%s %d %c\n", b1.cad, b1.num, b1.car);
    }
}

void mostrarArchivoBin (FILE *fp)
{
     t_paraBin c1;

    fseek(fp,0L, SEEK_SET);

    fread(&c1, sizeof(t_paraBin),1, fp);

    while (!feof(fp))
    {

        printf ("%d %c %f\n", c1.num, c1.car, c1.real);
        fread(&c1, sizeof(t_paraBin),1, fp);
    }
}

void mostrarArchivoGenerico (FILE **fp, const char *nom, const char *modo, Mostrar mostrar)
{
    *fp= fopen(nom, modo);

    if (!*fp)
    {
        printf ("\n Error %s", nom);
        return;
    }
    mostrar (*fp);
    fclose(*fp);
}
