#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10

typedef struct {
    int rows;
    int cols;
    float data[MAX][MAX];
} Matrix;

// Função para imprimir uma matriz
void printMatrix(Matrix m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            printf("%.2f\t", m.data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para criar uma nova matriz
Matrix createMatrix(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    printf("Digite os elementos da matriz %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &m.data[i][j]);
        }
    }
    return m;
}

// Função para adicionar duas matrizes
Matrix addMatrices(Matrix a, Matrix b) {
    Matrix result;
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Erro: Matrizes de tamanhos diferentes.\n");
        result.rows = result.cols = 0;
        return result;
    }
    result.rows = a.rows;
    result.cols = a.cols;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

// Função para subtrair duas matrizes
Matrix subtractMatrices(Matrix a, Matrix b) {
    Matrix result;
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Erro: Matrizes de tamanhos diferentes.\n");
        result.rows = result.cols = 0;
        return result;
    }
    result.rows = a.rows;
    result.cols = a.cols;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

// Função para multiplicar duas matrizes
Matrix multiplyMatrices(Matrix a, Matrix b) {
    Matrix result;
    if (a.cols != b.rows) {
        printf("Erro: Número de colunas da primeira matriz deve ser igual ao número de linhas da segunda.\n");
        result.rows = result.cols = 0;
        return result;
    }
    result.rows = a.rows;
    result.cols = b.cols;
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

// Função para multiplicar uma matriz por um escalar
Matrix multiplyByScalar(Matrix m, float scalar) {
    Matrix result = m;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[i][j] *= scalar;
        }
    }
    return result;
}

// Função para transpor uma matriz
Matrix transposeMatrix(Matrix m) {
    Matrix result;
    result.rows = m.cols;
    result.cols = m.rows;
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];
        }
    }
    return result;
}

// Função para calcular o traço de uma matriz (somente para matrizes quadradas)
float traceMatrix(Matrix m) {
    float trace = 0;
    if (m.rows != m.cols) {
        printf("Erro: O traço só pode ser calculado para matrizes quadradas.\n");
        return 0;
    }
    for (int i = 0; i < m.rows; i++) {
        trace += m.data[i][i];
    }
    return trace;
}

// Função auxiliar para trocar linhas
void swapRows(float a[MAX][MAX], int row1, int row2, int n) {
    for (int i = 0; i < n; i++) {
        float temp = a[row1][i];
        a[row1][i] = a[row2][i];
        a[row2][i] = temp;
    }
}

// Função para calcular a inversa de uma matriz n x n usando o método de Gauss-Jordan
Matrix inverseMatrixN(Matrix m) {
    Matrix result;
    if (m.rows != m.cols) {
        printf("Erro: A inversa só pode ser calculada para matrizes quadradas.\n");
        result.rows = result.cols = 0;
        return result;
    }

    int n = m.rows;
    result.rows = n;
    result.cols = n;

    // Criando uma matriz aumentada [A | I]
    float augmented[MAX][MAX * 2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = m.data[i][j]; // Parte da matriz original
        }
        for (int j = n; j < 2 * n; j++) {
            augmented[i][j] = (i == j - n) ? 1.0 : 0.0; // Parte da matriz identidade
        }
    }

    // Método de Gauss-Jordan para obter a inversa
    for (int i = 0; i < n; i++) {
        // Tornando o pivô 1
        if (augmented[i][i] == 0) {
            int swapRow = i + 1;
            while (swapRow < n && augmented[swapRow][i] == 0) swapRow++;
            if (swapRow == n) {
                printf("Erro: Matriz não inversível.\n");
                result.rows = result.cols = 0;
                return result;
            }
            swapRows(augmented, i, swapRow, 2 * n);
        }

        float pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= pivot;
        }

        // Zerando as outras linhas
        for (int k = 0; k < n; k++) {
            if (k != i) {
                float factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // Extraindo a parte da inversa
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.data[i][j] = augmented[i][j + n];
        }
    }

    return result;
}

// Menu principal
void showMenu() {
    printf("===== Calculadora de Matrizes =====\n");
    printf("1. Criar nova matriz\n");
    printf("2. Adicionar matrizes\n");
    printf("3. Subtrair matrizes\n");
    printf("4. Multiplicar matrizes\n");
    printf("5. Multiplicar matriz por escalar\n");
    printf("6. Transpor matriz\n");
    printf("7. Inverter matriz 2x2\n");
    printf("8. Inverter matriz nxn\n");
    printf("9. Calcular o traço de uma matriz\n");
    printf("10. Exibir matriz armazenada\n");
    printf("11. Sair\n");
    printf("===================================\n");
    printf("Escolha uma opção: ");
}

int main() {
    Matrix matrices[MAX];
    int matrixCount = 0;
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int rows, cols;
                printf("Digite o número de linhas: ");
                scanf("%d", &rows);
                printf("Digite o número de colunas: ");
                scanf("%d", &cols);

                if (rows > MAX || cols > MAX) {
                    printf("Erro: O tamanho máximo é %dx%d.\n", MAX, MAX);
                } else {
                    matrices[matrixCount++] = createMatrix(rows, cols);
                    printf("Matriz armazenada como matriz %d.\n", matrixCount);
                }
                break;
            }

            case 2: {
                int mat1, mat2;
                printf("Escolha a primeira matriz para adicionar (1-%d): ", matrixCount);
                scanf("%d", &mat1);
                printf("Escolha a segunda matriz para adicionar (1-%d): ", matrixCount);
                scanf("%d", &mat2);

                if (mat1 >= 1 && mat1 <= matrixCount && mat2 >= 1 && mat2 <= matrixCount) {
                    Matrix result = addMatrices(matrices[mat1 - 1], matrices[mat2 - 1]);
                    if (result.rows != 0) {
                        printMatrix(result);
                        matrices[matrixCount++] = result;
                        printf("Resultado armazenado como matriz %d.\n", matrixCount);
                    }
                } else {
                    printf("Erro: Matrizes inválidas.\n");
                }
                break;
            }

            case 3: {
                int mat1, mat2;
                printf("Escolha a primeira matriz para subtrair (1-%d): ", matrixCount);
                scanf("%d", &mat1);
                printf("Escolha a segunda matriz para subtrair (1-%d): ", matrixCount);
                scanf("%d", &mat2);

                if (mat1 >= 1 && mat1 <= matrixCount && mat2 >= 1 && mat2 <= matrixCount) {
                    Matrix result = subtractMatrices(matrices[mat1 - 1], matrices[mat2 - 1]);
                    if (result.rows != 0) {
                        printMatrix(result);
                        matrices[matrixCount++] = result;
                        printf("Resultado armazenado como matriz %d.\n", matrixCount);
                    }
                } else {
                    printf("Erro: Matrizes inválidas.\n");
                }
                break;
            }

            case 4: {
                int mat1, mat2;
                printf("Escolha a primeira matriz para multiplicar (1-%d): ", matrixCount);
                scanf("%d", &mat1);
                printf("Escolha a segunda matriz para multiplicar (1-%d): ", matrixCount);
                scanf("%d", &mat2);

                if (mat1 >= 1 && mat1 <= matrixCount && mat2 >= 1 && mat2 <= matrixCount) {
                    Matrix result = multiplyMatrices(matrices[mat1 - 1], matrices[mat2 - 1]);
                    if (result.rows != 0) {
                        printMatrix(result);
                        matrices[matrixCount++] = result;
                        printf("Resultado armazenado como matriz %d.\n", matrixCount);
                    }
                } else {
                    printf("Erro: Matrizes inválidas.\n");
                }
                break;
            }

            case 5: {
                int mat;
                float scalar;
                printf("Escolha uma matriz para multiplicar por um escalar (1-%d): ", matrixCount);
                scanf("%d", &mat);
                printf("Digite o valor do escalar: ");
                scanf("%f", &scalar);

                if (mat >= 1 && mat <= matrixCount) {
                    Matrix result = multiplyByScalar(matrices[mat - 1], scalar);
                    printMatrix(result);
                    matrices[matrixCount++] = result;
                    printf("Resultado armazenado como matriz %d.\n", matrixCount);
                } else {
                    printf("Erro: Matriz inválida.\n");
                }
                break;
            }

            case 6: {
                int mat;
                printf("Escolha uma matriz para transpor (1-%d):\n", matrixCount);
                scanf("%d", &mat);

                if (mat >= 1 && mat <= matrixCount) {
                    Matrix result = transposeMatrix(matrices[mat - 1]);
                    printMatrix(result);
                    matrices[matrixCount++] = result;
                    printf("Resultado armazenado como matriz %d.\n", matrixCount);
                } else {
                    printf("Erro: Matriz inválida.\n");
                }
                break;
            }

            case 7: {
                int mat;
                printf("Escolha uma matriz 2x2 para inverter (1-%d):\n", matrixCount);
                scanf("%d", &mat);

                if (mat >= 1 && mat <= matrixCount) {
                    Matrix result = inverseMatrixN(matrices[mat - 1]);
                    if (result.rows != 0) {
                        printMatrix(result);
                        matrices[matrixCount++] = result;
                        printf("Resultado armazenado como matriz %d.\n", matrixCount);
                    }
                } else {
                    printf("Erro: Matriz inválida.\n");
                }
                break;
            }

            case 8: {
                int mat;
                printf("Escolha uma matriz para calcular a inversa (1-%d):\n", matrixCount);
                scanf("%d", &mat);

                if (mat >= 1 && mat <= matrixCount) {
                    Matrix result = inverseMatrixN(matrices[mat - 1]);
                    if (result.rows != 0) {
                        printMatrix(result);
                        matrices[matrixCount++] = result;
                        printf("Resultado armazenado como matriz %d.\n", matrixCount);
                    }
                } else {
                    printf("Erro: Matriz inválida.\n");
                }
                break;
            }

            case 9: {
                int mat;
                printf("Escolha uma matriz para calcular o traço (1-%d):\n", matrixCount);
                scanf("%d", &mat);

                if (mat >= 1 && mat <= matrixCount) {
                    float trace = traceMatrix(matrices[mat - 1]);
                    printf("Traço da matriz: %.2f\n", trace);
                } else {
                    printf("Erro: Matriz inválida.\n");
                }
                break;
            }

            case 10: {
                int mat;
                printf("Escolha uma matriz para exibir (1-%d):\n", matrixCount);
                scanf("%d", &mat);

                if (mat >= 1 && mat <= matrixCount) {
                    printMatrix(matrices[mat - 1]);
                } else {
                    printf("Erro: Matriz inválida.\n");
                }
                break;
            }

            case 11:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 11);
}
