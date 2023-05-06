// Bibliotecas.
#include "C:\sqlite-libs\sqlite3.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Conta o números de retornos da query.
int rows;
// Função de callback para exibir retornos da query.
/**
 * callback: É uma função que é chamada como argumento de uma outra função.
 * *NotUsed: Parâmentro padrão da documentação do SQLite, ponteiro vazio.
 * argc: Contagem do número de atributos do registro.
 * **argv: Conjunto de dados em formado de ponteiro do ponteiro. Quando você junta 2 ponteiros simulo uma matriz.
 * **azColName: O mesmo de argv, mas invés de conter os dados da query, vai conter o nome dos atributos do registro.
 * ?: É um inlineif, um if else que cabe em uma linha só. Se for true retorna o primeiro campo, se for false retorna o segundo campo.
*/
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    // Incrementa a contagem do número de linhas retornadas pela query.
   rows++;
   // Percorre os atributos retornados pela query para exibir os dados do registro.
   for(int i = 0; i < argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
// callback2: Faz a contagem de registros retornadas pela query. Esse callback apenas exibe os dados.
static int callback2(void *NotUsed, int argc, char **argv, char **azColName) {
    // Incrementando para contar os registros da query.
   rows++;
   return 0;
}
// Chamada principal.
int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    // Armazena uma mensagem de erro que eu não quis exibir.
    char *zErrMsg = 0;
    // Ponteiro que referencia o DB que estou utilizando.
    sqlite3* DB;
    // Váriável noobinha para saber se o banco vai dar liga.
    int erro = 0;
    erro = sqlite3_open("C:\\ProjetoC#\\crud-csharp\\db\\banco_estudantes.db", &DB);
    if (erro) {
        printf("Erro ao abrir o DB! \n");
        return -1;
    }
    int sair, op;
    // Variável de controle para o while não rodar infinitamente.
    sair = 0;
    int ID;
    char sql[250];
    char nome[50], nome_pai[50], endereco[50];
    while (!sair)
    {
        printf("\nEscolha uma opção: \n\n");
        printf("1) Listar todos os alunos \n");
        printf("2) Buscar aluno pelo ID \n");
        printf("3) Inserir novo aluno \n");
        printf("4) Remover um aluno \n");
        printf("5) Atualizar dados do aluno \n");
        printf("6) Sair \n\n");
        printf(">> ");
        // &: scanf lê um decimal digitado pelo usuário e salva no endereço de memória de op.
        scanf("%d", &op);
        switch (op)
        {
            case 1:
                // strcopy é uma função para copiar o conteúdo de texto para dentro de uma variável.
                // Está jogando o meu texto de select para dentro de sql.
                printf("\nAlunos listados: \n\n");
                strcpy(sql, "SELECT * from Students");
                // Executa a SQL no banco.
                sqlite3_exec(DB, sql, callback, 0, &zErrMsg);
                break;
            case 2:
                // rows é resetado antes de contar quantos itens o select achou.
                rows = 0;
                printf("\nDigite o ID: ");
                scanf("%i", &ID);
                printf("\nInformações do ID: \n\n");
                // sprintf junta dentro de SQL uma nova query formatada.
                // sprintf formata uma string para dentro de uma variável.
                sprintf(sql, "SELECT * from Students WHERE ID = %i", ID);
                sqlite3_exec(DB, sql, callback, 0, &zErrMsg);
                // Se rows for 0, siginifica que o usuário fez besteira.
                if (rows == 0)
                {
                    printf("\nNenhum usuário com esse ID! \n");
                }
                break;
            case 3:
                // getchar pega um caractere que está em um buffer de entrada porque isso atrapalharia a execução do case.
                getchar();
                printf("\nDigite o nome do aluno: ");
                // gets tem uma leitura mais completa, evita ter que ficar formatando.
                gets(nome);
                printf("Digite o nome do pai do aluno: ");
                gets(nome_pai);
                printf("Digite o endereço do aluno: ");
                gets(endereco);
                // Insere uma nova entrada no DB.
                // \"%s\": É uma string que vai ficar entre aspas dentro da query. É uma formatação.
                sprintf(sql, "INSERT INTO Students (Name, FatherName, Address) VALUES (\"%s\", \"%s\", \"%s\"); ", nome, nome_pai, endereco);
                sqlite3_exec(DB, sql, callback, 0, &zErrMsg);
                printf("\nO aluno foi inserido com sucesso! \n");
                break;
            case 4:
                rows = 0;
                getchar();
                printf("\nDigite o ID do aluno que deseja remover: ");
                scanf("%i", &ID);
                // Para remover verificar se o ID existe.
                sprintf(sql, "SELECT * from Students WHERE ID = %i", ID);
                sqlite3_exec(DB, sql, callback2, 0, &zErrMsg);
                // Se o usuário digitar um registro inválido apenas exige a mensagem de erro.
                if (rows == 0)
                {
                    printf("\nNenhum usuário com esse ID! \n");
                } else {
                    sprintf(sql, "DELETE from Students WHERE ID = %i", ID);
                    sqlite3_exec(DB, sql, 0, 0, &zErrMsg);
                    printf("\nRegistro apagado com sucesso! \n\n");
                }
                break;
            case 5:
                rows = 0;
                getchar();
                printf("\nDigite o ID do aluno que deseja atualizar: ");
                scanf("%i", &ID);
                // É preciso selecionar para atualizar.
                sprintf(sql, "SELECT * from Students WHERE ID = %i", ID);
                sqlite3_exec(DB, sql, callback2, 0, &zErrMsg);
                if (rows == 0)
                {
                    printf("\nNenhum usuário com esse ID! \n");
                } else {
                    getchar();
                    printf("\nDigite o nome do aluno: ");
                    gets(nome);
                    printf("Digite o nome do pai do aluno: ");
                    gets(nome_pai);
                    printf("Digite o endereço do aluno: ");
                    gets(endereco);
                    // Formata a query de update e faz o update.
                    sprintf(sql, "UPDATE Students set Name=\"%s\", FatherName=\"%s\", Address=\"%s\" WHERE ID = %i", nome, nome_pai, endereco, ID);
                    sqlite3_exec(DB, sql, 0, 0, &zErrMsg);
                    printf("\nRegistro atualizado com sucesso! \n\n");
                }
                break;
            case 6: 
                sair = 1;
                printf("\nVocê saiu do programa!");
                return 0;
                break;
            default:
                printf("\nOpção inválida!\n");
        }
        printf("\n");
        system("pause");
    }
    // Fecha o DB.
    sqlite3_close(DB);
    return 0;
}
