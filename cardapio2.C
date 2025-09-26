#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define VALOR_MINIMO_DESCONTO 200.00
#define PERCENTUAL_DESCONTO 0.10
#define NUMERO_DE_ITENS 10
#define MAX_ITENS_PEDIDOS 20

// limpa buffer de entrada (stdin)
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// limpar tela
void limparTela(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(void) {
    // cardápio
    const char *Itens[NUMERO_DE_ITENS] = {
        "File a Parmegiana (File empanado com molho de tomate artesanal, gratinado com queijo mussarela, servido com arroz branco e fritas.)",
        "Salmao Grelhado ao Molho de Maracuja (Acompanhado de pure de batata e legumes salteados.)",
        "Risoto de Cogumelos (Arroz arboreo cremoso com cogumelos frescos, finalizado com parmesao.)",
        "Frango ao Curry com Arroz de Coco (Peito de frango ao molho curry suave com arroz de coco aromatico.)",
        "Suco Natural de Laranja ou Abacaxi com Hortela",
        "Refrigerante Lata (Coca Cola, Guarana Antartica ou Dolly Limao.)",
        "Caipirinha Classica (Limao, acucar e cachaca artesanal) tambem na versao sem alcool.",
        "Petit Gateau (Bolinho de chocolate com recheio cremoso, acompanhado de sorvete de creme.)",
        "Cheesecake de Frutas Vermelhas (Base crocante, creme leve de queijo e calda de frutas vermelhas.)",
        "Pave de Limao Siciliano (Sobremesa refrescante e citrica com creme suave.)",
        
    };

    const double precos[NUMERO_DE_ITENS] = {
        54.99, 69.90, 48.50, 42.00, 8.00, 6.00, 15.00 ,22.00, 18.50, 19.00, 
    };
    

    const char *Categorias[NUMERO_DE_ITENS] = {
        "Pratos Principais", "Pratos Principais", "Pratos Principais", "Pratos Principais",
        "Bebidas", "Bebidas", "Bebidas",
        "Sobremesas", "Sobremesas", "Sobremesas",
        
    };

    // variáveis de controle
    int menuOpcao = -1;
    double total = 0.0;
    int pedidoItens[MAX_ITENS_PEDIDOS];
    int contadorPedidos = 0;

    do {
        limparTela();
        printf("========================================\n");
        printf("Seja Bem-Vindo ao Restaurante Rodrigues Gastronomia\n");
        printf("======================================== \n");
        printf("Menu principal \n");
        printf("======================================== \n");
        printf("1. Ver Cardapio\n");
        printf("2. Sobre o restaurante\n");
        printf("0. Sair do Programa\n");
        printf("======================================== \n");
        printf(">> Escolha uma opcao: ");

        if (scanf("%d", &menuOpcao) != 1) {
            limparBufferEntrada();
            menuOpcao = -1;
        } else {
            limparBufferEntrada();
        }
        
        switch (menuOpcao) {
            case 1: {
                // Inicia novo pedido
                total = 0.0;
                contadorPedidos = 0; 
                int categoriaOpcao = -1;
           
                do {
                    limparTela();
                    printf("--- CATEGORIAS ---\n");
                    printf("1. Pratos Principais\n");
                    printf("2. Bebidas\n");
                    printf("3. Sobremesas\n");
                    printf("--------------------\n");
                    printf("0. Finalizar Pedido e Ver a Conta\n\n");
                    printf("Total Parcial: R$ %.2f\n", total);
                    printf(">> Escolha uma categoria: ");

                    if (scanf("%d", &categoriaOpcao) != 1) {
                        limparBufferEntrada();
                        categoriaOpcao = -1;
                    } else {
                        limparBufferEntrada();
                    }

                    const char *categoriaEscolhida = NULL;
                    if (categoriaOpcao == 1) categoriaEscolhida = "Pratos Principais";
                    else if (categoriaOpcao == 2) categoriaEscolhida = "Bebidas";
                    else if (categoriaOpcao == 3) categoriaEscolhida = "Sobremesas";

                    if (categoriaOpcao >= 1 && categoriaOpcao <= 3) {
                        limparTela();
                        printf("--- %s ---\n", categoriaEscolhida);
                        for (int i = 0; i < NUMERO_DE_ITENS; ++i) {
                            if (strcmp(Categorias[i], categoriaEscolhida) == 0) {
                                printf("%d. %s - R$ %.2f\n", i + 1, Itens[i], precos[i]);
                            }
                        }

                        printf("--------------------\n");
                        printf(">> Digite o codigo do item (ou 0 para voltar as categorias): ");

                        int itemOpcao;
                        if (scanf("%d", &itemOpcao) != 1) {
                            limparBufferEntrada();
                            itemOpcao = -1;
                        } else {
                            limparBufferEntrada();
                        }

                        if (itemOpcao > 0 && itemOpcao <= NUMERO_DE_ITENS) {
                            int indice = itemOpcao - 1;
                            if (strcmp(Categorias[indice], categoriaEscolhida) == 0) {
                                if (contadorPedidos < MAX_ITENS_PEDIDOS) {
                                    total += precos[indice];
                                    pedidoItens[contadorPedidos++] = itemOpcao;
                                    printf("\nAdicionado: %s\n", Itens[indice]);
                                } else {
                                    printf("\n[ERRO] Limite de itens no pedido atingido (%d).\n", MAX_ITENS_PEDIDOS);
                                }
                            } else {
                                printf("\n[ERRO] Esse item não pertence a categoria selecionada.\n");
                            }
                        } else if (itemOpcao != 0) {
                            printf("\n[ERRO] Codigo de item invalido.\n");
                        }

                        printf("\nPressione Enter para continuar...");
                        getchar();
                    } else if (categoriaOpcao != 0) {
                        printf("\n[ERRO] Categoria invalida. Pressione Enter para continuar...");
                        getchar();
                    }

                } while (categoriaOpcao != 0);

                // Resumo do pedido
                limparTela();
                printf("\n--- RESUMO DO PEDIDO ---\n\n");

                if (contadorPedidos == 0) {
                    printf("Nenhum item foi selecionado.\n");
                } else {
                    printf("Itens Consumidos:\n");
                    for (int i = 0; i < contadorPedidos; ++i) {
                        int itemID = pedidoItens[i];
                        int indice = itemID - 1;
                        printf("- %-35s R$ %6.2f\n", Itens[indice], precos[indice]);
                    }
                    printf("\n--------------------------------------------\n");
                    printf("Subtotal: R$ %.2f\n", total);

                    if (total >= VALOR_MINIMO_DESCONTO) {
                        double valorDesconto = total * PERCENTUAL_DESCONTO;
                        double totalComDesconto = total - valorDesconto;
                        printf("Desconto (%.0f%%): - R$ %.2f\n", PERCENTUAL_DESCONTO * 100.0, valorDesconto);
                        printf("--------------------------------------------\n");
                        printf("TOTAL A PAGAR: R$ %.2f\n", totalComDesconto);
                    } else {
                        printf("--------------------------------------------\n");
                        printf("TOTAL A PAGAR: R$ %.2f\n", total);
                    }
                }

                printf("\nObrigado por seu pedido!\n\n");
                printf("Pressione Enter para voltar ao menu principal...");
                getchar();

                break;
            }

            case 2:
                limparTela();
                printf("--- SOBRE O RESTAURANTE RODRIGUES ---\n\n");
                printf("Fundado em 2025, o Restaurante Rodrigues e um projeto de\n");
                printf("cardapio digital desenvolvido com a linguagem C.\n\n");
                printf("Pressione Enter para voltar ao menu principal...");
                getchar();
                break;

            case 0:
                printf("\nObrigado por visitar o Restaurante Rodrigues. Volte sempre!\n");
                break;

            default:
                printf("\n[ERRO] Opção inválida! Pressione Enter para tentar novamente.");
                getchar();
                break;
        }

    } while (menuOpcao != 0);

    return 0;
}








