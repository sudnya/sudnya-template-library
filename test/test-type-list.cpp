
#include <iostream>

class NullType;

template<typename Payload, typename Next>
class TypeList {
public:
    typedef Payload payload_type;
    typedef Next    next_type;

};

// TODO : append_type
template<typename List, typename Value>
class append_type {
    // value not nullType static_assert();
public:
    typedef TypeList<typename List::payload_type, typename append_type<typename List::next_type, Value>::type> type;
};

template<typename Value>
class append_type<TypeList<NullType, NullType>, Value> {
public:
    typedef TypeList<Value, NullType> type;
};

template<typename Payload, typename Value>
class append_type<TypeList<Payload, NullType>, Value> {
public:
    typedef TypeList<Payload, TypeList<Value, NullType>> type;
};

// TODO: new_type_list
class new_type_list {
public:
    typedef TypeList<NullType, NullType> type;
};

template<typename T>
class get_first_type {
public:
    typedef typename T::payload_type type;
};

template<typename T>
class get_second_type {
public:
    typedef typename T::next_type type;
};

template<typename T>
class print_types {
public:
    void operator()() const {
        typedef typename get_first_type<T>::type first;
        typedef typename get_second_type<T>::type second;
        
        print_types<first>()();
        print_types<second>()();
    }
};

template<>
class print_types<int> {
    public:
        void operator()() const {
            std::cout << "int ";
        }
};

template<>
class print_types<float> {
    public:
        void operator()() const {
            std::cout << "float ";
        }
};

template<>
class print_types<char> {
    public:
        void operator()() const {
            std::cout << "char\n";
        }
};

template<>
class print_types<NullType> {
public:
    void operator()() const {
        //intentionally blank
    }

};

int main(int argc, char** argv) {

    typedef typename new_type_list::type empty_list;

    typedef typename append_type<empty_list, int>::type temp1;
    typedef typename append_type<temp1, float>::type temp2;
    typedef typename append_type<temp2, float>::type temp3;
    typedef typename append_type<temp3, float>::type temp4;
    typedef typename append_type<temp4, char>::type complete_list;
    
    print_types<complete_list>()();

    return 0;
}





