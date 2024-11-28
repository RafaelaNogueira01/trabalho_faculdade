#include <stdio.h>
#include <stdlib.h>                 // o trabalho apresenta um sistema simples feito para gerenciar um consultorio de psicologia.
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    int idade;						// aqui, é a estrutura que contem os dados do sistema 		
    char diagnostico[100];
} Paciente;

Paciente *pacientes = NULL; 		// declara um ponteiro para armazenar uma lista de pacientes de forma dinamica. NULL pq nao tem nenhuma memoria alocada ainda 
int total_pacientes = 0;  			// variavel criada para armazenar o numero de pacientes. no momento é 0;


void cadastrar_paciente();          // funcao para cadatsrar pacientes 
void consultar_paciente();			// funcao para consultar pacientes 
void gerar_relatorio();				// funcao para gerar relatoriosn
void excluir_paciente();			// funcao para  excluir paciente 

int main() {         // interage com o usuario 
    int opcao;

    do {
        printf("\n--- Consultorio de Psicologia ---\n");
        printf("1. Cadastro de Paciente\n");
        printf("2. Consultar Paciente\n");
        printf("3. Gerar Relatorio\n");
        printf("4. Excluir Paciente\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                cadastrar_paciente();
                break;
            case 2:
                consultar_paciente();                                                  // essa parte é a interacao com o usuario, ele pode escolher as opcoes.
                break;
            case 3:
                gerar_relatorio();
                break;
            case 4:
                excluir_paciente();
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");                    // se caso ele nao escolher nenhuma das opçoes 
        }
    } while (opcao != 5);     // vai repetir ate o usuario digitar 5(sair)
    free(pacientes);         
    return 0;
}


void cadastrar_paciente() {
    pacientes = realloc(pacientes, (total_pacientes + 1) * sizeof(Paciente));         // ajusta o tamanho do array para incluir mais um paciente             
    if (pacientes == NULL) {
        printf("Erro ao alocar memoria para novos pacientes.\n");
        return;
    }

    Paciente p;
    p.id = total_pacientes + 1;               

    printf("Digite o nome do paciente: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = 0; 
 
    printf("Digite a idade do paciente: ");
    scanf("%d", &p.idade);                                                                 // essa parte adiciona um paciente a lista 
    getchar(); 

    printf("Digite o diagnostico do paciente: ");
    fgets(p.diagnostico, sizeof(p.diagnostico), stdin);
    p.diagnostico[strcspn(p.diagnostico, "\n")] = 0; 
    pacientes[total_pacientes++] = p;
    printf("Paciente cadastrado com sucesso!\n");
}

void consultar_paciente() {
    int id;
    printf("Digite o ID do paciente para consulta: ");
    scanf("%d", &id);

    for (int i = 0; i < total_pacientes; i++) {
        if (pacientes[i].id == id) {
            printf("\n--- Paciente %d ---\n", id);
            printf("Nome: %s\n", pacientes[i].nome);                                          // exibe os dados do paciente especifico atraves do ID
            printf("Idade: %d\n", pacientes[i].idade);
            printf("Diagnostico: %s\n", pacientes[i].diagnostico);
            return;
        }
    }

    printf("Paciente com ID %d nao encontrado.\n", id);
}

void gerar_relatorio() {
    printf("\n--- Relatorio de Pacientes ---\n");
    for (int i = 0; i < total_pacientes; i++) {
        printf("ID: %d\n", pacientes[i].id);
        printf("Nome: %s\n", pacientes[i].nome);												// exibe todos os pacientes da lista com os dados e um resumo de cada caso
        printf("Idade: %d\n", pacientes[i].idade);
        printf("Diagnostico: %s\n\n", pacientes[i].diagnostico);
    }
}

void excluir_paciente() {                           //exclui pacientes atraves do id 
    int id, encontrado = 0;
    printf("Digite o ID do paciente para exclusao: ");          //procura o paciente pelo ID.
    scanf("%d", &id);

    for (int i = 0; i < total_pacientes; i++) {
        if (pacientes[i].id == id) {                                     
            encontrado = 1;													//Move os pacientes seguintes para preencher a lacuna. (espaço no array)
            for (int j = i; j < total_pacientes - 1; j++) {       
                pacientes[j] = pacientes[j + 1];									
            }
            total_pacientes--;
            pacientes = realloc(pacientes, total_pacientes * sizeof(Paciente));                        // Reduz o total de pacientes e ajusta a memória.
            printf("Paciente com ID %d excluido com sucesso.\n", id);
            break;
        }
    }

    if (!encontrado) {
        printf("Paciente com ID %d nao encontrado.\n", id);                       //Exibe mensagem de sucesso e encerra.
    }
}