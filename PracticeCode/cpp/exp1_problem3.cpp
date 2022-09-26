#include <iostream>
#include <algorithm>
using namespace std;

class SparseMatrix;

class MatrixTerm {
    friend class SparseMatrix;
    int row, col, value;
public:
    MatrixTerm() {row = 0;col = 0;value = 0;}
    MatrixTerm(int r, int c, int v)
    {
        row = r;
        col = c;
        value = v;
    }
    void print()
    {
        cout << row << '\t' << col << '\t' << value;
    }
};

class SparseMatrix
{
public:
    int rows, cols, terms;
    MatrixTerm* smArray;

    SparseMatrix(int r, int c, int t)
    {
        rows = r;
        cols = c;
        terms = t;
        smArray = new MatrixTerm[terms];
    }
    void print()
    {
        for (int i = 0; i < terms; ++i)
        {
            smArray[i].print();
            cout << endl;
        }
    }
    SparseMatrix FastTranspose();
};

SparseMatrix SparseMatrix::FastTranspose()
{
    SparseMatrix b(rows,cols,terms);
    if (terms > 0)
    {
        int* rowInfo = new int[2 * cols+1];       
        fill(rowInfo,rowInfo+2*cols,0);
        for (int i = 0; i < terms; i++) rowInfo[smArray[i].col + cols]++;
        rowInfo[0] = 0;
        for (int i = 1; i < cols; i++) {rowInfo[i] = rowInfo[i - 1] + rowInfo[i - 1 + cols];}
        for (int i = 0; i < terms; i++)
        {
            int j = rowInfo[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowInfo[smArray[i].col]++;
        }
        delete[]rowInfo;
    }
    return b;
}

int main()
{
    SparseMatrix test(4, 5, 5);
    test.smArray[0] = MatrixTerm(1, 2, 100);
    test.smArray[1] = MatrixTerm(2, 3, 101);
    test.smArray[2] = MatrixTerm(3, 1, 102);
    test.smArray[3] = MatrixTerm(3, 4, 103);
    test.smArray[4] = MatrixTerm(4, 2, 104);
    cout << "转置前：" << endl;
    test.print();
    cout << "转置后：" << endl;

    test.FastTranspose().print();
    system("pause");
    return 0;
}