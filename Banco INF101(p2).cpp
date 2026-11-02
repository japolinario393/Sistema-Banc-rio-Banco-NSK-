#include <iostream>
#include <string>

using namespace std;

int main() {
    const int MAX_CONTAS = 100;

    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    int quantidadeContas = 0;

    const int MAX_MOVIMENTACOES = 500;
    int contaMovimentacao[MAX_MOVIMENTACOES];
    char tipoMovimentacao[MAX_MOVIMENTACOES];
    double valorMovimentacao[MAX_MOVIMENTACOES];
    int quantidadeMovimentacoes = 0;
    
    int opcao;

    do {
        cout << "\n ****************** SISTEMA BANCARIO FASE 2 **************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Listar contas cadastradas\n";
        cout << "3 - Consultar conta\n";
        cout << "4 - Realizar deposito\n";
        cout << "5 - Realizar saque\n";
        cout << "6 - Exibir extrato\n";
        cout << "7 - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                if (quantidadeContas < MAX_CONTAS) {
                    cout << "Numero da conta: ";
                    cin >> numeroConta[quantidadeContas];
                    
                    cout << "Nome do cliente: ";
                    cin.ignore();
                    getline(cin, nomeCliente[quantidadeContas]);
                    
                    cout << "CPF: ";
                    cin >> cpf[quantidadeContas];
                    
                    cout << "Saldo inicial: R$ ";
                    cin >> saldo[quantidadeContas];
                    
                    quantidadeContas++;
                    cout << "Conta cadastrada com sucesso!\n";
                } else {
                    cout << "Limite de contas atingido!\n";
                }
                break;
            }

            case 2: {
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada.\n";
                } else {
                    cout << "\n--- CONTAS CADASTRADAS ---\n";
                    for (int i = 0; i < quantidadeContas; i++) {
                        cout << "Conta: " << numeroConta[i] 
                             << " | Nome: " << nomeCliente[i] 
                             << " | Saldo: R$ " << saldo[i] << "\n";
                    }
                }
                break;
            }

            case 3: {
                int busca;
                cout << "Digite o numero da conta: ";
                cin >> busca;

                int idx = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == busca) {
                        idx = i;
                        break;
                    }
                }

                if (idx != -1) {
                    cout << "Conta: " << numeroConta[idx] << "\n";
                    cout << "Nome: " << nomeCliente[idx] << "\n";
                    cout << "CPF: " << cpf[idx] << "\n";
                    cout << "Saldo: R$ " << saldo[idx] << "\n";
                } else {
                    cout << "Conta nao encontrada!\n";
                }
                break;
            }

            case 4: {
                int busca;
                double valor;
                cout << "Digite o numero da conta para deposito: ";
                cin >> busca;

                int idx = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == busca) {
                        idx = i;
                        break;
                    }
                }

                if (idx != -1) {
                    cout << "Valor do deposito: R$ ";
                    cin >> valor;
                    if (valor > 0) {
                        saldo[idx] += valor;
                        
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[idx];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Deposito realizado com sucesso!\n";
                    } else {
                        cout << "Valor invalido!\n";
                    }
                } else {
                    cout << "Conta nao encontrada!\n";
                }
                break;
            }

            case 5: {
                int busca;
                double valor;
                cout << "Digite o numero da conta para saque: ";
                cin >> busca;

                int idx = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == busca) {
                        idx = i;
                        break;
                    }
                }

                if (idx != -1) {
                    cout << "Valor do saque: R$ ";
                    cin >> valor;
                    if (valor > 0 && saldo[idx] >= valor) {
                        saldo[idx] -= valor;

                        // Registra movimentação
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[idx];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Saque realizado com sucesso!\n";
                    } else {
                        cout << "Saldo insuficiente ou valor invalido!\n";
                    }
                } else {
                    cout << "Conta nao encontrada!\n";
                }
                break;
            }

            case 6: {
                int busca;
                cout << "Digite o numero da conta para ver o extrato: ";
                cin >> busca;

                cout << "\n--- EXTRATO DA CONTA " << busca << " ---\n";
                for (int i = 0; i < quantidadeMovimentacoes; i++) {
                    if (contaMovimentacao[i] == busca) {
                        if (tipoMovimentacao[i] == 'D') {
                            cout << "Deposito: R$ " << valorMovimentacao[i] << "\n";
                        } else if (tipoMovimentacao[i] == 'S') {
                            cout << "Saque: R$ " << valorMovimentacao[i] << "\n";
                        }
                    }
                }
                cout << "--------------------------------\n";
                break;
            }

            case 7: {
                cout << "Saindo....\n";
                break;
            }

            default: {
                cout << "Opcao invalida, digite novamente\n";
                break;
            }
        }

    } while (opcao != 7);

    return 0;
}