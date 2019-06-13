# MC458 Laboratorio

## Compilação e Execução

Para o programa compilar basta digitar `make` na raiz do projeto. Para executar o programa você deve digitar `./solver` com as seguintes flags:
* `-i nome_do_arquivo`: onde nome_do_arquivo deve ser o arquivo de entrada que representa a instância a ser resolvida pelo programa.
* `-a algoritmo`: onde algoritmo é uma string que pode ser **A** ou **B** e denota o algoritmo que deve ser utilizado para resolver o problema.
* `-g`: essa flag é opcional, caso você coloque ela, seu programa irá gerar um arquivo **out.pdf** que contém uma visualização da solução encontrada pelo seu algoritmo. Para que a visualização funcione você deve ter o [graphviz](https://www.graphviz.org/download/) instalado em sua máquina.
* `-t tempo`: essa flag é opcional, caso você coloque ela, seu programa deverá ter um tempo limite de tempo para executar. Caso você não coloque essa flag, o tempo limite será de **60 segundos**.

Por exemplo, se digitarmos `./solver -i test.in -a A -g` iremos executar o algoritmo de programação dinâmica *“Bottom-Up”* para resolver a instância test.in com o tempo limite de 60 segundos, além disso, o programa também vai gerar uma visualização no arquivo out.pdf.

**Obs.:** Caso precise utilizar um debugger, você também pode compilar o código com o comando `make debug`.
