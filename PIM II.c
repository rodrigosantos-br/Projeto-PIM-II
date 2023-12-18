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
  char dataDeFabricacao[30];
  char imporatanciaHistorica[250];
  char conservacao[250];
} obras;

struct Vendas
{  
  int ingresso;
  char nome[100];
  int idade;
  float preco;
  char formaDePagamento[30];
  struct tm dataHora;
} vendas[1000];

struct tm dataHoraVenda;

int quantidadeTotalObras=0;
int quantidadeTotalIngresso=0;
int ingressoInteiro = 0, ingressoMeia = 0, ingressoIsento = 0;
char confirmacaoDeNomeUsuario[] = "admin";
char confirmacaoSenha[] = "admin";

// ### Protótipos das Funções ###
void gotoxy(int x, int y);
void ExibirLogotipo();
void ExibirMenuPrincipal();
int NumerarIngresso(int ingresso);
void ImprimirDataHoraAtual();
char VerificarFormaDePagamento(int idade, char *formaDePagamento);
float CalcularValorDoIngresso(int idade);
void AutenticarUsuario();
void ExibirMenuAdministrativo();
void AlterarSenha();
void AlterarPrecoIngresso();
void ExibirMenuAcervo();
void AdicionarAcervo();
void ExcluirAcervo();
void ListarAcervo();
  
int main() 
{
  setlocale(LC_ALL, "es_US.UTF-8");
  char opcao;
  do 
  {
    ExibirLogotipo();
    ExibirMenuPrincipal();
    scanf("%c", &opcao);
    getchar();
    fflush(stdin);

    switch(opcao) 
    {
      case '1':
        system("cls");        
        ExibirLogotipo();
        printf("\n\n\t\t\t\t### ** Nova Venda ** ###");
        printf("\n\n\t\t\t--------------- Ingresso %d ---------------\n\n", NumerarIngresso(vendas[quantidadeTotalIngresso].ingresso));
        ImprimirDataHoraAtual();
        printf("\n\t\t\t### Digite o nome: ");
        scanf("\t %[^\n]", &vendas[quantidadeTotalIngresso].nome);
        fflush(stdin);         printf("\t\t\t### Digite a idade: ");
        scanf("%d", &vendas[quantidadeTotalIngresso].idade);        
        getchar();
        VerificarFormaDePagamento(vendas[quantidadeTotalIngresso].idade, vendas[quantidadeTotalIngresso].formaDePagamento);

        vendas[quantidadeTotalIngresso].ingresso = quantidadeTotalIngresso;
        vendas[quantidadeTotalIngresso].preco = CalcularValorDoIngresso(vendas[quantidadeTotalIngresso].idade);

        ingressoInteiro += (vendas[quantidadeTotalIngresso].idade >= 16 && vendas[quantidadeTotalIngresso].idade < 60);
        ingressoMeia += (vendas[quantidadeTotalIngresso].idade < 16);
        ingressoIsento += (vendas[quantidadeTotalIngresso].idade >= 60);
        quantidadeTotalIngresso++;
        break;
      case '2':
        system("cls");
        ExibirLogotipo();
        printf("\n\t\t\t\t** Lista de Vendas **\n\n");
        printf("\t-----------------------------------------------------------------------------------\n");
        for(int i=0; i<quantidadeTotalIngresso; i++)
        {
          printf("\t\t\t###############  Ingresso - %d  ###############\n", (vendas[i].ingresso + 1));
          dataHoraVenda = vendas[i].dataHora;
          printf("\t\t\tData: %02d/%02d/%02d  \t  Horário: %02d:%02d\n",
          dataHoraVenda.tm_mday, dataHoraVenda.tm_mon + 1, dataHoraVenda.tm_year + 1900,
          dataHoraVenda.tm_hour, dataHoraVenda.tm_min);          
          printf("\t\t\tNome: %s\n", vendas[i].nome);
          printf("\t\t\tIdade: %d anos\n", vendas[i].idade);
          printf("\t\t\tPreço: R$%.2f\n", vendas[i].preco);
          printf("\t\t\tTipo Pagamento: %s\n\n", vendas[i].formaDePagamento);
          printf("\t-----------------------------------------------------------------------------------\n");
        }
        getch();
        break;
      case '3':
        system("cls");
        ExibirLogotipo();
        AutenticarUsuario();
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
void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void ExibirLogotipo() 
{
    system("cls");
    gotoxy(30, 2);
    printf("#########################\n");
    gotoxy(30, 3);
    printf("#    **MUSEU TECH**     #");
    gotoxy(30, 4);
    printf("#########################\n");
}
void ExibirMenuPrincipal() 
{
  printf("\n\n\t### ** Menu Principal **");
  printf("\n\n\t### 1. Nova Venda");
  printf("\n\t### 2. Listar Vendas");
  printf("\n\t### 3. Administração");
  printf("\n\t### 0. Sair\n\n\n");
  printf("\t### Digite a opção: ");
}
int NumerarIngresso(int ingresso) 
{
  ingresso = quantidadeTotalIngresso +1;
  return ingresso;
}
void ImprimirDataHoraAtual() 
{
  // Obtém a data e hora atuais
  struct tm *dataHoraAtual;
  time_t segundos;
  time(&segundos);
  dataHoraAtual = localtime(&segundos);

  // Imprime a data e a hora
  printf("\t\t\t### Data: %02d/%02d/%02d  \t  Horário: %02d:%02d ###",
      dataHoraAtual->tm_mday, dataHoraAtual->tm_mon + 1, dataHoraAtual->tm_year + 1900,
      dataHoraAtual->tm_hour, dataHoraAtual->tm_min);
  vendas[quantidadeTotalIngresso].dataHora = *dataHoraAtual;
  dataHoraVenda = *dataHoraAtual;
}
char VerificarFormaDePagamento(int idade, char *formaDePagamento) 
{
  int opcao;
  do 
  {
    if (idade >= 60) 
    {
      strcpy(formaDePagamento, "Isento(a)");
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
      strcpy(formaDePagamento, "Pix");
      break;
    case 2:
      strcpy(formaDePagamento, "Cartão");
      break;
    case 3:
      strcpy(formaDePagamento, "Dinheiro");
      break;
  } 
  return *formaDePagamento;
}
float CalcularValorDoIngresso(int idade) 
{ 
  float meia = 10.00;
  float inteiro = 20.00;
  float isento = 0.00;
  return (idade > 0 && idade <= 16) ? meia : (idade >= 60 && idade <=110) ? isento : inteiro;
}
void AutenticarUsuario()
{
  char senha[20];
  char nomeUsuario[20];
  int tentativas = 3;

  while(tentativas > 0)
  {
    system("cls");
    ExibirLogotipo();
    printf("\n\n\t### Administração - Digite o nome de usuário e a senha para continuar\n\n");
    printf("\t### Nome de Usuário: ");
    scanf("%s",&nomeUsuario);
    printf("\t### Senha: ");
    scanf("%s",&senha);
    fflush(stdin);
    
    if((strcmp(senha, confirmacaoSenha) == 0) && (strcmp(nomeUsuario, confirmacaoDeNomeUsuario) == 0)) 
    {
      printf("\t### Nome de usuário e senha corretos!\n\n\t### Pressione qualquer tecla para continuar");
      getch();
      ExibirMenuAdministrativo();
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
void ExibirMenuAdministrativo() 
{
  char opcao;
  do 
  {    
    system("cls");
    ExibirLogotipo();
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
        ExibirLogotipo();
        printf("\n\n\t\t### Ingressos inteiro: %d\t-\tValor ingressos inteiro: R$%.2f\n", ingressoInteiro, ingressoInteiro*20.00);
        printf("\t\t### Ingressos meia: %d\t\t-\tValor ingressos meia: R$%.2f\n", ingressoMeia, ingressoMeia*10.00);
        printf("\t\t### Ingressos isento: %d\n", ingressoIsento);
        printf("\n\n\t\t### Total de vendas: %d ingressos.\t-\tValor total: R$%.2f", quantidadeTotalIngresso, (ingressoInteiro*20.00+ingressoMeia*10.00));
        getch();
        break;
      case '2':
        system("cls");
        AlterarPrecoIngresso();
        getch();
        break;
      case '3':
        //TODO
        // **Adicionar código para listar os clientes**
        break;
      case '4':
        //TODO
        // **Adicionar código para controle de acervo**
        system("cls");
        ExibirLogotipo();
        ExibirMenuAcervo();

      break;
      case '5':
        system("cls");
        AlterarSenha(confirmacaoSenha);
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

void AlterarSenha()
{
  // Declara as variáveis
  char senhaAtual[20];
  char novoNomeUsuario[20];
  char novaSenha[20];
  char confirmacaoNovoNomeUsuario[20];
  char confirmacaoNovaSenha[20];
  int tentativas = 3;

  // Valida a senha atual
  while(tentativas > 0)
  {
    system("cls");
    ExibirLogotipo();
    printf("\n\n\t### Digite a senha atual: ");
    scanf("%s", &senhaAtual);
    if (strcmp(*senhaAtual, *confirmacaoSenha) != 0) 
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
        scanf("%s", &novoNomeUsuario);

        printf("\t### Confirme o novo nome de usuário: ");
        scanf("%s", &confirmacaoNovoNomeUsuario);

        if (strcmp(novoNomeUsuario, confirmacaoNovoNomeUsuario) != 0) 
        {
          printf("\n\t### Os nomes de usuário não coincidem. Tente novamente.\n");
        }  
      }while (strcmp(novoNomeUsuario, confirmacaoNovoNomeUsuario) != 0);

      do 
      {
        printf("\n\t### Digite a nova senha: ");
        scanf("%s", &novaSenha);

        printf("\t### Confirme a nova senha: ");
        scanf("%s", &confirmacaoNovaSenha);

        if (strcmp(novaSenha, confirmacaoNovaSenha) != 0) 
        {
          printf("\n\t### As senhas não coincidem. Tente novamente.\n");
        }
      }while (strcmp(novaSenha, confirmacaoNovaSenha) != 0);

        // Atribui as novas informações
        strcpy(confirmacaoDeNomeUsuario, novoNomeUsuario);
        strcpy(confirmacaoSenha, novaSenha);

        printf("\n\t### Senha alterada com sucesso!\n");
        getch();
        ExibirMenuAdministrativo();
    }
  }
}
void AlterarPrecoIngresso()
{
  
}
void ExibirMenuAcervo()
{
  char opcao;
  do
  {
    system("cls");
    ExibirLogotipo();
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
        ExibirLogotipo();
        AdicionarAcervo();
        break;
      case '2':
        system("cls");
        ExibirLogotipo();
        ExcluirAcervo();
        fflush(stdin);
        break;
      case '3':
        system("cls");
        ExibirLogotipo();
        ListarAcervo();
        getch();
        break;
      case '0':
        system("cls");
        printf("Voltando ao menu anterior....");
        getch();
        ExibirMenuAdministrativo();
        break;
      default:      
        printf("Opção Inválida");
    }
  } while (opcao != 0);
}
void AdicionarAcervo(){
  FILE * fp;
  obras DadosObras;
  char CadastrarObras;
    
  do
  {
    system("cls");
    ExibirLogotipo();   
    printf("\n\t\t### ** Adicionar Obra ** ###\n\n");    
    printf("\n\t### Nome: ");
    scanf(" %[^\n]", DadosObras.nome);
    printf("\t### Fabricante: ");
    scanf(" %[^\n]", DadosObras.fabricante);
    printf("\t### Data de fabricação: ");
    scanf(" %[^\n]", DadosObras.dataDeFabricacao);
    printf("\t### Importância Histórica: ");
    scanf(" %[^\n]", DadosObras.imporatanciaHistorica);
    printf("\t### Conservação: ");
    scanf(" %[^\n]", DadosObras.conservacao);
    
    quantidadeTotalObras++;
    if(( fp = fopen ("obras.csv", "a+")) == NULL )
    {
      printf("\n\t### Erro na abertura do arquivo obras.csv !\n\n");
      return 1;
    }
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0) 
    {
        fprintf(fp, "Nome, Fabricante, Data de Fabricação, Importância Histórica, Conservação\n");
    }
    fprintf(fp, "%s, %s,%s, %s,%s\n", DadosObras.nome, DadosObras.fabricante, DadosObras.dataDeFabricacao,
                                           DadosObras.imporatanciaHistorica, DadosObras.conservacao);                                          
    fclose(fp);
    do
    {
      printf("\n\t### Deseja Cadastrar outro obra ( S / N ): ");
      scanf(" %c", &CadastrarObras);
      CadastrarObras = toupper(CadastrarObras);
    } while( CadastrarObras != 'S' && CadastrarObras != 'N' );
  } while( CadastrarObras == 'S');
  fflush(stdin);
}
void ExcluirAcervo() 
{
  FILE *fp, *temp;
  char linha[500], nomeExcluir[50];
  int linhaEncontrada = 0;

  printf("Digite o nome da obra que deseja excluir: ");
  scanf(" %[^\n]", nomeExcluir);

  if ((fp = fopen("obras.csv", "r")) == NULL) 
  {
      printf("\n\t### Erro na abertura do arquivo obras.csv !\n\n");
      return;
  }

  if ((temp = fopen("temp.csv", "w")) == NULL) 
  {
      printf("\n\t### Erro na abertura do arquivo temporário !\n\n");
      fclose(fp);
      return;
  }

  // Ignorar a primeira linha, que é o cabeçalho
  fgets(linha, sizeof(linha), fp);
  fputs(linha, temp); // Copiar o cabeçalho para o arquivo temporário

  while (fgets(linha, sizeof(linha), fp) != NULL) 
  {
    char nome[50], fabricante[50], dataDeFabricacao[30], importanciaHistorica[250], conservacao[250];

    // Ler os dados do arquivo
    sscanf(linha, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
            nome, fabricante, dataDeFabricacao, importanciaHistorica, conservacao);

    // Comparar o nome lido com o nome a ser excluído
    if (strcmp(nome, nomeExcluir) == 0) 
    {
        linhaEncontrada = 1; // Marcar que a linha foi encontrada
    } 
    else 
    {
        fputs(linha, temp); // Copiar as outras linhas para o arquivo temporário
    }
  }

  fclose(fp);
  fclose(temp);

  if (!linhaEncontrada) 
  {
      printf("Obra com o nome '%s' não encontrada.\n", nomeExcluir);
      remove("temp.csv"); // Remover o arquivo temporário, já que não houve alterações
  } 
  else 
  {
      remove("obras.csv"); // Remover o arquivo original
      rename("temp.csv", "obras.csv"); // Renomear o arquivo temporário para substituir o original
      printf("Obra com o nome '%s' foi excluída com sucesso.\n", nomeExcluir);
  }
}


void ListarAcervo() 
{
  FILE *fp;
  char linha[500];
  int linhasLidas = 0;

  if ((fp = fopen("obras.csv", "r")) == NULL) 
  {
      printf("\n\t### Erro na abertura do arquivo obras.csv !\n\n");
      return;
  }

  printf("\n\n\t\t\t    ### ** Lista de Obras ** ###\n");

  // Ignorar a primeira linha, que é o cabeçalho
  fgets(linha, sizeof(linha), fp);

  while (fgets(linha, sizeof(linha), fp) != NULL) 
  {
    char nome[50], fabricante[50], dataDeFabricacao[30], importanciaHistorica[250], conservacao[250];

    // Ler os dados do arquivo
    sscanf(linha, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
            &nome, fabricante, dataDeFabricacao, importanciaHistorica, conservacao);

    
    printf("\n\t\t--------------------------------------------------------------------------");
    printf("\n\t\t\t### Nome:\t\t\t  %s", nome);
    printf("\n\t\t\t### Fabricante:\t\t\t %s", fabricante);
    printf("\n\t\t\t### Data de Fabricação:\t\t  %s", dataDeFabricacao);
    printf("\n\t\t\t### Importância Histórica:\t %s", importanciaHistorica);
    printf("\n\t\t\t### Conservação:\t\t  %s", conservacao);
    linhasLidas++;
  }

  fclose(fp);

  if (linhasLidas == 0) 
  {
      printf("\n\n\n\n\n\n\n\t\t\t### Nenhuma obra encontrada. ###");
  }
}




  

