//
// Created by fokus on 18.04.2021.
//

#ifndef MAT_MATRIX_H
#define MAT_MATRIX_H

#endif //MAT_MATRIX_H

#include <strings.h>
using namespace std;
#include <stdexcept>
const string INVALID_ARGUMENT = "Invalid argument";
const string DIFFERENT_DIMS = "Impossible to make this operation: Matrices have different dimensions";
#include <cmath>
#include "Complex.h"
#include "ArraySequence.h"
#include "DynamicArray.h"
template <typename T>
class TriangleMatrix {
private:
    Sequence<T>** rows; //Every row is an array sequence
    int dimension; // size of matrix
public:

    TriangleMatrix() :dimension(0) {
        rows=0;
    }
    //Creation of matrix with size n filled with zeros
    TriangleMatrix(int size) :dimension(size) {
        rows =(Sequence<T>**) new ArraySequence<T>*[size];
        for (int i =0; i<size; i++) {
            rows[i] = new ArraySequence<T>(size);
        }
        for (int i = 0; i<size; i++) {
            for (int j=0; j<size; j++) {
                this->SetElement(i,j,0);
            }
        }
    }

    TriangleMatrix(const TriangleMatrix<T>& matrix) {
        this->dimension=matrix.dimension;
        this->rows=matrix.rows;
    }
//Creating from sequence of elements, if matrix is upper triangle , first n elements for 1st row, next n-1 for 2nd row and etc...
    TriangleMatrix(ArraySequence<T> sequence, int size, string str) : TriangleMatrix(size)  {
        if (str == "upper") {
            int count = 0;
            for (int i = 0; i<size; i++) {
                for (int j=i; j<size; j++) {
                    this->SetElement(i,j, sequence[count]);
                    count++;
                }
            }
        }
        else if (str == "lower") {
            int count = 0;
            for (int i =0; i<size; i++) {
                for (int j =0; j<i+1;j++) {
                    this->SetElement(i,j, sequence[count]);
                    count++;
                }
            }
        }
        else {
            throw invalid_argument(INVALID_ARGUMENT);
        }
        this->dimension=size;
    }
    //Get dimension
    int GetDim() {
        return this->dimension;
    }
    //Get row
    Sequence<T>* GetRow(int index) {
        if (index<0 || index>=this->dimension) {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return rows[index];
    }

    //Get element of matrix if we now it's coordinates. NOTICE! Rows and cols start with 0 index!!!!

    T GetElement(int row, int col) {
        if (row<0 || col<0 || col>=dimension || row>=dimension) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        //  ArraySequence<T> temp = this->GetRow(row);
        return this->GetRow(row)->Get(col);
    }

    //Set element to matrix if we now it's coordinates and value. NOTICE! Rows and cols start with 0 index!!!!

    void SetElement(int row, int col, T item) {
        if (row<0 || col<0 || col>=dimension || row>=dimension) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        Sequence<T>* temp = this->GetRow(row);
        temp->Set(col, item);
        rows[row] = temp;

    }

    //matrixC = matrixA + matrixB
    TriangleMatrix<T> operator+(TriangleMatrix<T>& matrix) {
        if (this->dimension != matrix.dimension)  {
            throw logic_error(DIFFERENT_DIMS);
        }
        TriangleMatrix<T> matrixR = TriangleMatrix<T>(matrix.dimension);

        for(int i = 0; i<matrix.dimension; i++) {
            for(int j = 0; j<matrix.dimension; j++){
                T item = this->GetElement(i, j)+matrix.GetElement(i, j);
                matrixR.SetElement(i, j, item);
            }
        }
        return matrixR;
    }

    //matrixC = matrixA - matrixB
    TriangleMatrix<T> operator-(TriangleMatrix<T>& matrix) {
        if (this->dimension != matrix.dimension)  {
            throw logic_error(DIFFERENT_DIMS);
        }
        TriangleMatrix<T> matrixR = TriangleMatrix<T>(matrix.dimension);

        for(int i = 0; i<matrix.dimension; i++) {
            for(int j = 0; j<matrix.dimension; j++){
                T item = this->GetElement(i, j) - matrix.GetElement(i, j);
                matrixR.SetElement(i, j, item);
            }
        }
        return matrixR;
    }

    // matrixC = maatrixA * factor
    template<typename U>
    TriangleMatrix<T> operator*(U factor) {
        TriangleMatrix<T> matrixR = TriangleMatrix<T>(this->dimension);
        for(int i = 0; i<this->dimension; i++) {
            for(int j = 0; j<this->dimension; j++){
                T item =((this->GetElement(i, j))*factor);
                matrixR.SetElement(i, j, item);
            }
        }
        return (matrixR);
    }

    //Matrix norm - Square root of element square summ.

    template<typename U>
    U MatrixNorm(){
        U Summ =U();
        for(int i = 0; i<this->dimension; i++) {
            for(int j = 0; j<this->dimension; j++){
                Summ = Summ + ((this->GetElement(i, j)) * (this->GetElement(i, j)));
            }
        }
        return (U)(sqrt(Summ));
    }

//Operator to get row.
    Sequence<T>* operator[](const int index) {
       return this->GetRow(index);
    }

    ~TriangleMatrix(){};


};

//Special template to get norm as a complex number
//Square root of complex number
// if the number looks like a+i(b)
//root will look like c+i(d) where
//             ________________                _______________
//           /   _______                     /   ________
// с = -   /  -/ a^2+b^2 +a    d= sgn(b)   /  -/ a^2+b^2  -a
//      \/        2                     \/          2
//
template<>
template<> inline
complex TriangleMatrix<complex>::MatrixNorm<complex>() {
    complex summ = complex(0,0);
    for (int i = 0; i<this->dimension; i++) {
        for (int j=0; j<this->dimension; j++) {
            summ = summ + ((this->GetElement(i,j))*(this->GetElement(i,j)));
        }
    }
    return summ.sqrt_complex();
}