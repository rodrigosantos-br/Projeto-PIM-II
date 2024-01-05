#include <stdio.h>

int main() {
    printf("Digite algo na primeira linha: ");
    fflush(stdout); // Garante que a mensagem seja exibida imediatamente

    char input[100];
    fgets(input, sizeof(input), stdin); // Lê a entrada do usuário

    printf("\033[2E"); // Move o cursor para 2 linhas abaixo
    printf("\033[10C"); // Move o cursor para a coluna 10
    printf("Digite algo na próxima linha a partir da coluna 10: ");
    fflush(stdout); // Garante que a mensagem seja exibida imediatamente

    char input2[100];
    fgets(input2, sizeof(input2), stdin); // Lê a próxima entrada do usuário

    return 0;
}
