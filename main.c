#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char modelo[50];
    char fabricante[50];
    int anoFabricacao;
    char placa[10];
    char cor[20];
    char dataEntrada[20];
    char dataVenda[20];
    float valor;
    char observacoes[100];
    int condicao;
} Carro;

typedef struct {
    char cpf[12];
    char nome[50];
    float salario;
    char dataNascimento[20];
    float percentualVenda;
} Vendedor;

typedef struct {
    char cpf[12];
    int matricula;
    char nome[50];
    char endereco[100];
} Cliente;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserir_carro() {
    Carro novoCarro;
    printf("Modelo: ");
    fgets(novoCarro.modelo, sizeof(novoCarro.modelo), stdin);
    printf("Fabricante: ");
    fgets(novoCarro.fabricante, sizeof(novoCarro.fabricante), stdin);
    printf("Ano de Fabricação: ");
    scanf("%d", &novoCarro.anoFabricacao);
    clear_input_buffer();
    printf("Placa: ");
    fgets(novoCarro.placa, sizeof(novoCarro.placa), stdin);
    printf("Cor: ");
    fgets(novoCarro.cor, sizeof(novoCarro.cor), stdin);
    printf("Data de Entrada: ");
    fgets(novoCarro.dataEntrada, sizeof(novoCarro.dataEntrada), stdin);
    printf("Data de Venda: ");
    fgets(novoCarro.dataVenda, sizeof(novoCarro.dataVenda), stdin);
    printf("Valor: ");
    scanf("%f", &novoCarro.valor);
    clear_input_buffer();
    printf("Observações: ");
    fgets(novoCarro.observacoes, sizeof(novoCarro.observacoes), stdin);
    printf("Condição (1 - Não Vendido, 0 - Vendido): ");
    scanf("%d", &novoCarro.condicao);
    clear_input_buffer();

    FILE *arquivo = fopen("carros.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&novoCarro, sizeof(Carro), 1, arquivo);

    fclose(arquivo);

    printf("Carro inserido com sucesso.\n");
}

void inserir_cliente() {
    Cliente novoCliente;
    printf("CPF: ");
    fgets(novoCliente.cpf, sizeof(novoCliente.cpf), stdin);
    printf("Matrícula: ");
    scanf("%d", &novoCliente.matricula);
    clear_input_buffer();
    printf("Nome: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    printf("Endereço: ");
    fgets(novoCliente.endereco, sizeof(novoCliente.endereco), stdin);

    FILE *arquivo = fopen("clientes.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);

    fclose(arquivo);

    printf("Cliente inserido com sucesso.\n");
}

void inserir_vendedor() {
    Vendedor novoVendedor;
    printf("CPF: ");
    fgets(novoVendedor.cpf, sizeof(novoVendedor.cpf), stdin);
    printf("Nome: ");
    fgets(novoVendedor.nome, sizeof(novoVendedor.nome), stdin);
    printf("Salário: ");
    scanf("%f", &novoVendedor.salario);
    clear_input_buffer();
    printf("Data de Nascimento: ");
    fgets(novoVendedor.dataNascimento, sizeof(novoVendedor.dataNascimento), stdin);
    printf("Percentual de Venda: ");
    scanf("%f", &novoVendedor.percentualVenda);
    clear_input_buffer();

    FILE *arquivo = fopen("vendedores.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&novoVendedor, sizeof(Vendedor), 1, arquivo);

    fclose(arquivo);

    printf("Vendedor inserido com sucesso.\n");
}

void listar_carros() {
    FILE *arquivo = fopen("carros.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Carro carro;

    printf("\033[1;34m\n=== Lista de Carros ===\033[m\n\n");

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        printf("Modelo: %s", carro.modelo);
        printf("Fabricante: %s", carro.fabricante);
        printf("Ano de Fabricação: %d\n", carro.anoFabricacao);
        printf("Placa: %s", carro.placa);
        printf("Cor: %s", carro.cor);
        printf("Data de Entrada: %s", carro.dataEntrada);
        printf("Data de Venda: %s", carro.dataVenda);
        printf("Valor: %.2f\n", carro.valor);
        printf("Observações: %s", carro.observacoes);
        printf("Condição: %d\n", carro.condicao);
        printf("\n");
    }

    fclose(arquivo);
}

void listar_clientes() {
    FILE *arquivo = fopen("clientes.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;

    printf("\033[1;34m\n=== Lista de Clientes ===\033[m\n\n");

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        printf("CPF: %s", cliente.cpf);
        printf("Matrícula do Cliente: %d\n", cliente.matricula);
        printf("Nome: %s", cliente.nome);
        printf("Endereço: %s", cliente.endereco);
        printf("\n");
    }

    fclose(arquivo);
}

void listar_vendedores() {
    FILE *arquivo = fopen("vendedores.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vendedor vendedor;

    printf("\n\033[1;34m=== Lista de Vendedores ===\033[m\n\n");

    while (fread(&vendedor, sizeof(Vendedor), 1, arquivo) == 1) {
        printf("CPF: %s", vendedor.cpf);
        printf("Nome: %s", vendedor.nome);
        printf("Salário: %.2f\n", vendedor.salario);
        printf("Data de Nascimento: %s", vendedor.dataNascimento);
        printf("Percentual de Venda: %.2f\n", vendedor.percentualVenda);
        printf("\n");
    }

    fclose(arquivo);
}

void consultar_carro_por_ano() {
    int ano;
    printf("Digite o ano de fabricação: ");
    scanf("%d", &ano);
    clear_input_buffer();

    FILE *arquivo = fopen("carros.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Carro carro;
    int encontrou = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (carro.anoFabricacao == ano) {
            encontrou = 1;
            printf("Modelo: %s", carro.modelo);
            printf("Fabricante: %s", carro.fabricante);
            printf("Ano de Fabricação: %d\n", carro.anoFabricacao);
            printf("Placa: %s", carro.placa);
            printf("Cor: %s", carro.cor);
            printf("Data de Entrada: %s", carro.dataEntrada);
            printf("Data de Venda: %s", carro.dataVenda);
            printf("Valor: %.2f\n", carro.valor);
            printf("Observações: %s", carro.observacoes);
            printf("Condição: %d\n", carro.condicao);
            printf("\n");
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum carro encontrado para o ano de fabricação %d.\n", ano);
    }
}

void consultar_carro_por_modelo() {
    char modelo[50];
    printf("Digite o modelo do carro: ");
    fgets(modelo, sizeof(modelo), stdin);

    FILE *arquivo = fopen("carros.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Carro carro;
    int encontrou = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcmp(carro.modelo, modelo) == 0) {
            encontrou = 1;
            printf("Modelo: %s", carro.modelo);
            printf("Fabricante: %s", carro.fabricante);
            printf("Ano de Fabricação: %d\n", carro.anoFabricacao);
            printf("Placa: %s", carro.placa);
            printf("Cor: %s", carro.cor);
            printf("Data de Entrada: %s", carro.dataEntrada);
            printf("Data de Venda: %s", carro.dataVenda);
            printf("Valor: %.2f\n", carro.valor);
            printf("Observações: %s", carro.observacoes);
            printf("Condição: %d\n", carro.condicao);
            printf("\n");
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum carro encontrado para o modelo %s.\n", modelo);
    }
}

void consultar_carro_por_placa() {
    char placa[10];
    printf("Digite a placa do carro: ");
    fgets(placa, sizeof(placa), stdin);

    FILE *arquivo = fopen("carros.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Carro carro;
    int encontrou = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcmp(carro.placa, placa) == 0) {
            encontrou = 1;
            printf("Modelo: %s", carro.modelo);
            printf("Fabricante: %s", carro.fabricante);
            printf("Ano de Fabricação: %d\n", carro.anoFabricacao);
            printf("Placa: %s", carro.placa);
            printf("Cor: %s", carro.cor);
            printf("Data de Entrada: %s", carro.dataEntrada);
            printf("Data de Venda: %s", carro.dataVenda);
            printf("Valor: %.2f\n", carro.valor);
            printf("Observações: %s", carro.observacoes);
            printf("Condição: %d\n", carro.condicao);
            printf("\n");
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum carro encontrado para a placa %s.\n", placa);
    }
}

void alterar_carro() {
    char placa[10];
    printf("Digite a placa do carro a ser alterado: ");
    fgets(placa, sizeof(placa), stdin);

    FILE *arquivo = fopen("carros.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Carro carro;
    int encontrou = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcmp(carro.placa, placa) == 0) {
            encontrou = 1;

            printf("Atual: %sNova Cor: ", carro.cor);
            fgets(carro.cor, sizeof(carro.cor), stdin);
            printf("Atual: %sNova Data de Entrada: ", carro.dataEntrada);
            fgets(carro.dataEntrada, sizeof(carro.dataEntrada), stdin);
            printf("Atual: %sNova Data de Venda: ", carro.dataVenda);
            fgets(carro.dataVenda, sizeof(carro.dataVenda), stdin);
            printf("Atual: %.2f\nNovo Valor: ", carro.valor);
            scanf("%f", &carro.valor);
            clear_input_buffer();
            printf("Atual: %sNovas Observações: ", carro.observacoes);
            fgets(carro.observacoes, sizeof(carro.observacoes), stdin);
            printf("Atual: %d\nNova Condição: ", carro.condicao);
            scanf("%d", &carro.condicao);
            clear_input_buffer();

            fseek(arquivo, -sizeof(Carro), SEEK_CUR);
            fwrite(&carro, sizeof(Carro), 1, arquivo);
            printf("Carro alterado com sucesso.\n");
            break;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum carro encontrado para a placa %s.\n", placa);
    }
}

void alterar_cliente() {
    char cpf[12];
    printf("Digite o CPF do cliente a ser alterado: ");
    fgets(cpf, sizeof(cpf), stdin);

    FILE *arquivo = fopen("clientes.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;
    int encontrou = 0;

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (strcmp(cliente.cpf, cpf) == 0) {
            encontrou = 1;

            printf("Atual: %sNovo Endereço: ", cliente.endereco);
            fgets(cliente.endereco, sizeof(cliente.endereco), stdin);

            fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, arquivo);
            printf("Cliente alterado com sucesso.\n");
            break;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum cliente encontrado para o CPF %s.\n", cpf);
    }
}

void alterar_vendedor() {
    char cpf[12];
    printf("Digite o CPF do vendedor a ser alterado: ");
    fgets(cpf, sizeof(cpf), stdin);

    FILE *arquivo = fopen("vendedores.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vendedor vendedor;
    int encontrou = 0;

    while (fread(&vendedor, sizeof(Vendedor), 1, arquivo) == 1) {
        if (strcmp(vendedor.cpf, cpf) == 0) {
            encontrou = 1;

            printf("Atual: %.2f\nNovo Salário: ", vendedor.salario);
            scanf("%f", &vendedor.salario);
            clear_input_buffer();
            printf("Atual: %.2f\nNovo Percentual de Venda: ", vendedor.percentualVenda);
            scanf("%f", &vendedor.percentualVenda);
            clear_input_buffer();

            fseek(arquivo, -sizeof(Vendedor), SEEK_CUR);
            fwrite(&vendedor, sizeof(Vendedor), 1, arquivo);
            printf("Vendedor alterado com sucesso.\n");
            break;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhum vendedor encontrado para o CPF %s.\n", cpf);
    }
}

void remover_carro() {
    char placa[10];
    printf("Digite a placa do carro a ser removido: ");
    fgets(placa, sizeof(placa), stdin);

    FILE *arquivo = fopen("carros.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Carro carro;
    int encontrou = 0;

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcmp(carro.placa, placa) == 0) {
            encontrou = 1;
        } else {
            fwrite(&carro, sizeof(Carro), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("carros.bin");
    rename("temp.bin", "carros.bin");

    if (encontrou) {
        printf("Carro removido com sucesso.\n");
    } else {
        printf("Nenhum carro encontrado para a placa %s.\n", placa);
    }
}

void remover_cliente() {
    char cpf[12];
    printf("Digite o CPF do cliente a ser removido: ");
    fgets(cpf, sizeof(cpf), stdin);

    FILE *arquivo = fopen("clientes.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;
    int encontrou = 0;

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (strcmp(cliente.cpf, cpf) == 0) {
            encontrou = 1;
        } else {
            fwrite(&cliente, sizeof(Cliente), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("clientes.bin");
    rename("temp.bin", "clientes.bin");

    if (encontrou) {
        printf("Cliente removido com sucesso.\n");
    } else {
        printf("Nenhum cliente encontrado para o CPF %s.\n", cpf);
    }
}

void remover_vendedor() {
    char cpf[12];
    printf("Digite o CPF do vendedor a ser removido: ");
    fgets(cpf, sizeof(cpf), stdin);

    FILE *arquivo = fopen("vendedores.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Vendedor vendedor;
    int encontrou = 0;

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    while (fread(&vendedor, sizeof(Vendedor), 1, arquivo) == 1) {
        if (strcmp(vendedor.cpf, cpf) == 0) {
            encontrou = 1;
        } else {
            fwrite(&vendedor, sizeof(Vendedor), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("vendedores.bin");
    rename("temp.bin", "vendedores.bin");

    if (encontrou) {
        printf("Vendedor removido com sucesso.\n");
    } else {
        printf("Nenhum vendedor encontrado para o CPF %s.\n", cpf);
    }
}

int main() {
    int opcao;

    do {
        printf("\033[32;1m====== Trabalho Final de C ======\033[m\n");
        printf("1.  Inserir Carro\n");
        printf("2.  Inserir Cliente\n");
        printf("3.  Inserir Vendedor\n");
        printf("4.  Listar Carros\n");
        printf("5.  Listar Clientes\n");
        printf("6.  Listar Vendedores\n");
        printf("7.  Consultar Carro por Ano\n");
        printf("8.  Consultar Carro por Modelo\n");
        printf("9.  Consultar Carro por Placa\n");
        printf("10. Alterar Carro\n");
        printf("11. Alterar Cliente\n");
        printf("12. Alterar Vendedor\n");
        printf("13. Remover Carro\n");
        printf("14. Remover Cliente\n");
        printf("15. Remover Vendedor\n");
        printf("0.  Sair\n");
        printf("\033[32;1m=================================\033[m\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        clear_input_buffer();

        switch (opcao) {
            case 1:
                inserir_carro();
                break;
            case 2:
                inserir_cliente();
                break;
            case 3:
                inserir_vendedor();
                break;
            case 4:
                listar_carros();
                break;
            case 5:
                listar_clientes();
                break;
            case 6:
                listar_vendedores();
                break;
            case 7:
                consultar_carro_por_ano();
                break;
            case 8:
                consultar_carro_por_modelo();
                break;
            case 9:
                consultar_carro_por_placa();
                break;
            case 10:
                alterar_carro();
                break;
            case 11:
                alterar_cliente();
                break;
            case 12:
                alterar_vendedor();
                break;
            case 13:
                remover_carro();
                break;
            case 14:
                remover_cliente();
                break;
            case 15:
                remover_vendedor();
                break;
            case 0:
                printf("\033[31;1mEncerrando o programa.\033[m\n");
                break;
            default:
                printf("Opção inválida. Digite novamente.\n");
                break;
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}
