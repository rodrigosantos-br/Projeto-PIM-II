#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Obras
{
  char nome[50];
  char fabricante[50];
  char data_de_fabricacao[10];
  char conservacao[30];
  char importancia_historica[1000];
} obras;

int quantidade_total_de_obras = 0;

int main()
{
  FILE * fp;
  obras dados_obras;
  char cadastrar_obras;
    
  do
  {
    system("cls");  
    printf("\n\t\t### ** Adicionar Obra ** ###\n\n");    
    printf("\n\t### Nome: ");
    scanf(" %[^\n]", dados_obras.nome);
    printf("\t### Fabricante: ");
    scanf(" %[^\n]", dados_obras.fabricante);
    
      printf("\t### Data de fabricação (dd/mm/aaaa): ");
      scanf(" %[^\n]", dados_obras.data_de_fabricacao);
    
    printf("\t### Conservação: ");
    scanf(" %[^\n]", dados_obras.conservacao);
    printf("\t### Importância Histórica: ");
    scanf(" %[^\n]", dados_obras.importancia_historica);
    
    quantidade_total_de_obras++;
    if(( fp = fopen ("obras.csv", "a+")) == NULL )
    {
      printf("\n\t### Erro na abertura do arquivo obras.csv !\n\n");
      return 0;
    }
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0) 
    {
      fprintf(fp, "Nome, Fabricante, Data de Fabricação, Conservação, Importância Histórica\n");
    }
    fprintf(fp, "%s, %s, %s, %s, %s\n", dados_obras.nome, dados_obras.fabricante, dados_obras.data_de_fabricacao,
                                        dados_obras.conservacao, dados_obras.importancia_historica);                                          
    fclose(fp);
    do
    {
      printf("\n\t### Deseja Cadastrar outro obra ( S / N ): ");
      scanf(" %c", &cadastrar_obras);
      cadastrar_obras = toupper(cadastrar_obras);
    } while( cadastrar_obras != 'S' && cadastrar_obras != 'N' );
  } while( cadastrar_obras == 'S');
  fflush(stdin);
}