//
// Created by fokus on 18.04.2021.
//
#include "Matrix.h"
#ifndef MAT_MENU_H
#define MAT_MENU_H
#endif //MAT_MENU_H
#include <cstdlib>
#include "random"

int choice(){
    int ch;
    cin >> ch;
    return ch;
}
//Settings for genarating random numbers
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dist(-10.0, 10.0);

//Set or generate matrix with real numbers
template <typename T> TriangleMatrix<T> SetRealMatrix(int size, string str) {
    int count = size*(size+1)/2;
    cout<<"Automatic input or manual?"<<endl;
    cout<<"1 - Auto input(numbers from -10 to 10)"<<endl;
    cout<<"0 - Manual (input whatever you want)"<<endl;
    ArraySequence<T> seq = ArraySequence<T>(0);
    int ch = choice();
    if (ch == 0) {
        cout<<"Set "<<count<<" elements of matrix, (print every element in different row)"<<endl;
        cout<<"NOTICE! Firstly set elements of 1st row, then 2nd and etc"<<endl;
        for (int i = 0; i<count; i++) {
            T item;
            cout<<"element "<<i+1<<":";
            cin>>item;
            seq.Append(item);
        }
    }
    else if (ch == 1) {
        cout<<"Filling the matrix..."<<endl;
        for (int i = 0; i<count; i++) {
            T item = dist(mt);
            seq.Append(item);
        }
    }
    TriangleMatrix<T> matrix = TriangleMatrix<T>(seq, size, str);
    return matrix;
}
//Set or generate matrix with complex numbers
TriangleMatrix<complex> SetComplexMatrix(int size, string str) {
    int count = size*(size+1)/2;
    cout<<"Automatic input or manual?"<<endl;
    cout<<"1 - Auto input(numbers from -10 to 10)"<<endl;
    cout<<"0 - Manual (input whatever you want)"<<endl;
    ArraySequence<complex> seq = ArraySequence<complex>(0);
    int ch = choice();
    if (ch == 0) {
        cout<<"Set "<<count<<" elements of matrix"<<endl;
        cout<<"real part-imag part"<<endl;
        for (int i = 0; i<count; i++) {
            cout<<"element "<<i+1<<":";
            float re,im;
            cin>>re>>im;
            complex item = complex(re,im);
            seq.Append(item);
        }
    }
    else if (ch == 1) {
        cout<<"Filling the matrix..."<<endl;
        for (int i = 0; i<count; i++) {
            int re = dist(mt);
            int im = dist(mt);
            complex item = complex(re,im);
            seq.Append(item);
        }
    }
    TriangleMatrix<complex> matrix = TriangleMatrix<complex>(seq, size, str);
    return matrix;
}

//Print matrix or real numbers
template <typename T> void PrintRealMatrix(TriangleMatrix<T>& matrix) {
    cout<<"YOUR MATRIX IS:"<<endl;
    for (int i = 0; i<matrix.GetDim(); i++ ) {
        cout<<"---------";
    }
    cout<<endl;
    for (int i = 0; i < matrix.GetDim(); i++) {
        for (int j = 0; j < matrix.GetDim(); j++) {
            cout <<setw(9)<<left<< matrix[i][j] << " ";
        }
        cout<<endl;
    }
    for (int i = 0; i<matrix.GetDim(); i++ ) {
        cout<<"---------";
    }
    cout<<endl;
}
//Print matrix of complex numbers
void PrintComplexMatrix(TriangleMatrix<complex>& matrix) {
    cout<<"YOUR MATRIX IS:"<<endl;
    for (int i = 0; i<matrix.GetDim(); i++ ) {
        cout<<"---------";
    }
    cout<<endl;
    for (int i=0; i<matrix.GetDim(); i++) {
        for (int j=0; j<matrix.GetDim(); j++) {
            matrix[i][j].print();
            cout<<" ";
        }
        cout<<endl;
    }
    for (int i = 0; i<matrix.GetDim(); i++ ) {
        cout<<"---------";
    }
    cout<<endl;
}

template <typename T>
void RealMatrixOperations(int size, string str){
    TriangleMatrix<T> matrix= SetRealMatrix<T>(size,str);
    cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
    int ch = choice();
    if (ch==1) {
        PrintRealMatrix(matrix);
    }
    cout<<"Press any key to continue..."<<endl;
    getchar();
    getchar();
    cout<<"Choose operation:"<<endl;
    cout<<"1 - summ of 2 matrix"<<endl;
    cout<<"2 - multiply"<<endl;
    cout<<"3 - get norm"<<endl;
    cout<<"Your choice:";
    ch = choice();
    cout<<endl;
   if (ch == 1) {
       cout<<"'upper - 1' or 'lower- 0?':";
       int str_ch;
       cin >> str_ch;
       string str1;
       if (str_ch == 1) {
           str1 = "upper";
       }
       else if (str_ch == 0) {
           str1 = "lower";
       }
       else {
           throw invalid_argument(INVALID_ARGUMENT);
       }
       TriangleMatrix<T> matrix2 = SetRealMatrix<T>(size, str1);
       cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
       int ch2 = choice();
       if (ch2==1) {
           PrintRealMatrix(matrix2);
       }
       cout<<"Summimg... Please Wait"<<endl;
       TriangleMatrix<T> matrixR = matrix+matrix2;
       cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
       int ch3 = choice();
       if (ch3==1) {
           PrintRealMatrix(matrixR);
       }
       cout<<"Ended!"<<endl;
   }
   else if (ch ==2) {
       cout<<"What is the factor of multiplication?"<<endl;
       float factor;
       cin>>factor;
       TriangleMatrix<T> matrixR = matrix*factor;
       cout<<"Multiplicating... Please Wait"<<endl;
       cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
       int ch3 = choice();
       if (ch3==1) {
           PrintRealMatrix(matrixR);
       }
   }
   else if (ch == 3) {
       cout<<"Getting a norm, result will be float"<<endl;
       cout<<"Press any key to continue..."<<endl;
       getchar();
       getchar();
       cout<<"Matrix K-norm is "<<matrix.template MatrixNorm<float>();
   }
   else {
       cout<<"Ooops, wrong number"<<endl;
       throw invalid_argument(INVALID_ARGUMENT);
   }
}

void ComplexMatrixOperations(int size, string str){
    TriangleMatrix<complex> matrix= SetComplexMatrix(size,str);
    cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
    int ch = choice();
    if (ch==1) {
        PrintComplexMatrix(matrix);
    }
    cout<<"Press any key to continue..."<<endl;
    getchar();
    getchar();
    cout<<"Choose operation:"<<endl;
    cout<<"1 - summ of 2 matrix"<<endl;
    cout<<"2 - multiply"<<endl;
    cout<<"3 - get norm"<<endl;
    cout<<"Your choice:";
    ch = choice();
    cout<<endl;
    if (ch == 1) {
        cout<<"Setting another matrix:"<<endl;
        cout<<"'upper - 1' or 'lower- 0?':";
        int str_ch;
        cin >> str_ch;
        string str;
        if (str_ch == 1) {
            str = "upper";
        }
        else if (str_ch == 0) {
            str = "lower";
        }
        else {
            throw invalid_argument(INVALID_ARGUMENT);
        }
        TriangleMatrix<complex> matrix2 = SetComplexMatrix(size, str);
        cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
        int ch2 = choice();
        if (ch2==1) {
            PrintComplexMatrix(matrix2);
        }
        cout<<"Summimg... Please Wait"<<endl;
        TriangleMatrix<complex> matrixR = matrix+matrix2;
        cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
        int ch3 = choice();
        if (ch3==1) {
            PrintComplexMatrix(matrixR);
        }
        cout<<"Ended!"<<endl;
    }
    else if (ch ==2) {

        cout<<"Do you want to multiply on real or complex number?"<<endl;
        cout<<"1 - complex"<<endl;
        cout<<"0- real" << endl;
        cout<<"Your choice:";
        int ch2;
        cin>>ch2;
        if (ch2 == 1) {
            complex factor;
            float re,im;
            cout<<"real and imag part of factor"<<endl;
            cin>>re>>im;
            factor = complex(re,im);
            TriangleMatrix<complex> matrixR = matrix*factor;
            cout<<"Multiplicating... Please Wait"<<endl;
            cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
            int ch3 = choice();
            if (ch3==1) {
                PrintComplexMatrix(matrixR);
            }
        }
        if (ch2 == 0) {
            float factor;
            cout<<"Set your factor";
            cin>>factor;
            TriangleMatrix<complex> matrixR = matrix*factor;
            cout<<"Multiplicating... Please Wait"<<endl;
            cout<<"Print matrix? 1 - yes, 0 - no"<<endl;
            int ch3 = choice();
            if (ch3==1) {
                PrintComplexMatrix(matrixR);
            }
        }

    }
    else if (ch == 3) {
        cout<<"Getting a norm, result will be complex"<<endl;
        cout<<"Press any key to continue..."<<endl;
        getchar();
        getchar();
        cout<<"Matrix K-norm is ";
        matrix.MatrixNorm<complex>().print();
    }
    else {
        cout<<"Ooops, wrong number"<<endl;
        throw invalid_argument(INVALID_ARGUMENT);
    }
}


void menu() {
    cout<<"Choose type:"<<endl;
    cout<<"1 - int"<<endl;
    cout<<"2 - float"<<endl;
    cout<<"3 - complex"<<endl;
    cout<<"Set your choice:";
    int choice;
    cin >> choice;
    cout<<endl;
    if (choice!=1 & choice!=2 & choice !=3) {
        cout<<"Ooops, wrong number"<<endl;
        throw invalid_argument(INVALID_ARGUMENT);
    }
    cout<<"Set matrix size:";
    int size;
    cin>>size;
    cout<<endl;
    cout<<"'upper - 1' or 'lower- 0?':";
    int str_ch;
    cin >> str_ch;
    string str;
    if (str_ch == 1) {
        str = "upper";
    }
    else if (str_ch == 0) {
        str = "lower";
    }
    else {
        throw invalid_argument(INVALID_ARGUMENT);
    }
    cout<<endl;
    if (choice ==1) {
       RealMatrixOperations<int>(size, str);
    }
    else if (choice ==2) {
        RealMatrixOperations<float>(size, str);
    }
    else if (choice==3) {
        ComplexMatrixOperations(size, str);
    }

}