// Implement a class "my_shared_ptr" that will have equivalent semantics to
// "std::shared_ptr" for the code given below.
// Do not modify anything below this line


struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // Note: virtual destructor is OK here
    virtual ~Base() { std::cout << "  Base::~Base()\n"; }
};


struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};


void thr(my_shared_ptr<Base> pt)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // ***** 3 *****
    my_shared_ptr<Base> lp = pt; // thread-safe, even though the
                                  // shared use_count is incremented

    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        // ***** 4 & 5 *****
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
    //destructor
}

template <typename T>
class my_shared_ptr
{
    private:
        int* refCount;
        T* barePtr;
        static std::mutex io_mutex;
    public:
        //constructor
        my_shared_ptr(T* baseClass) 
        {
            this->barePtr = baseClass;
            this->refCount = new (int);
            *this->refCount = 1;

        }

        //cp constructor
        my_shared_ptr(const my_shared_ptr<T>& that) 
        {
            this->refCount = that.refCount;
            this->barePtr = that.barePtr;
            std::lock_guard<std::mutex> lk(io_mutex);
            *(this->refCount)++;
        }

        //destructor
        ~my_shared_ptr()
        { 
            reset();
        }

        //get active ref count
        int use_count()
        {
            if (this->refCount != nullptr)
                return *(this->refCount);
            return 0;
        }

        //get bareptr
        T* get()
        {
            return (this->barePtr);
        }

        //decrement refCount
        void reset()
        {
            if (this->refCount != nullptr)
            {
                std::lock_guard<std::mutex> lk(io_mutex);
                *(this->refCount)--;
                if (*(this->refCount) <= 0) {
                    delete this->refCount;
                    delete this->barePtr;
                }
            }
            if (this->barePtr != nullptr) {
                this->barePtr = nullptr;
                this->refCount = nullptr;
            }
        }
}

int main()
{
    my_shared_ptr<Base> p1(new Derived);
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p1.get()
              << ", p.use_count() = " << p1.use_count() << '\n';

    // ***** 1 *****
    std::thread t1(thr, p1), t2(thr, p1), t3(thr, p1);
    // ***** 2 *****
    p1.reset(); // release ownership from main

    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p1.get()
              << ", p.use_count() = " << p1.use_count() << '\n';

    t1.join(); 
    t2.join(); 
    t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";

}
