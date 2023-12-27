#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct Obras
{
  char nome[50];
  char fabricante[50];
  char data_de_fabricacao[11];
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

int quantidade_total_de_obras=0;
int quantidade_total_de_ingressos=0;
int ingresso_inteiro = 0, ingresso_meia = 0, ingresso_isento = 0;

// ### Protótipos das Funções ###
void menu_administrativo();
void menu_acervo();
void exibir_logotipo();
void efetuar_nova_venda();
void listar_vendas();
void incrementar_tipo_de_ingresso_vendido();
void relatorio_de_vendas();
int numerar_ingresso(int ingresso);
void imprimir_data_hora_atual();
void ocultar_senha_entrada(char *senha, int comprimento_maximo);
void criptografar_descriptografar(char senha[]);
int criar_senhas_padrao();
int autenticar_usuario();
int trocar_senha();
void formatar_nome(char *nome_completo);
int valiadar_entrada_de_caracteres(int indice, char entrada_do_usuario[]);
int validar_data(char *data);
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
  if (criar_senhas_padrao()) 
  {
    main();
    return -1; // Primeiro acesso
  }
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
        if (autenticar_usuario() == 1) 
        {
        menu_administrativo();
        } 
        else if (autenticar_usuario() == 0) 
        {
        printf("\n\t ### Credenciais incorretas. Tente novamente.\n");
        getch();
        }
        break;
      case '0':
        system("cls");
        printf("\n\n\t\t\t### Encerrando......\n");
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
    printf("\t### 5. Alterar Senha\n");
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
        if (trocar_senha()) 
        {
        printf("\n\t### Senha alterada com sucesso.\n");
        getch();
        } 
        else 
        {
        printf("\t### Falha ao trocar a senha.\n");
        getch();
        }
        fflush(stdin);
        break;
      case '0':
        system("cls");
        printf("\n\n\t\t\t### Voltando ao Menu Anterior...\n");
        getch();
        main();
        break;
      default:
        printf("\n\t### Opção Inválida! Digite uma opcão entre 0 e 5");
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
        printf("\n\n\t\t\t### Voltando ao menu anterior....");
        getch();
        menu_administrativo();
        break;
      default:      
        printf("\n\t### Opção Inválida. Digite uma opção de 0 a 3.");
        getch();
    }
  } while (opcao != 0);
}
//---------------------------------------------------------------------------------------------
void exibir_logotipo() 
{
    system("cls");
    printf("\t\t\t\t\t\t#########################\n");
    printf("\t\t\t\t\t\t#    **MUSEU TECH**     #\n");
    printf("\t\t\t\t\t\t#########################\n");
}
//---------------------------------------------------------------------------------------------
void efetuar_nova_venda()
{
  printf("\n\n\t\t\t\t### ** Nova Venda ** ###");
  printf("\n\n\t\t\t--------------- Ingresso %d ---------------\n\n", 
          numerar_ingresso(vendas[quantidade_total_de_ingressos].ingresso));
  imprimir_data_hora_atual();
  printf("\n\t\t\t### Digite o nome: ");
  scanf("\t %[^\n]", vendas[quantidade_total_de_ingressos].nome);
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
  printf("\n\t\t\t\t\t\t  ** Lista de Vendas **\n\n");
  
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
void ocultar_senha_entrada(char *senha, int comprimento_maximo) 
{
  int i = 0;

  while (1) 
  {
    senha[i] = getch();
    if (senha[i] == '\r' || senha[i] == '\n') 
    {
      senha[i] = '\0';
      break;
    } 
    else if (senha[i] == 8 && i > 0) 
    { // Backspace
      printf("\b \b");
      i--;
    } 
    else 
    {
      printf("*");
      i++;
    }
    if (i == comprimento_maximo - 1) 
    {
      senha[i] = '\0';
      break;
    }
  }
  printf("\n");
}
//---------------------------------------------------------------------------------------------
void criptografar_descriptografar(char senha[]) 
{
  char chave = 'K'; // Chave de criptografia

  for (int i = 0; i < (int)strlen(senha); i++) 
  {
    senha[i] = senha[i] ^ chave; // Operação XOR com a chave
  }
}
//---------------------------------------------------------------------------------------------
int criar_senhas_padrao()

{
  FILE *arquivo;
  char nome_de_usuario_padrao[50];
  char senha_padrao[50];

  if ((arquivo = fopen("senhas.dat", "rb")) == NULL) 
  {
    exibir_logotipo();
    printf("\n\n\t### Olá, este é o seu primeiro acesso, defina o nome de usuário e a senha"
           "\n\t### O nome de usuário não poderá ser alterado posteriormente!");
    printf("\n\n\n\t### Defina o novo nome de usuário: ");
    scanf("%s", nome_de_usuario_padrao);
    printf("\t### Defina a nova senha: ");
    ocultar_senha_entrada(senha_padrao, sizeof(senha_padrao));
    fflush(stdin);

    arquivo = fopen("senhas.dat", "wb");
    if (arquivo == NULL) 
    {
      printf("\n\n\n\n\n\n\n\t\t\t\t\t\t### Erro ao criar o arquivo.\n");
      getch();
      exit(1);
    }

    criptografar_descriptografar(senha_padrao);

    fprintf(arquivo, "%s\n", nome_de_usuario_padrao);
    fprintf(arquivo, "%s\n", senha_padrao);

    fclose(arquivo);

    printf("\n\t### Credenciais padrão criadas com sucesso.\n");
    getch();
    return 1;
  }
  return 0;
}
//---------------------------------------------------------------------------------------------
int autenticar_usuario() 

{
  FILE *arquivo;
  char nome_de_usuario_arquivo[50];
  char senha_criptografada[50];
  char usuario[20];
  char senha[20];

  arquivo = fopen("senhas.dat", "r");
  if (arquivo == NULL) 
  {
    printf("\n\t### Erro ao abrir o arquivo.\n");
    exit(1);
  }
  exibir_logotipo();
  printf("\n\n\t### Digite o nome de usuário: ");
  scanf("%s", usuario);
  printf("\t### Digite a senha: ");
  ocultar_senha_entrada(senha, sizeof(senha));

  fgets(nome_de_usuario_arquivo, sizeof(nome_de_usuario_arquivo), arquivo);
  nome_de_usuario_arquivo[strcspn(nome_de_usuario_arquivo, "\n")] = '\0';

  fgets(senha_criptografada, sizeof(senha_criptografada), arquivo);
  senha_criptografada[strcspn(senha_criptografada, "\n")] = '\0';

  fclose(arquivo);

  criptografar_descriptografar(senha_criptografada);

  if (strcmp(usuario, nome_de_usuario_arquivo) == 0 && strcmp(senha, senha_criptografada) == 0) 
  {
    return 1; // Autenticação bem-sucedida
  } 
  else 
  {
    return 0; // Autenticação falhou
  }
}
//---------------------------------------------------------------------------------------------
int trocar_senha() 
{
  FILE *arquivo;
  char usuario_atual[20];
  char senha_atual[20];
  char nome_de_usuario_arquivo[50];
  char senha_criptografada[50];
  char nova_senha[50];

  arquivo = fopen("senhas.dat", "r");
  if (arquivo == NULL) 
  {
    printf("\n\t### Erro ao abrir o arquivo.\n");
    exit(1);
  }
  printf("\n\t### Digite o usuário atual: ");
  scanf("%s", usuario_atual);
  printf("\t### Digite a senha atual: ");
  ocultar_senha_entrada(senha_atual, sizeof(senha_atual));

  fgets(nome_de_usuario_arquivo, sizeof(nome_de_usuario_arquivo), arquivo);
  nome_de_usuario_arquivo[strcspn(nome_de_usuario_arquivo, "\n")] = '\0';

  fgets(senha_criptografada, sizeof(senha_criptografada), arquivo);
  senha_criptografada[strcspn(senha_criptografada, "\n")] = '\0';

  fclose(arquivo);

  criptografar_descriptografar(senha_criptografada);

  if (strcmp(senha_atual, senha_criptografada) != 0) 
  {
    printf("\n\t### Senha atual incorreta.\n\t### Acesso negado.\n");
    return 0;
  }

  printf("\n\t### Digite a nova senha: ");
  ocultar_senha_entrada(nova_senha, sizeof(nova_senha));

  criptografar_descriptografar(nova_senha);

  arquivo = fopen("senhas.dat", "w");
  if (arquivo == NULL) 
  {
    printf("\n\t### Erro ao abrir o arquivo.\n");
    exit(1);
  }

  fprintf(arquivo, "%s\n", nome_de_usuario_arquivo);
  fprintf(arquivo, "%s\n", nova_senha);
  fclose(arquivo);

  return 1;
}
//---------------------------------------------------------------------------------------------
void formatar_nome(char *nome_completo) 
{
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
  if ((int)strlen(entrada_do_usuario) > limite) 
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
void adicionar_acervo()
{
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
           nome, fabricante, data_de_fabricacao, conservacao, importancia_historica);

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
    printf("\n\t### Obra com o nome '%s' não encontrada.\n", nome_excluir);
    getch();
    remove("temp.csv"); // Remover o arquivo temporário, já que não houve alterações
  } 
  else 
  {
    remove("obras.csv"); // Remover o arquivo original
    rename("temp.csv", "obras.csv"); // Renomear o arquivo temporário para substituir o original
    printf("\n\t### Obra com o nome '%s' foi excluída com sucesso.\n", nome_excluir);
    getch();
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
           nome, fabricante, data_de_fabricacao, conservacao, importancia_historica);
    
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
//---------------------------------------------------------------------------------------------
