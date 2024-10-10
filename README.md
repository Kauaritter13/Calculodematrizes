# Calculadora De Matrizes em C
No meu programa, implementei uma calculadora de matrizes que permite
realizar várias operações, como adição, subtração, multiplicação,
transposição e até mesmo o cálculo da inversa de matrizes! 🎉💻

Comecei definindo uma estrutura chamada Matrix, que armazena o número de
linhas e colunas, além dos dados da matriz em si. Para facilitar a
visualização, fiz uma função printMatrix que imprime os elementos de uma
matriz formatados com duas casas decimais. 📊✨

Uma das funcionalidades mais legais é a criação de matrizes. A função
createMatrix pede ao usuário para digitar os elementos da matriz, e, em
seguida, armazena tudo. Quando eu precisava adicionar ou subtrair duas
matrizes, usei as funções addMatrices e subtractMatrices. Se as matrizes
não tivessem o mesmo tamanho, o programa avisa que ocorreu um erro. ⚠️

Na multiplicação, a função multiplyMatrices verifica se as dimensões são
compatíveis e realiza a multiplicação, enquanto multiplyByScalar permite
multiplicar uma matriz por um número escalar, o que é muito útil. 🧮🔢

Para quem gosta de matemática, a função traceMatrix calcula o traço da
matriz, que é a soma dos elementos da diagonal principal, mas só
funciona com matrizes quadradas. E, claro, não poderia faltar a função
que transpoe uma matriz, transposeMatrix, trocando suas linhas e
colunas. 🔄

Uma das partes mais desafiadoras foi implementar a inversa da matriz
usando o método de Gauss-Jordan na função inverseMatrixN. Isso exige um
pouco de manipulação, mas é muito interessante! 💡🤓

Finalmente, criei um menu interativo onde o usuário pode escolher qual
operação deseja realizar, tornando tudo mais amigável. A interface
permite que o usuário armazene várias matrizes e escolha qual usar em
cada operação. É como ter uma calculadora de matrizes na palma da mão!
🙌📐
