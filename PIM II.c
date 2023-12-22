#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include<time.h>
#include<Windows.h>

typedef struct Obras
{
  char nome[50];
  char fabricante[50];
  char data_de_fabricacao[10];
  char conservacao[30];
  char importancia_historica[1000];
} obras;

struct Vendas
{  
  int ingresso;
  char nome[100];
  int idade;
  float preco;
  char forma_de_pagamento[30];
  struct tm data_hora;
} vendas[1000];

struct tm data_hora_venda;

char confirmacao_nome_de_usuario[20] = "admin";
char confirmacao_senha[20] = "admin";
int quantidade_total_de_obras=0;
int quantidade_total_de_ingressos=0;
int ingresso_inteiro = 0, ingresso_meia = 0, ingresso_isento = 0;

// ### Protótipos das Funções ###
void menu_administrativo();
void menu_acervo();
void gotoxy(int x, int y);
void exibir_logotipo();
void efetuar_nova_venda();
void listar_vendas();
void incrementar_tipo_de_ingresso_vendido();
void autenticar_usuario();
void relatorio_de_vendas();
void formatar_nome(char *nome_completo);
void alterar_senha();
int valiadar_entrada_de_caracteres(int indice, char entrada_do_usuario[]);
int validar_data(char *data);
int numerar_ingresso(int ingresso);
void imprimir_data_hora_atual();
char verificar_forma_de_pagamento(int idade, char *forma_de_pagamento);
float calcular_valor_do_ingresso(int idade);
void alterar_preco_do_ingresso();
void adicionar_acervo();
void excluir_acervo();
void listar_acervo();

//---------------------------------------------------------------------------------------------
int main() 
{
  setlocale(LC_ALL, "es_US.UTF-8");
  
  char opcao;
  do 
  {
    exibir_logotipo();
    printf("\n\n\t### ** Menu Principal **");
    printf("\n\n\t### 1. Nova Venda");
    printf("\n\t### 2. Listar Vendas");
    printf("\n\t### 3. Administração");
    printf("\n\t### 0. Sair\n\n\n");
    printf("\t### Digite a opção: ");
    scanf("%c", &opcao);
    getchar();
    fflush(stdin);

    switch(opcao) 
    {
      case '1':
        system("cls");        
        exibir_logotipo();
        efetuar_nova_venda();
        incrementar_tipo_de_ingresso_vendido();
        break;
      case '2':
        system("cls");
        exibir_logotipo();
        listar_vendas();
        getch();
        break;
      case '3':
        system("cls");
        exibir_logotipo();
        autenticar_usuario();
        fflush(stdin);
        break;
      case '0':
        system("cls");
        gotoxy(10, 20);
        printf("Encerrando......\n");
        getch();
        exit(1);
        break;
      default:
        printf("\n\t### Opção Inválida! Por favor digite uma opção ente 0 a 3.");
        getch();
    }
  }while(opcao != '0');
  return 0;
}
//---------------------------------------------------------------------------------------------
void menu_administrativo() 
{
  char opcao;
  do 
  {    
    system("cls");
    exibir_logotipo();
    printf("\n\t### ** Administração **\n\n");
    printf("\t### 1. Relatório de vendas\n");
    printf("\t### 2. Alterar preço do ingresso\n");
    printf("\t### 3. Lista de clientes\n");
    printf("\t### 4. Controle de acervo\n");
    printf("\t### 5. Aterar Senha\n");
    printf("\t### 0. Voltar ao menu anterior\n\n\n");
    printf("\t### Digite a opção: ");
    scanf(" %c", &opcao);
    fflush(stdin);

    switch (opcao) 
    {
      case '1':
        system("cls");
        exibir_logotipo();
        relatorio_de_vendas();
        break;
      case '2':
        system("cls");
        alterar_preco_do_ingresso();
        getch();
        break;
      case '3':
        //TODO
        // **Adicionar código para listar os clientes**
        break;
      case '4':
        system("cls");
        exibir_logotipo();
        menu_acervo();
        getch();
      break;
      case '5':
        system("cls");
        exibir_logotipo();
        alterar_senha();
        fflush(stdin);
        break;
      case '0':
        system("cls");
        printf("Voltando ao Menu Anterior...\n");
        getch();
        main();
        break;
      default:
        printf("### Opção Inválida! Digite uma opcão entre 0 e 5");
        getch();
    }
  }while(opcao != '0');
}
//---------------------------------------------------------------------------------------------
void menu_acervo()
{
  char opcao;
  do
  {
    system("cls");
    exibir_logotipo();
    printf("\n\t### ** Controle de Acervo ** ###\n\n");
    printf("\t### 1. Adicionar obra\n");
    printf("\t### 2. Remover obra\n");
    printf("\t### 3. Lista de obras\n");
    printf("\t### 0. Voltar ao menu anterior\n\n\n");
    printf("\t### Digite a opção: ");
    scanf("%c", &opcao);
    getchar();
    switch (opcao)
    {
      case '1':
        system("cls");
        exibir_logotipo();
        adicionar_acervo();
        break;
      case '2':
        system("cls");
        exibir_logotipo();
        excluir_acervo();
        fflush(stdin);
        break;
      case '3':
        system("cls");
        exibir_logotipo();
        listar_acervo();
        getch();
        break;
      case '0':
        system("cls");
        printf("Voltando ao menu anterior....");
        getch();
        menu_administrativo();
        break;
      default:      
        printf("Opção Inválida");
    }
  } while (opcao != 0);
}
//---------------------------------------------------------------------------------------------
void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//---------------------------------------------------------------------------------------------
void exibir_logotipo() 
{
    system("cls");
    gotoxy(45, 2);
    printf("#########################\n");
    gotoxy(45, 3);
    printf("#    **MUSEU TECH**     #");
    gotoxy(45, 4);
    printf("#########################\n");
}
//---------------------------------------------------------------------------------------------
void efetuar_nova_venda()
{
  printf("\n\n\t\t\t### ** Nova Venda ** ###");
  printf("\n\n\t\t\t--------------- Ingresso %d ---------------\n\n", 
          numerar_ingresso(vendas[quantidade_total_de_ingressos].ingresso));
  imprimir_data_hora_atual();
  printf("\n\t\t\t### Digite o nome: ");
  scanf("\t %[^\n]", &vendas[quantidade_total_de_ingressos].nome);
  formatar_nome(vendas[quantidade_total_de_ingressos].nome);
  fflush(stdin);         
  printf("\t\t\t### Digite a idade: ");
  scanf("%d", &vendas[quantidade_total_de_ingressos].idade);        
  getchar();
  
  verificar_forma_de_pagamento(vendas[quantidade_total_de_ingressos].idade, 
                               vendas[quantidade_total_de_ingressos].forma_de_pagamento);

  vendas[quantidade_total_de_ingressos].ingresso = quantidade_total_de_ingressos;
  vendas[quantidade_total_de_ingressos].preco = 
  calcular_valor_do_ingresso(vendas[quantidade_total_de_ingressos].idade);
}
//---------------------------------------------------------------------------------------------
void listar_vendas()
{
  printf("\n\t\t\t\t\t      ** Lista de Vendas **\n\n");
  
  for(int i=0; i<quantidade_total_de_ingressos; i++)
  {
    printf("\t\t\t--------------------------------------------------------------------\n");
    printf("\t\t\t| ########################  Ingresso - %d  ######################## |\n", 
            (vendas[i].ingresso + 1));
    printf("\t\t\t|------------------------------------------------------------------|\n");
    data_hora_venda = vendas[i].data_hora;
    printf("\t\t\t| Data: %02d/%02d/%02d   \t    Horário: %02d:%02d\t\t\t   |\n",
            data_hora_venda.tm_mday, data_hora_venda.tm_mon + 1, data_hora_venda.tm_year + 1900,
            data_hora_venda.tm_hour, data_hora_venda.tm_min);          
    printf("\t\t\t| Nome:.................... %-39s|\n", vendas[i].nome);
    printf("\t\t\t| Idade:................... %d anos \t\t\t\t   |\n", vendas[i].idade);
    printf("\t\t\t| Preço:................... R$%.2f \t\t\t\t   |\n", vendas[i].preco);
    printf("\t\t\t| Tipo Pagamento:.......... %s \t\t\t\t   |\n", vendas[i].forma_de_pagamento);
    printf("\t\t\t|------------------------------------------------------------------|\n\n");
  }
}
//---------------------------------------------------------------------------------------------
void incrementar_tipo_de_ingresso_vendido()
{
  ingresso_inteiro += (vendas[quantidade_total_de_ingressos].idade >= 16 && 
                       vendas[quantidade_total_de_ingressos].idade < 60);
  ingresso_meia += (vendas[quantidade_total_de_ingressos].idade < 16);
  ingresso_isento += (vendas[quantidade_total_de_ingressos].idade >= 60);
  quantidade_total_de_ingressos++;
}
//---------------------------------------------------------------------------------------------
void autenticar_usuario()
{
  
  char senha[20];
  char nome_de_usuario[20];
  int tentativas = 3;

  while(tentativas > 0)
  {
    system("cls");
    exibir_logotipo();
    printf("\n\n\t### Administração - Digite o nome de usuário e a senha para continuar\n\n");
    printf("\t### Nome de Usuário: ");
    scanf("%s",&nome_de_usuario);
    printf("\t### Senha: ");
    scanf("%s",&senha);
    fflush(stdin);
    
    if((strcmp(senha, confirmacao_senha) == 0) && (strcmp(nome_de_usuario, confirmacao_nome_de_usuario) == 0)) 
    {
      printf("\t### Nome de usuário e senha corretos!\n\n\t### Pressione qualquer tecla para continuar");
      getch();
      menu_administrativo();
    }
    else 
    {
      tentativas--;
      printf("\n\t### Nome de usuário e/ou senha inválidos!\n\n");
      printf("\t### %d tentativas restantes\n\n", tentativas);
      getch();
    }
  }
  if(tentativas == 0)
  {
    printf("\t### Você excedeu o número de tentativas.\n");
    getch();
  }
}
//---------------------------------------------------------------------------------------------
void relatorio_de_vendas()
{
  printf("\n\n\t\t### Ingressos inteiro: %d\t-\tValor ingressos inteiro: R$%.2f\n", 
          ingresso_inteiro, ingresso_inteiro*20.00);
  printf("\t\t### Ingressos meia: %d\t\t-\tValor ingressos meia: R$%.2f\n", 
          ingresso_meia, ingresso_meia*10.00);
  printf("\t\t### Ingressos isento: %d\n", ingresso_isento);
  printf("\n\n\t\t### Total de vendas: %d ingressos.\t-\tValor total: R$%.2f", 
          quantidade_total_de_ingressos, (ingresso_inteiro*20.00+ingresso_meia*10.00));
  getch();
}
//---------------------------------------------------------------------------------------------
void alterar_senha()
{
  // Declara as variáveis
  char senha_atual[20];
  char novo_nome_de_usuario[20];
  char nova_senha[20];
  char confirmacao_novo_nome_de_usuario[20];
  char confimacao_nova_senha[20];
  int tentativas = 3;

  // Valida a senha atual
  while(tentativas > 0)
  {
    system("cls");
    exibir_logotipo();
    printf("\n\n\t### Digite a senha atual: ");
    scanf("%s", &senha_atual);
    if (strcmp(senha_atual, confirmacao_senha) != 0) 
    {
      tentativas--;
      printf("\n\t### A senha atual está incorreta.\n\n");
      printf("\t### %d tentativas restantes\n\n", tentativas);
      getch();
    }
    else
    {
      // Solicita as novas informações
      do
      {
        printf("\n\t### Digite o novo nome de usuário: ");
        scanf("%s", &novo_nome_de_usuario);

        printf("\t### Confirme o novo nome de usuário: ");
        scanf("%s", &confirmacao_novo_nome_de_usuario);

        if (strcmp(novo_nome_de_usuario, confirmacao_novo_nome_de_usuario) != 0) 
        {
          printf("\n\t### Os nomes de usuário não coincidem. Tente novamente.\n");
        }  
      }while (strcmp(novo_nome_de_usuario, confirmacao_novo_nome_de_usuario) != 0);

      do 
      {
        printf("\n\t### Digite a nova senha: ");
        scanf("%s", &nova_senha);

        printf("\t### Confirme a nova senha: ");
        scanf("%s", &confimacao_nova_senha);

        if (strcmp(nova_senha, confimacao_nova_senha) != 0) 
        {
          printf("\n\t### As senhas não coincidem. Tente novamente.\n");
        }
      }while (strcmp(nova_senha, confimacao_nova_senha) != 0);

        // Atribui as novas informações
        strcpy(confirmacao_novo_nome_de_usuario, novo_nome_de_usuario);
        strcpy(confirmacao_senha, nova_senha);

        printf("\n\t### Senha alterada com sucesso!\n");
        getch();
        menu_administrativo();
    }
  }
}
//---------------------------------------------------------------------------------------------
void formatar_nome(char *nome_completo) {
  int tamanho = strlen(nome_completo);
  int i;

  // Transforma o primeiro caractere em maiúscula
  nome_completo[0] = toupper(nome_completo[0]);

  // Percorre a string para encontrar espaços e transformar a próxima letra em maiúscula
  for (i = 1; i < tamanho; i++) 
  {
    // Verifica se o caractere anterior é um espaço e se o caractere atual é uma letra
    if (nome_completo[i - 1] == ' ' && isalpha(nome_completo[i])) 
    {
        nome_completo[i] = toupper(nome_completo[i]);
    }
  }
}
//---------------------------------------------------------------------------------------------
int valiadar_entrada_de_caracteres(int indice, char entrada_do_usuario[]) 
{
  int limite = indice + 1; // Considerando o índice baseado em 0
  if (strlen(entrada_do_usuario) > limite) 
  {
    printf("Você excedeu o limite de caracteres.\n");
    return 0; // Retorna 0 se exceder o limite
  }
  return 1; // Retorna 1 se for válido
}
//---------------------------------------------------------------------------------------------
int validar_data(char *data) 
{
    int dia, mes, ano;
    char barra1, barra2;
    // Verifica se a entrada tem o formato esperado
    if (sscanf(data, "%d %c %d %c %d", &dia, &barra1, &mes, &barra2, &ano) != 5)
    {
        return 0;
    }
    // Verifica se as barras estão no lugar correto e se os valores são válidos
    if (barra1 != '/' || barra2 != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100) 
    {
        return 0;
    }
    return 1;
}
//---------------------------------------------------------------------------------------------
int numerar_ingresso(int ingresso) 
{
  ingresso = quantidade_total_de_ingressos +1;
  return ingresso;
}
//---------------------------------------------------------------------------------------------
void imprimir_data_hora_atual() 
{
  // Obtém a data e hora atuais
  struct tm *data_horaAtual;
  time_t segundos;
  time(&segundos);
  data_horaAtual = localtime(&segundos);

  // Imprime a data e a hora
  printf("\t\t\t### Data: %02d/%02d/%02d  \t  Horário: %02d:%02d ###",
          data_horaAtual->tm_mday, data_horaAtual->tm_mon + 1, data_horaAtual->tm_year + 1900,
          data_horaAtual->tm_hour, data_horaAtual->tm_min);
  vendas[quantidade_total_de_ingressos].data_hora = *data_horaAtual;
  data_hora_venda = *data_horaAtual;
}
//---------------------------------------------------------------------------------------------
char verificar_forma_de_pagamento(int idade, char *forma_de_pagamento) 
{
  int opcao;
  do 
  {
    if (idade >= 60) 
    {
      strcpy(forma_de_pagamento, "Isento(a)");
      break;
    }
    else
    {
      printf("\n\t\t\t### 1.Pix | 2.Cartão  | 3.Dinheiro");
      printf("\n\n\t\t\t### Forma de Pagamento: ");
      scanf("%d", &opcao);
      getchar();
      if (opcao < 1 || opcao > 3) 
      {
        gotoxy(6, 18);
        printf("\n\t\t\t### Opção Inválida. Por favor digite uma opcão entre 1 e 3");
      }
    }
  }while(opcao < 1 || opcao > 3);
  
  switch (opcao) 
  {
    case 1:
      strcpy(forma_de_pagamento, "Pix");
      break;
    case 2:
      strcpy(forma_de_pagamento, "Cartão");
      break;
    case 3:
      strcpy(forma_de_pagamento, "Dinheiro");
      break;
  } 
  return *forma_de_pagamento;
}
//---------------------------------------------------------------------------------------------
float calcular_valor_do_ingresso(int idade) 
{ 
  float meia = 10.00;
  float inteiro = 20.00;
  float isento = 0.00;
  return (idade > 0 && idade <= 16) ? meia : (idade >= 60 && idade <=110) ? isento : inteiro;
}
//---------------------------------------------------------------------------------------------
void alterar_preco_do_ingresso()
{
  
}
//---------------------------------------------------------------------------------------------
void adicionar_acervo(){
  FILE * fp;
  obras dados_obras;
  char cadastrar_obras;
    
  do
  {
    system("cls");
    exibir_logotipo();   
    printf("\n\t\t### ** Adicionar Obra ** ###\n\n");    
    printf("\n\t### Nome: ");
    scanf(" %[^\n]", dados_obras.nome);
    printf("\t### Fabricante: ");
    scanf(" %[^\n]", dados_obras.fabricante);
    while(!validar_data(dados_obras.data_de_fabricacao))
    {
      printf("\t### Data de fabricação (dd/mm/aaaa): ");
      scanf(" %[^\n]", dados_obras.data_de_fabricacao);
      if(!validar_data(dados_obras.data_de_fabricacao))
      {
        printf("\t### Por favor digite a data no formato correto.\n\n");
      }
    }
    printf("\t### Conservação: ");
    scanf(" %[^\n]", dados_obras.conservacao);
    printf("\t### Importância Histórica: ");
    scanf(" %[^\n]", dados_obras.importancia_historica);
    
    quantidade_total_de_obras++;
    if(( fp = fopen ("obras.csv", "a+")) == NULL )
    {
      printf("\n\t### Erro na abertura do arquivo obras.csv !\n\n");
      return;
    }
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0) 
    {
      fprintf(fp, "Nome, Fabricante, Data de Fabricação, Conservação, Importância Histórica\n");
    }
    fprintf(fp, "%s, %s,%s, %s,%s\n", dados_obras.nome, dados_obras.fabricante, dados_obras.data_de_fabricacao,
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
//---------------------------------------------------------------------------------------------
void excluir_acervo() 
{
  FILE *fp, *temp;
  char linha[500], nome_excluir[50];
  int linha_encontrada = 0;

  printf("\n\t### Digite o nome da obra que deseja excluir: ");
  scanf(" %[^\n]", nome_excluir);

  if ((fp = fopen("obras.csv", "r")) == NULL) 
  {
      printf("\n\t### Erro na abertura do arquivo!\n\n");
      return;
  }

  if ((temp = fopen("temp.csv", "w")) == NULL) 
  {
      printf("\n\t### Erro na abertura do arquivo temporário!\n\n");
      fclose(fp);
      return;
  }
  // Ignorar a primeira linha, que é o cabeçalho
  fgets(linha, sizeof(linha), fp);
  fputs(linha, temp); // Copiar o cabeçalho para o arquivo temporário

  while (fgets(linha, sizeof(linha), fp) != NULL) 
  {
    char nome[50], fabricante[50], data_de_fabricacao[30], conservacao[250], importancia_historica[250];

    // Ler os dados do arquivo
    sscanf(linha, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
           &nome, &fabricante, &data_de_fabricacao, &conservacao, &importancia_historica);

    // Comparar o nome lido com o nome a ser excluído
    if (strcmp(nome, nome_excluir) == 0) 
    {
      linha_encontrada = 1; // Marcar que a linha foi encontrada
    } 
    else 
    {
      fputs(linha, temp); // Copiar as outras linhas para o arquivo temporário
    }
  }
  fclose(fp);
  fclose(temp);
  if (!linha_encontrada) 
  {
      printf("Obra com o nome '%s' não encontrada.\n", nome_excluir);
      remove("temp.csv"); // Remover o arquivo temporário, já que não houve alterações
  } 
  else 
  {
      remove("obras.csv"); // Remover o arquivo original
      rename("temp.csv", "obras.csv"); // Renomear o arquivo temporário para substituir o original
      printf("Obra com o nome '%s' foi excluída com sucesso.\n", nome_excluir);
  }
}
//---------------------------------------------------------------------------------------------
void listar_acervo() 
{
  FILE *fp;
  char linha[500];
  int linhas_lidas = 0;

  if ((fp = fopen("obras.csv", "r")) == NULL) 
  {
      printf("\n\t### Erro na abertura do arquivo!\n\n");
      return;
  }
  printf("\n\n\t\t\t\t\t  ### ** Lista de Acervos ** ###\n");

  // Ignorar a primeira linha, que é o cabeçalho
  fgets(linha, sizeof(linha), fp);
  while (fgets(linha, sizeof(linha), fp) != NULL) 
  {
    char nome[50], fabricante[50], data_de_fabricacao[30], conservacao[250], importancia_historica[250];

    // Ler os dados do arquivo
    sscanf(linha, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
          &nome, &fabricante, &data_de_fabricacao, &conservacao, &importancia_historica);
    
    printf("\n-------------------------------------------------------------------------------------------------");
    printf("\n### Nome:\n   • %s\n", nome);
    printf("\n### Fabricante:\n   •%s\n", fabricante);
    printf("\n### Data de Fabricação:\n   • %s\n", data_de_fabricacao);
    printf("\n### Conservação:\n   •%s\n", conservacao);
    printf("\n### Importância Histórica:\n   • %s\n", importancia_historica);
    linhas_lidas++;
  }

  fclose(fp);

  if (linhas_lidas == 0) 
  {
      printf("\n\n\n\n\n\n\n\t\t\t### Nenhuma obra encontrada. ###");
  }
}




  

