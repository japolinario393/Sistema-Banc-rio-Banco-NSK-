#include <iostream>
#include <string>
using namespace std;

const int MAX_CONTAS = 5; // limite de contas cadastradas

// Vetores paralelos: a posicao i de cada vetor pertence a mesma conta
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];      // 1 = Corrente; 2 = Poupanca
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int totalContas = 0;            // quantas contas ja foram cadastradas

// Procura uma conta pelo numero. Retorna a posicao ou -1 se nao achar.
int buscarConta(int numero) {
    for (int i = 0; i < totalContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

int main() {
    int opcao;

    do {
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Consultar conta" << endl;
        cout << "3 - Verificar saldo" << endl;
        cout << "4 - Alterar tipo da conta" << endl;
        cout << "5 - Ativar/Desativar conta" << endl;
        cout << "6 - Sair" << endl;
        cout << "Digite uma opcao: ";
        cin >> opcao;

        // O switch fica DENTRO do do-while, para rodar a cada repeticao do menu
        switch (opcao) {

            case 1: { // ---------- CADASTRAR ----------
                if (totalContas >= MAX_CONTAS) {
                    cout << "Limite de " << MAX_CONTAS << " contas atingido!" << endl;
                    break;
                }

                int i = totalContas; // posicao livre
                int numero;

                cout << "Numero da conta: ";
                cin >> numero;
                if (numero <= 0) {
                    cout << "Erro: o numero da conta deve ser maior que zero." << endl;
                    break;
                }
                if (buscarConta(numero) != -1) {
                    cout << "Erro: ja existe uma conta com esse numero." << endl;
                    break;
                }
                numeroConta[i] = numero;

                cin.ignore(); // limpa o Enter que sobrou antes do getline
                cout << "Nome do titular: ";
                getline(cin, nomeCliente[i]);

                cout << "CPF do titular: ";
                getline(cin, cpf[i]);

                cout << "Tipo da conta (1 = Corrente, 2 = Poupanca): ";
                cin >> tipoConta[i];
                if (tipoConta[i] != 1 && tipoConta[i] != 2) {
                    cout << "Erro: tipo de conta invalido." << endl;
                    break;
                }

                cout << "Saldo inicial: ";
                cin >> saldo[i];
                if (saldo[i] < 0) {
                    cout << "Erro: o saldo inicial nao pode ser negativo." << endl;
                    break;
                }

                contaAtiva[i] = true; // toda conta nova nasce ativa
                totalContas++;        // so conta como cadastrada se passou nas validacoes
                cout << "Conta cadastrada com sucesso!" << endl;
                break;
            }

            case 2: { // ---------- CONSULTAR ----------
                int numero;
                cout << "Numero da conta: ";
                cin >> numero;
                int i = buscarConta(numero);

                if (i == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else {
                    cout << "\n--- Dados da conta ---" << endl;
                    cout << "Numero: " << numeroConta[i] << endl;
                    cout << "Titular: " << nomeCliente[i] << endl;
                    cout << "CPF: " << cpf[i] << endl;
                    cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << endl;
                    cout << "Saldo: R$ " << saldo[i] << endl;
                    cout << "Situacao: " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
                }
                break;
            }

            case 3: { // ---------- VERIFICAR SALDO ----------
                int numero;
                cout << "Numero da conta: ";
                cin >> numero;
                int i = buscarConta(numero);

                if (i == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else if (!contaAtiva[i]) {
                    cout << "Operacao negada: a conta esta inativa." << endl;
                } else {
                    cout << "Saldo atual: R$ " << saldo[i] << endl;
                }
                break;
            }

            case 4: { // ---------- ALTERAR TIPO ----------
                int numero;
                cout << "Numero da conta: ";
                cin >> numero;
                int i = buscarConta(numero);

                if (i == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else if (!contaAtiva[i]) {
                    cout << "Operacao negada: a conta esta inativa." << endl;
                } else {
                    int novoTipo;
                    cout << "Novo tipo (1 = Corrente, 2 = Poupanca): ";
                    cin >> novoTipo;
                    if (novoTipo != 1 && novoTipo != 2) {
                        cout << "Erro: tipo de conta invalido." << endl;
                    } else {
                        tipoConta[i] = novoTipo;
                        cout << "Tipo da conta alterado com sucesso!" << endl;
                    }
                }
                break;
            }

            case 5: { // ---------- ATIVAR / DESATIVAR ----------
                int numero;
                cout << "Numero da conta: ";
                cin >> numero;
                int i = buscarConta(numero);

                if (i == -1) {
                    cout << "Conta nao encontrada." << endl;
                } else {
                    contaAtiva[i] = !contaAtiva[i]; // inverte o valor
                    cout << "Conta agora esta " << (contaAtiva[i] ? "ATIVA" : "INATIVA") << "." << endl;
                }
                break;
            }

            case 6:
                cout << "Saindo do sistema. Ate logo!" << endl;
                break;

            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }

    } while (opcao != 6);

    return 0;
}
