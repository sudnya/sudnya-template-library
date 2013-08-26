
#include <vector>

namespace sudnya
{

template<typename T>
class vector
{
    public:
        typedef size_t size_type;


    public:
        explicit vector()
        {
            const size_type initSize = 2;
            _elements = new T[initSize];
            _capacity = initSize;
            _size     = 0;
        }

        ~vector()
        {
            delete [] _elements;
        }

        T& operator[](size_type index)
        {
            return _elements[index];
        }

        size_type capacity() const
        {
            return _capacity;
        }

        size_type size() const
        {
            return _size;
        }

        void push_back (const T& val)
        {
            // if current vector is as big as capacity allocated, we need more storage
            if (_capacity == size())
            {
                T* newElem = new T[_capacity*2];
                for (unsigned i = 0; i < _capacity; ++i)
                {
                    newElem[i] = _elements[i];
                }
                newElem[_capacity] = val;
                _size += 1;
                _capacity *= 2;
                delete [] _elements;
                _elements = newElem;
            } else {
                _elements[size()] = val;
                _size += 1;
            }
        }
    
    
    private:
        T* _elements;
        size_type _capacity;
        size_type _size;
         
};

}

