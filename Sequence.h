//
// Created by fokus on 18.04.2021.
//

#ifndef MAT_SEQUENCE_H
#define MAT_SEQUENCE_H

#endif //MAT_SEQUENCE_H

#ifndef UNTITLED_SEQUENCE_H
#define UNTITLED_SEQUENCE_H

#endif //UNTITLED_SEQUENCE_H
template <typename T> class Sequence {
public:
    //decompose
    virtual int GetSize() const = 0;
    virtual T Get(int index) const = 0;
    virtual T GetLast() const = 0;
    virtual T GetFirst() const = 0;
    virtual Sequence<T>* GetSubSequence(int start, int end) = 0;

    //operations
    virtual void Set(int index, T item) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
// operators
    virtual T operator[](const int index) = 0;

};