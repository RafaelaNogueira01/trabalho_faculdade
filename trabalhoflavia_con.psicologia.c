#include <stdio.h>
#include <stdlib.h>               
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    int idade;								
    char diagnostico[100];
} Paciente;

Paciente *pacientes = NULL; 		 
int total_pacientes = 0;  			

void cadastrar_paciente();          
void consultar_paciente();			 
void gerar_relatorio();				
void excluir_paciente();			
int main() {         
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
                consultar_paciente();                                                  
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
                printf("Opcao invalida. Tente novamente.\n");                    
        }
    } while (opcao != 5);     // vai repetir ate o usuario digitar 5(sair)
    free(pacientes);         
    return 0;
}


void cadastrar_paciente() {
    pacientes = realloc(pacientes, (total_pacientes + 1) * sizeof(Paciente));                      
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
    scanf("%d", &p.idade);                                                                
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
            printf("Nome: %s\n", pacientes[i].nome);                                          
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
        printf("Nome: %s\n", pacientes[i].nome);												
        printf("Idade: %d\n", pacientes[i].idade);
        printf("Diagnostico: %s\n\n", pacientes[i].diagnostico);
    }
}

void excluir_paciente() {                           
    int id, encontrado = 0;
    printf("Digite o ID do paciente para exclusao: ");          
    scanf("%d", &id);

    for (int i = 0; i < total_pacientes; i++) {
        if (pacientes[i].id == id) {                                     
            encontrado = 1;													
            for (int j = i; j < total_pacientes - 1; j++) {       
                pacientes[j] = pacientes[j + 1];									
            }
            total_pacientes--;
            pacientes = realloc(pacientes, total_pacientes * sizeof(Paciente));                        
            printf("Paciente com ID %d excluido com sucesso.\n", id);
            break;
        }
    }

    if (!encontrado) {
        printf("Paciente com ID %d nao encontrado.\n", id);                      
    }
}
