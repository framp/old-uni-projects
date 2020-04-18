#ifndef CISPOINTER_H
#define CISPOINTER_H

template <class T>
class CISpointer
{
public:
    T* pointer;
    CISpointer (T* = 0);
    CISpointer (const CISpointer<T>&);
    CISpointer& operator=(const CISpointer<T>&);
    T& operator*() const;
    T* operator->() const;
    bool operator==(const CISpointer<T>&) const;
    bool operator!=(const CISpointer<T>&) const;
    ~CISpointer();
};

template <class T>
CISpointer<T>::CISpointer (T* p):
    pointer(p)
{
    if (pointer)
        pointer->references++;
}

template <class T>
CISpointer<T>::CISpointer (const CISpointer<T>& p):
    pointer(p.pointer)
{
    if (pointer)
        pointer->references++;
}

template <class T>
CISpointer<T>& CISpointer<T>::operator=(const CISpointer<T>& p)
{
    if (this != &p) {
        T* t = pointer;
        pointer = p.pointer;
        if (pointer)
            pointer->references++;
        if (t) {
            t->references--;
            if (t->references == 0 )
                delete t;
        }
    }
    return *this;
}

template <class T>
T& CISpointer<T>::operator*() const
{
    return const_cast<T&>(*pointer);
}

template <class T>
T* CISpointer<T>::operator->() const
{
    return const_cast<T*>(pointer);
}

template <class T>
bool CISpointer<T>::operator==(const CISpointer<T>& p) const
{
    return pointer == p.pointer;
}

template <class T>
bool CISpointer<T>::operator!=(const CISpointer<T>& p) const
{
    return pointer != p.pointer;
}

template <class T>
CISpointer<T>::~CISpointer()
{
    if (pointer) {
        pointer->references--;
        if (pointer->references==0)
            delete pointer;
    }
}


#endif // CISPOINTER_H
