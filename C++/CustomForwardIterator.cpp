#include <iostream>

using namespace std;

struct Iterator
{ 
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = int;
    using pointer           = int*;  // or also value_type*
    using reference         = int&;  // or also value_type&
    
    Iterator(pointer ptr) : m_ptr(ptr) {}
    
    reference operator*() const { 
        cout << "Operator *" << endl;
        return *m_ptr; 
    }
    pointer operator->() {
        cout << "Operator ()" << endl;
        return m_ptr; 
    }

    // Prefix increment
    Iterator& operator++() 
    { 
        cout << "Operator Prefix++" << endl;
        m_ptr++; 
        return *this; 
    }  

    // Postfix increment
    Iterator operator++(int) 
    { 
        cout << "Operator Postfix++" << endl;
        Iterator tmp = *this; 
        ++(*this); 
        return tmp; 
    }

    friend bool operator== (const Iterator& a, const Iterator& b) 
    { 
        cout << "Operator ==" << endl;
        return a.m_ptr == b.m_ptr; 
    };
    friend bool operator!= (const Iterator& a, const Iterator& b) 
    { 
        cout << "Operator !=" << endl;
        return a.m_ptr != b.m_ptr; 
    };     

    private:
        pointer m_ptr;
};

class Integers
{
private:
    int m_data[5];
public:
    Integers()
    {
        for (int i = 0; i < 5; i++)
            m_data[i] = i;
    }
    Iterator begin() 
    {
        cout << "Begin()" << endl;
        return Iterator(&m_data[0]); 
    }
    Iterator end()   
    { 
        cout << "End()" << endl;
        return Iterator(&m_data[5]); 
    } // 10 is out of bounds
    
};

int main()
{
    cout<<"Hello World" << "\n";
    Integers integers;
    for (auto i : integers)
        std::cout << i << "\n";
#if 0
    for (auto it = integers.begin(), end = integers.end(); it != end; ++it) 
    { 
        const auto i = *it; 
        std::cout << i << "\n";
    }
#endif
    std::fill(integers.begin(), integers.end(), 3);
    for (auto i : integers)
        std::cout << i << "\n";
    return 0;
}
