# li31617tp
Projeto de LI3 16/17

# Introdução
O objetivo deste projeto é criar um sistema que permita analisar artigos pre-
sentes em backups da Wikipedia, realizados em diversos momentos temporais
e extrair informação útil bem como dados estatı́sticos dos mesmos. Para tal,
utilizámos diferentes estruturas de dados que nos permitiram dar resposta
em tempo útil às queries propostas.
Este trabalho envolve duas versões semelhantes, sendo que uma é escrita em C e outra em Java.

# Desenho
Neste projeto respondemos a vários tipos de queries. Tendo em conta a
natureza das mesmas, foi necessária uma abordagem que visa conjugar da
melhor maneira a utilização de memória central e o tempo de resposta do
sistema.

## Abordagem
Deparamo-nos com várias abordagens possı́veis no que diz respeito à com-
plexidade de tempo e espaço do sistema.
O objetivo do sistema é efetuar o load de uma lista de backups e o utili-
zador poder retirar toda a informação que desejar dessa lista, chamando as
queries quantas vezes pretender tendo como garantia uma rápida resposta às
mesmas.
Optamos por priveligiar o tempo de resposta das queries sacrificando,
assim, o tempo de load tentando gerir da melhor maneira os recursos dis-
ponı́veis. Posto isto, decidimos carregar toda a informação necessária de
uma só vez.
Para cada backup da wikipédia é feito o parsing de cada artigo individu-
almente, com o auxı́lio da biblioteca libxml2 (em C) e da API StAX (em Java) . Os vários tipos de informação
são organizados e carregados nas respetivas estruturas que, por fim, poderão
ser acedidos de forma eficiente aquando da chamada das várias queries.

![Diagrama do projeto em C](http://i.imgur.com/IDyEz4V.png "Diagrama do projeto em C")

![Diagrama do projeto em Java](http://i.imgur.com/3unyLnV.png "Diagrama do projeto em Java")

Tal como mencionado em cima, utilizamos a biblioteca StAX para realizar
o parsing do XML em Java. Esta usa o modelo de pull Streaming invés do modelo
DOM. Este modelo permite um menor uso da memória, menos requisitos
de processamento e, por vezes, maior performance. No entanto, apenas te-
mos acesso ao elemento onde nos encontramos que, após iterarmos para o
próximo, é descartado e recolhido pelo garbage collector.
O processo de parsing está ordenado da forma apresentada no seguinte dia-
grama.

## Estruturas
Para responder a queries de procura não ordenada utlizamos tabelas de hash (HashMap's)
por nos permitirem pesquisas em tempo constante. Para queries que im-
pliquem ordenação utilizamos árvores balanceadas de procura (TreeSet's), que propor-
cionam acesso a dados ordenados em tempo logaritmico. Utilizamos ainda
como estruturas auxiliares listas ligadas (ArrayList's) que permitem manter um pequeno
registo de dados ordenados.

# Desempenho
Para conseguirmos apresentar um sistema não só funcional mas também efi-
caz na forma como apresenta os resultados tivemos em grande conta o de-
sempenho por ele apresentado.
Como dito anteriormente, priorizámos o tempo em função da memória uti-
lizando assim estruturas que nos permitiram obter uma rápida resposta às
queries

## Tempo
O tempo de resposta foi um dos aspectos que mais pesou na conceção deste
projeto e na forma como foi conduzido. Para melhor percebermos as razões
da nossa decisão são apresentados os tempos de execução de cada uma das
queries solicitadas.


![Desempenho programa C](http://i.imgur.com/7Ovw5Fz.png "Desempenho programa C")

![Desempenho programa Java](http://i.imgur.com/oVbWOBJ.png "Desempenho programa Java")

## Paralelização
Para conseguir minimizar os tempos, principalmente no parsing que eram os
mais custosos, e obter assim os resultados apresentados utilizámos parale-
lização tendo em conta as arquiteturas multicore dos processadores atuais.
Para proceder à paralelização do código utilizámos o OpenMP no caso do 
programa em C e parallel Streams em Java.

# Conclusão
A implementação deste sistema cumpre com os objetivos pretendidos com
um desempenho dentro do previsto, no entanto talvez seja possı́vel fazer
uma melhor gestão dos recursos.
No que toca ao tempo de resposta das queries, à exceção da query número
9 (titles with prefix ) que se desviou dos restantes resultados, conseguimos ob-
ter resultados bastante favoráveis o que nos leva a crer que seguimos uma
boa abordagem do problema, no entanto ainda existe muito por onde melho-
rar. Uma possı́vel melhoria consiste na implementação de uma Radix Tree
ou Prefix Tree que, como o nome indica, permite a ordenação dos artigos por
prefixo que não foi efetuada devido ao peso que esta nova estrutura iria ter
em termos de espaço utilizado e à escassez de tempo.
Em respeito ao programa em Java, encontramos também uma certa dificuldade em compreender como uti-
lizar o diferente modelo de parsing, onde são necessárias mais iterações do
que o normal e o conteúdo referente a uma tag encontra-se num elemento
diferente do da própria tag. Contudo, após alguma pesquisa sobre o assunto,
chegamos à conclusão que a sua implementação não foi de tanta dificuldade
como aparentava. Quanto ao restante, criar, preencher e aceder às estruturas,
foi tarefa fácil, graças à vasta biblioteca da linguagem Java.
O código é modular, encontra-se bem dividido, documentado e estrutu-
rado. Respeita a abstração de dados ao utilizador e a API pretendida.
