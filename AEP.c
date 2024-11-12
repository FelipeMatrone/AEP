#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define arquivoNAME "usuarios.txt"
#define MAX_NAME_LENGTH  50
#define MAX_senha_LENGTH 50
#define SHIFT_KEY 7  

char usuarios[50][MAX_NAME_LENGTH ]; 
char senhas  [50][MAX_senha_LENGTH];  
int conta = 0;  

void senha_crypto(char *senha) {
	int i = 0; 
    for (i; senha[i] != '\0'; i++) {
        senha[i] += SHIFT_KEY;  
    }
}
void senha_descrypto(char *senha) {
	int i = 0;
    for (i; senha[i] != '\0'; i++) {
        senha[i] -= SHIFT_KEY;  
    }
}

void Usuarios() {
	
    FILE *arquivo = fopen(arquivoNAME, "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado!\n");
    return;
    }
    while (fgets(usuarios[conta], sizeof(usuarios[conta]), arquivo) != NULL) {
        usuarios[conta][strcspn(usuarios[conta], "\n")] = '\0';  

        if (fgets(senhas[conta], sizeof(senhas[conta]), arquivo) != NULL) {
            senhas[conta][strcspn(senhas[conta], "\n")] = '\0';  
            
        senha_descrypto(senhas[conta]);  
        conta++;
        }
    }
    fclose(arquivo);
}

void usu_salvos() {
    FILE *arquivo = fopen(arquivoNAME, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }
    
    int i = 0;
    
    for (i; i < conta; i++) {
        senha_crypto(senhas[i]); 
        fprintf(arquivo, "%s\n%s\n", usuarios[i], senhas[i]);
        senha_descrypto(senhas[i]);  
    }
    fclose(arquivo);
}

void registrar() {
	
     printf("Digite o nome de usuario: ");
     fgets(usuarios[conta], sizeof(usuarios[conta]), stdin);
     usuarios[conta][strcspn(usuarios[conta], "\n")] = 0;
    
     printf("Digite a senha: ");
     fgets(senhas[conta], sizeof(senhas[conta]), stdin);  
     senhas[conta][strcspn(senhas[conta], "\n")] = 0;  

     senha_crypto(senhas[conta]);  

     conta++;
    
     printf("Usuario cadastrado com sucesso!\n");
     system("cls");
     usu_salvos();
}

void listagem() {
    if (conta == 0) {
    
        printf("Nenhum usuario cadastrado no sistema! \n");
        return;
    }
    printf("Estes sao os usuarios cadastrados no sistema: \n");

    int i = 0;
    
    for (i; i < conta; i++) {
        printf("%d. %s\n", i + 1, usuarios[i]);
        
    }
}

void deletar() {
	
    char usu_codigo[MAX_NAME_LENGTH];
    char senha[MAX_senha_LENGTH];
    
    printf("Digite o nome de usuario a ser excluido: ");
    fgets(usu_codigo, sizeof(usu_codigo), stdin);  
    usu_codigo[strcspn(usu_codigo, "\n")] = 0;  

    int i;
    
    for (i = 0; i < conta; i++) {
        if (strcmp(usuarios[i], usu_codigo) == 0) {
            printf("Digite a senha para confirmar a exclusao: ");
            fgets(senha, sizeof(senha), stdin);
            senha[strcspn(senha, "\n")] = 0;
            
            senha_crypto(senha); 
            
            if (strcmp(senhas[i], senha) == 0) {  // Verifica se a senha está correta
                int j;
                for (j = i; j < conta - 1; j++) {
                    strcpy(usuarios[j], usuarios[j + 1]);
                    strcpy(senhas[j], senhas[j + 1]);
                }
                conta--; 
                
                usu_salvos();  
                printf("Usuario foi excluido com sucesso!\n");
                return;
            } else {
                printf("Senha incorreta. Nao foi possivel fazer a exclusao do usuario!\n");
              return;
            }
        }
    }
    printf("Usuario nao foi encontrado.\n");
}


void login() {
	
    char usu_codigo[MAX_NAME_LENGTH ];
    char senha     [MAX_senha_LENGTH];
    int login_sucesso = 0;  
    int tentativas    = 0;     

    while (!login_sucesso && tentativas < 3) {
    	
        printf("Digite o nome de usuario: ");
        fgets(usu_codigo, sizeof(usu_codigo), stdin);  
        usu_codigo[strcspn(usu_codigo, "\n")] = 0;  

        printf("Digite a senha: ");
        fgets(senha, sizeof(senha), stdin);  
        senha[strcspn(senha, "\n")] = 0;  
        senha_crypto(senha); 
        
        int i = 0;
        
        for (i; i < conta; i++) {
            if (strcmp(usuarios[i], usu_codigo) == 0 && strcmp(senhas[i], senha) == 0) {
                printf("Login bem-sucedido! Bem-vindo, %s.\n", usu_codigo);
                login_sucesso = 1; 
            return;
            }
        }
        tentativas++;  
        printf("Nome de usuario ou senha incorretos. Tentativa %d de 3.\n", tentativas);
    }
    if (tentativas == 3) {
        printf("Numero de tentaivas excedeu o limte! Seu acesso foi bloqueado! \n");
    }
}

int main() {
	
    Usuarios();  

    int op;

    printf("Bem-vindo ao nosso software! Esperamos que tenha uma boa experiencia! Escolha uma das opcoes abaixo!\n\n");
    printf("1) Cadastrar usuario    \n");
    printf("2) Login                \n");
    printf("3) Listagem de usuarios \n");
    printf("4) Excluir Usuario      \n");

    scanf("%d", &op);
    system("cls");
    getchar();  

    if (op == 1) {
        registrar();
    } else if (op == 2) {
        login();
    } else if (op == 3) {
        listagem();
    } else if (op == 4) {
        deletar();
    } else {
        printf("Opcao invalida!\n");
    }
return 0;

//Desenvolvido por: 
//Gustavo Chaves RA: 24021306-2 
//Felipe Matrone RA: 24051005-2
}

