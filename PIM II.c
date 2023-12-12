#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include<time.h>
#include<Windows.h>

// ### Protótipos das Funções ###
void gotoxy(int x, int y);
void GerarLogotipo();
void ExibirMenuPrincipal();
int NumerarIngresso(int ingresso);
void ImprimirDataHoraAtual();
void EfetuarNovaVenda();
char VerificarFormaDePagamento(int idade, char *formaDePagamento);
float CalcularValorDoIngresso(int idade);
void ListarVendas();
void AutenticarUsuario();
void ExibirMenuAdministrativo();
void RelatorioVendas();
void AlterarSenha();

struct Vendas 
{  
  int ingresso;
  char nome[100];
  int idade;
  float preco;
  char formaDePagamento[30];
  struct tm dataHora;
}vendas[1000];

struct tm dataHoraVenda;  
int quantidadeTotalIngresso=0;
int ingressoInteiro = 0, ingressoMeia = 0, ingressoIsento = 0;
char confirmacaoDeNomeUsuario[]= "admin";
char confirmacaoSenha[]="admin";
  
int main() 
{
  setlocale(LC_ALL, "es_US.UTF-8");

  char opcao;

  do 
  {
    GerarLogotipo();
    ExibirMenuPrincipal();
    scanf("%c", &opcao);
    getchar();
    fflush(stdin);

    switch(opcao) 
    {
      case '1':
        system("cls");        
        GerarLogotipo();
        EfetuarNovaVenda();
        break;
      case '2':
        system("cls");
        GerarLogotipo();
        ListarVendas(quantidadeTotalIngresso);
        break;
      case '3':
        system("cls");
        GerarLogotipo();
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
        printf("Opção Inválida! Por favor digite uma opção ente 0 a 3.");
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
void GerarLogotipo() 
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
  printf("\n\n### ** Menu Principal **");
  printf("\n\n### 1. Nova Venda");
  printf("\n### 2. Listar Vendas");
  printf("\n### 3. Administração");
  printf("\n### 0. Sair\n\n\n");
  printf("### Digite a opção: ");
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
  printf("%02d/%02d/%02d    %02d:%02d",
      dataHoraAtual->tm_mday, dataHoraAtual->tm_mon + 1, dataHoraAtual->tm_year + 1900,
      dataHoraAtual->tm_hour, dataHoraAtual->tm_min);
  vendas[quantidadeTotalIngresso].dataHora = *dataHoraAtual;
  dataHoraVenda = *dataHoraAtual;
}
void EfetuarNovaVenda() 
{
  gotoxy(12, 7);
  printf("** Nova Venda **\n");
  gotoxy(10, 9);
  ImprimirDataHoraAtual();
  gotoxy(10, 10);
  printf("---- Ingresso %d ----\n", NumerarIngresso(vendas[quantidadeTotalIngresso].ingresso));
  gotoxy(10, 11);
  printf("Digite o nome: ");
  scanf(" %[^\n]", &vendas[quantidadeTotalIngresso].nome);
  fflush(stdin);
  gotoxy(10, 12);
  printf("Digite a idade: ");
  scanf("%d", &vendas[quantidadeTotalIngresso].idade);
  gotoxy(10, 13);
  getchar();
  VerificarFormaDePagamento(vendas[quantidadeTotalIngresso].idade, vendas[quantidadeTotalIngresso].formaDePagamento);

  vendas[quantidadeTotalIngresso].ingresso = quantidadeTotalIngresso;
  vendas[quantidadeTotalIngresso].preco = CalcularValorDoIngresso(vendas[quantidadeTotalIngresso].idade);

  ingressoInteiro += (vendas[quantidadeTotalIngresso].idade >= 16 && vendas[quantidadeTotalIngresso].idade < 60);
  ingressoMeia += (vendas[quantidadeTotalIngresso].idade < 16);
  ingressoIsento += (vendas[quantidadeTotalIngresso].idade >= 60);
  quantidadeTotalIngresso++;  
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
      gotoxy(10, 14);
      printf("1.Pix | 2.Cartão  | 3.Dinheiro");
      gotoxy(10, 16);
      printf("Forma de Pagamento: ");
      scanf("%d", &opcao);
      getchar();
      if (opcao < 1 || opcao > 3) 
      {
        gotoxy(6, 18);
        printf("Opção Inválida. Por favor digite uma opcão entre 1 e 3");
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
//valorIngresso pode retornar uma string se achar mais fácil para alterar valor do ingresso
float CalcularValorDoIngresso(int idade) 
{ 
  return (idade> 0 && idade <= 16) ? 10.00 : (idade >= 60 && idade <=110) ? 0.00 : 20.00;
}
//TODO: Corrigir a data e a hora, está imprimindo a atual quando deveria estar imprimindo o dia e horário da venda
void ListarVendas() 
{
  GerarLogotipo();
  gotoxy(32, 6);
  printf("** Lista de Vendas **\n");
  printf("------------------------------");
  for(int i=0; i<quantidadeTotalIngresso; i++)
  {
    dataHoraVenda = vendas[i].dataHora;
    printf("\n%02d/%02d/%02d    %02d:%02d\n",
        dataHoraVenda.tm_mday, dataHoraVenda.tm_mon + 1, dataHoraVenda.tm_year + 1900,
        dataHoraVenda.tm_hour, dataHoraVenda.tm_min);
    printf("Ingresso %d\n", (vendas[i].ingresso + 1));
    printf("Nome: %s\n", vendas[i].nome);
    printf("Idade: %d anos\n", vendas[i].idade);
    printf("Preço: R$%.2f\n", vendas[i].preco);
    printf("Tipo Pagamento: %s\n\n", vendas[i].formaDePagamento);
    printf("------------------------------");
  }
  getch();
}

void AutenticarUsuario()
{
  char senha[20];
  char nomeUsuario[20];
  int tentativas = 3;

  while(tentativas > 0)
  {
    system("cls");
    GerarLogotipo();
    printf("\n### Administração - Digite o nome de usuário e a senha para continuar\n\n");
    printf("### Nome de Usuário: ");
    scanf("%s",&nomeUsuario);
    printf("### Senha: ");
    scanf("%s",&senha);
    fflush(stdin);
    
    if((strcmp(senha, confirmacaoSenha) == 0) && (strcmp(nomeUsuario, confirmacaoDeNomeUsuario) == 0)) 
    {
      printf("### Nome de usuário e senha corretos!\n\nPressione qualquer tecla para continuar");
      getch();
      ExibirMenuAdministrativo();
    }
    else 
    {
      tentativas--;
      printf("\nNome de usuário e/ou senha inválidos!\n\n");
      printf("%d tentativas restantes\n\n", tentativas);
      getch();
    }
  }
  if(tentativas == 0)
  {
    printf("Você excedeu o número de tentativas.\n");
    getch();
  }
}
void ExibirMenuAdministrativo() 
{
  char opcao;
  do 
  {    
    system("cls");
    GerarLogotipo();
    printf("\n### ** Administração **\n\n");
    printf("### 1. Relatório de vendas\n");
    printf("### 2. Alterar preço do ingresso\n");
    printf("### 3. Lista de clientes\n");
    printf("### 4. Controle de acervo\n");
    printf("### 5. Aterar Senha\n");
    printf("### 0. Voltar ao menu anterior\n\n\n");
    printf("### Digite a opção: ");
    scanf(" %c", &opcao);
    fflush(stdin);

    switch (opcao) 
    {
      case '1':
        system("cls");
        RelatorioVendas();
        getch();
        break;
      case '2':
        //TODO
        // **Adicionar código para alterar o pre�o dos ingressos**
        break;
      case '3':
        //TODO
        // **Adicionar código para listar os clientes**
        break;
      case '4':
        //TODO
        // **Adicionar código para controle de acervo**
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
void RelatorioVendas()
{
  printf("Total de vendas: %d\n", quantidadeTotalIngresso);
  printf("Valor total das vendas: %.2f\n\n", ingressoInteiro*20.00+ingressoMeia*10.00);
  printf("Total de inteiras: %d\n", ingressoInteiro);
  printf("Valor total de inteiras: %.2f\n\n", ingressoInteiro*20.00);
  printf("Total de meia: %d\n", ingressoMeia);
  printf("Valor total de meia: %.2f\n\n", ingressoMeia*10.00);
  printf("Total de isento: %d\n", ingressoIsento);
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
    printf("Digite a senha atual: ");
    scanf("%s", &senhaAtual);
    if (strcmp(senhaAtual, confirmacaoSenha) != 0) 
    {
      tentativas--;
      printf("A senha atual está incorreta.\n\n");
      printf("%d tentativas restantes\n\n", tentativas);
      getch();
    }
    else
    {
      // Solicita as novas informações
      do
      {
        printf("Digite o novo nome de usuário: ");
        scanf("%s", &novoNomeUsuario);

        printf("Confirme o novo nome de usuário: ");
        scanf("%s", &confirmacaoNovoNomeUsuario);

        if (strcmp(novoNomeUsuario, confirmacaoNovoNomeUsuario) != 0) 
        {
          printf("Os nomes de usuário não coincidem. Tente novamente.\n");
        }  
      }while (strcmp(novoNomeUsuario, confirmacaoNovoNomeUsuario) != 0);

      do 
      {
        printf("Digite a nova senha: ");
        scanf("%s", &novaSenha);

        printf("Confirme a nova senha: ");
        scanf("%s", &confirmacaoNovaSenha);

        if (strcmp(novaSenha, confirmacaoNovaSenha) != 0) 
        {
          printf("As senhas não coincidem. Tente novamente.\n");
        }
      }while (strcmp(novaSenha, confirmacaoNovaSenha) != 0);

        // Atribui as novas informações
        strcpy(confirmacaoDeNomeUsuario, novoNomeUsuario);
        strcpy(confirmacaoSenha, novaSenha);

        printf("Senha alterada com sucesso!\n");
        getch();
        ExibirMenuAdministrativo();
    }
  }
}

  

