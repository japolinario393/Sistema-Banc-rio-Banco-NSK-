#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CONTAS = 100;
const int MAX_MOV = 1000;

// ---------- Arrays das contas ----------
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];      // 1 = corrente, 2 = poupança
double saldo[MAX_CONTAS];
int contaAtiva[MAX_CONTAS];     // 1 = ativa, 0 = inativa
int quantidadeContas = 0;

// ---------- Arrays das movimentações ----------
int contaMovimentacao[MAX_MOV];
char tipoMovimentacao[MAX_MOV]; // D = depósito, S = saque
double valorMovimentacao[MAX_MOV];
int quantidadeMovimentacoes = 0;

// ---------- Funções de arquivo ----------
void carregarContas() {
    ifstream arquivo("contas.txt");
    if (!arquivo.is_open()) {
        return; // primeira execução: ainda não existe arquivo
    }
    string linha;
    while (getline(arquivo, linha) && quantidadeContas < MAX_CONTAS) {
        if (linha == "") continue;
        stringstream ss(linha);
        string campo;
        int i = quantidadeContas;

        getline(ss, campo, ';'); numeroConta[i] = stoi(campo);
        getline(ss, nomeCliente[i], ';');
        getline(ss, cpf[i], ';');
        getline(ss, campo, ';'); tipoConta[i] = stoi(campo);
        getline(ss, campo, ';'); saldo[i] = stod(campo);
        getline(ss, campo, ';'); contaAtiva[i] = stoi(campo);

        quantidadeContas++;
    }
    arquivo.close();
}

void salvarContas() {
    ofstream arquivo("contas.txt");
    if (arquivo.is_open()) {
        arquivo << fixed << setprecision(2);
        for (int i = 0; i < quantidadeContas; i++) {
            arquivo << numeroConta[i] << ";"
                    << nomeCliente[i] << ";"
                    << cpf[i] << ";"
                    << tipoConta[i] << ";"
                    << saldo[i] << ";"
                    << contaAtiva[i] << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao salvar contas.txt!" << endl;
    }
}

void carregarMovimentacoes() {
    ifstream arquivo("movimentacoes.txt");
    if (!arquivo.is_open()) {
        return;
    }
    string linha;
    while (getline(arquivo, linha) && quantidadeMovimentacoes < MAX_MOV) {
        if (linha == "") continue;
        stringstream ss(linha);
        string campo;
        int i = quantidadeMovimentacoes;

        getline(ss, campo, ';'); contaMovimentacao[i] = stoi(campo);
        getline(ss, campo, ';'); tipoMovimentacao[i] = campo[0];
        getline(ss, campo, ';'); valorMovimentacao[i] = stod(campo);

        quantidadeMovimentacoes++;
    }
    arquivo.close();
}

void salvarMovimentacoes() {
    ofstream arquivo("movimentacoes.txt");
    if (arquivo.is_open()) {
        arquivo << fixed << setprecision(2);
        for (int i = 0; i < quantidadeMovimentacoes; i++) {
            arquivo << contaMovimentacao[i] << ";"
                    << tipoMovimentacao[i] << ";"
                    << valorMovimentacao[i] << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao salvar movimentacoes.txt!" << endl;
    }
}

// ---------- Funções auxiliares ----------
int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) return i;
    }
    return -1;
}

void registrarMovimentacao(int numero, char tipo, double valor) {
    if (quantidadeMovimentacoes >= MAX_MOV) {
        cout << "Limite de movimentacoes atingido!" << endl;
        return;
    }
    contaMovimentacao[quantidadeMovimentacoes] = numero;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;
    quantidadeMovimentacoes++;
}

void mostrarConta(int i) {
    cout << "Conta: " << numeroConta[i] << endl;
    cout << "Cliente: " << nomeCliente[i] << endl;
    cout << "CPF: " << cpf[i] << endl;
    cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << endl;
    cout << "Saldo: R$ " << fixed << setprecision(2) << saldo[i] << endl;
    cout << "Situacao: " << (contaAtiva[i] == 1 ? "Ativa" : "Inativa") << endl;
}

// ---------- Funcionalidades ----------
void cadastrarConta() {
    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Limite de contas atingido!" << endl;
        return;
    }
    int i = quantidadeContas;

    // número automático: continua a partir da última conta
    if (i == 0) numeroConta[i] = 1001;
    else numeroConta[i] = numeroConta[i - 1] + 1;

    cin.ignore();
    cout << "Nome do cliente: ";
    getline(cin, nomeCliente[i]);
    cout << "CPF: ";
    getline(cin, cpf[i]);

    do {
        cout << "Tipo da conta (1 - Corrente, 2 - Poupanca): ";
        cin >> tipoConta[i];
    } while (tipoConta[i] != 1 && tipoConta[i] != 2);

    saldo[i] = 0;
    contaAtiva[i] = 1;
    quantidadeContas++;

    salvarContas();
    cout << "Conta cadastrada! Numero: " << numeroConta[i] << endl;
}

void listarContas() {
    if (quantidadeContas == 0) {
        cout << "Nenhuma conta cadastrada." << endl;
        return;
    }
    for (int i = 0; i < quantidadeContas; i++) {
        cout << "-----------------------" << endl;
        mostrarConta(i);
    }
}

void consultarConta() {
    int numero;
    cout << "Numero da conta: ";
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    mostrarConta(i);
}

void depositar() {
    int numero;
    double valor;
    cout << "Numero da conta: ";
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    if (contaAtiva[i] == 0) {
        cout << "Conta inativa!" << endl;
        return;
    }
    cout << "Valor do deposito: ";
    cin >> valor;
    if (valor <= 0) {
        cout << "Valor invalido!" << endl;
        return;
    }
    saldo[i] += valor;
    registrarMovimentacao(numero, 'D', valor);
    salvarContas();
    salvarMovimentacoes();
    cout << "Deposito realizado!" << endl;
}

void sacar() {
    int numero;
    double valor;
    cout << "Numero da conta: ";
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    if (contaAtiva[i] == 0) {
        cout << "Conta inativa!" << endl;
        return;
    }
    cout << "Valor do saque: ";
    cin >> valor;
    if (valor <= 0) {
        cout << "Valor invalido!" << endl;
        return;
    }
    if (valor > saldo[i]) {
        cout << "Saldo insuficiente!" << endl;
        return;
    }
    saldo[i] -= valor;
    registrarMovimentacao(numero, 'S', valor);
    salvarContas();
    salvarMovimentacoes();
    cout << "Saque realizado!" << endl;
}

void transferir() {
    int origem, destino;
    double valor;
    cout << "Conta de origem: ";
    cin >> origem;
    cout << "Conta de destino: ";
    cin >> destino;

    int io = buscarConta(origem);
    int id = buscarConta(destino);
    if (io == -1 || id == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    if (origem == destino) {
        cout << "As contas devem ser diferentes!" << endl;
        return;
    }
    if (contaAtiva[io] == 0 || contaAtiva[id] == 0) {
        cout << "Uma das contas esta inativa!" << endl;
        return;
    }
    cout << "Valor da transferencia: ";
    cin >> valor;
    if (valor <= 0) {
        cout << "Valor invalido!" << endl;
        return;
    }
    if (valor > saldo[io]) {
        cout << "Saldo insuficiente!" << endl;
        return;
    }
    saldo[io] -= valor;
    saldo[id] += valor;
    registrarMovimentacao(origem, 'S', valor);  // saída na origem
    registrarMovimentacao(destino, 'D', valor); // entrada no destino
    salvarContas();
    salvarMovimentacoes();
    cout << "Transferencia realizada!" << endl;
}

void exibirExtrato() {
    int numero;
    cout << "Numero da conta: ";
    cin >> numero;
    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    cout << "===== EXTRATO - Conta " << numero << " (" << nomeCliente[i] << ") =====" << endl;
    bool achou = false;
    for (int j = 0; j < quantidadeMovimentacoes; j++) {
        if (contaMovimentacao[j] == numero) {
            cout << (tipoMovimentacao[j] == 'D' ? "Deposito/Entrada: R$ " : "Saque/Saida:      R$ ")
                 << fixed << setprecision(2) << valorMovimentacao[j] << endl;
            achou = true;
        }
    }
    if (!achou) cout << "Sem movimentacoes." << endl;
    cout << "Saldo atual: R$ " << fixed << setprecision(2) << saldo[i] << endl;
}

// ---------- Programa principal ----------
int main() {
    carregarContas();
    carregarMovimentacoes();

    int opcao;
    do {
        cout << "\n===== BANCO INF101 PT: 3 =====" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Listar contas" << endl;
        cout << "3 - Consultar conta" << endl;
        cout << "4 - Depositar" << endl;
        cout << "5 - Sacar" << endl;
        cout << "6 - Transferir" << endl;
        cout << "7 - Extrato" << endl;
        cout << "8 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: listarContas(); break;
            case 3: consultarConta(); break;
            case 4: depositar(); break;
            case 5: sacar(); break;
            case 6: transferir(); break;
            case 7: exibirExtrato(); break;
            case 0: cout << "Encerrando..." << endl; break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);

    return 0;
}