#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>

#include <ilcplex/ilocplex.h>

using namespace std;

int main(int argc, char *argv[]) {
    // lendo nome da instancia por parametro
    string arquivo_instancia = argv[1];

    // ambiente (environment)
    IloEnv ambiente;

    // numero de medianas
    IloInt p;

    // declaracao matriz de distancias (2 dimensoes)
    IloArray<IloNumArray> c(ambiente);

    // ---- Leitura de arquivo
    ifstream arquivo(arquivo_instancia.c_str());

	if (!arquivo) {
		cerr << "Erro na leitura do arquivo!!!" << endl;
	}

    // ler matriz de distancias
    arquivo >> c;

    // ler o numero de medianas
    arquivo >> p;

    // numero de vertices (nós) pegando o tamanho dinamicamente
    IloInt n = c.getSize();

    // matriz de alocação
    IloArray<IloNumVarArray> x(ambiente, n);

    // declara modelo matematico
    IloModel modelo(ambiente);

    // variavel de decisao (matriz binaria)
    for (int i = 0;i < n; i++) {
        x[i] = IloNumVarArray(ambiente, n, 0, 1, ILOBOOL);
    }

    // ---- Funcao Objetivo

    IloExpr fo(ambiente);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fo += c[i][j] * x[i][j];
        }
    }
    // adiciona funcao objetivo ao modelo
    modelo.add(IloMinimize(ambiente, fo));

    // ---- Restricoes

    /*
        Restrição: 1b
        assegurar que cada vertice xj seja atendido por apenas uma mediana
    */
    for (int i = 0; i < n; i++) {
        IloExpr restricao_1b(ambiente);
        for (int j = 0; j < n; j++) {
            restricao_1b += x[i][j];
        }
        modelo.add(restricao_1b == 1);
    }

    /*
        Restrição: 1c
        Garante que a quantidade de medianas é igual a p
    */
    IloExpr restricao_1c(ambiente);

    for (int j = 0; j < n; j++) {
        restricao_1c += x[j][j];
    }
    modelo.add(restricao_1c == p);
    restricao_1c.end();


    /*
        Restrição: 1d
        certifica que cada v ertice j seja designado a um vertice i
        desde que xjj = 1
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            modelo.add(x[i][j] <= x[j][j]);
        }
    }

    // ---- Resolvendo modelo
    IloCplex cplex(modelo);
    cplex.exportModel("viatura.lp");

    if (cplex.solve()) {
        ambiente.out() << "\n-> Resultado Modelo: " << cplex.getStatus() << endl;
        ambiente.out() << "\n-> Menor Custo: " << cplex.getObjValue() << endl;
        ambiente.out() << "\n-> N: " << n << endl;
		ambiente.out() << "\n-> P: " << p << endl;

        cout << "\n~> Matriz de alocação: \n" << endl;
        
        // printa matriz de alocacao convertendo
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				cout << bool(cplex.getValue(x[i][j])) << " ";
			}
			cout << endl;
		}
	} else {
        cout << "Erro ao resolver modelo!" << endl;
    }

    ambiente.end();
    return 0;
}
