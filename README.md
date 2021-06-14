# Alocação de Viaturas 🚔📍

Este trabalho tem como objetivo propor a implementação de um modelo matemático de localização de viaturas policiais, que seja capaz de minimizar o custo de instalação de viaturas afim de reduzir a incidência de ocorrências criminais.

Objetivando resolver o problema, foi utilizado o modelo baseados no problema de p-medianas, considerando as caraterísticas do problema. O modelo foi implementado utilizando a linguagem C++ e resolvido via solver CPLEX 20.1.

Os resultados permitiram comprovar o funcionamento do modelo com soluções aplicadas a pequenas e médias instâncias de forma a reduzir o custo de distância entre os vértices.

## Modelo Matemático

O modelo matemático do problema de localização de facilidades com limites para o número de instalações abertas é considerado como um problema de programação inteira binária.

O problema de p-medianas tem como objetivo determinar p locais (medianas) em uma rede de nós **N** com a finalidade de minimizar a soma das distâncias entre cada nó até a sua mediana mais próxima.

Sabendo disso, os dados relevantes para o problema são:
- N: número finito de pontos de demanda (pontos estratégicos)
- P: número finito de candidatos a instalação de facilidades (viaturas policiais)
- cij: distâncias entre os pontos de demanda e o número P de viaturas (ou postos policiais) a serem alocados
- xij: matriz de alocação (variável de decisão binária)

## Execução

A execução do algoritmo é feita através de terminal usando o comando *make* concatenado com o executável do arquivo compilado *main* juntamente com o nome do arquivo texto que representa a instância, que é o primeiro argumento.

O arquivo [Makefile](./Makefile) garante a compilação do algoritmo e é encarregado de encontrar a biblioteca CPLEX na versão 20.1 na máquina. Caso o CPLEX não tenha sido localizado no caminho padrão (*/opt/ibm/ILOG/CPLEX\_Studio201*), sua configuração deve ser feita manualmente diretamente no arquivo Makefile.

Para executar com a instância 4x4 por exemplo:
```shell
make && ./main instancia4.txt
```

## Relatório

Para um relatório mais detalhado, verificar [este arquivo](./relatorio.pdf)
