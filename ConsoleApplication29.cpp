#include <iostream>
#include <string>

template <class T>
class Queue
{
    struct Node {
        T value;
        int prior;

        Node() : value{ 0 }, prior{ 0 } {}
        Node(const T& value, int prior) : value(value), prior(prior) {}
    };

    Node* data;
    int length;
public:
    Queue();
    explicit Queue(int size);
    Queue(const Queue<T>& queue);
    ~Queue();

    bool push_back(const T& value, int prior);
    bool pop();
    int size() const;
    bool empty() const;
    int front();
    int back();

    friend std::ostream& operator << (std::ostream& out, const Queue<T>& queue)
    {
        for (int i = 0; i < queue.length; ++i)
        {
            out << "Value: " << queue.data[i].value << ", Priority: " << queue.data[i].prior << "\n";
        }
        return out;
    }

    bool operator>(const Queue<T>& other)
    {
        return data[0].prior > other.data[0].prior;
    }

    bool operator<(const Queue<T>& other)
    {
        return data[0].prior < other.data[0].prior;
    }

};

template<class T>
inline Queue<T>::Queue() : data{ nullptr }, length{ 0 }
{
}

template<class T>
inline Queue<T>::Queue(int size) : length(size), data(new Node[size])
{
}

template<class T>
inline Queue<T>::Queue(const Queue<T>& queue) : length(queue.length), data(new Node[queue.length])
{
    for (int i = 0; i < queue.length; ++i)
    {
        data[i] = queue.data[i];
    }
}

template<class T>
inline Queue<T>::~Queue()
{
    delete[] data;
}

template<class T>
inline bool Queue<T>::push_back(const T& value, int prior)
{
    Node* temp = new Node[length + 1];
    for (size_t i = 0; i < length; i++)
    {
        temp[i] = data[i];
    }
    temp[length] = Node(value, prior);
    length++;
    delete[] data;
    data = temp;
    return true;

}

template<class T>
inline bool Queue<T>::pop()
{
    if (length > 0)
    {
        Node* temp = new Node[length - 1];
        for (int i = 0; i < length - 1; i++)
        {
            temp[i] = data[i + 1];
        }
        delete[] data;
        data = temp;
        length--;
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
inline int Queue<T>::size() const
{
    return length;
}

template<class T>
inline bool Queue<T>::empty() const
{
    return length > 0 ? false : true;
}

template<class T>
inline int Queue<T>::front()
{
    return length > 0 ? data[0].value : false;
}

template<class T>
inline int Queue<T>::back()
{
    return length > 0 ? data[length - 1].value : false;
}

int main() {

    Queue<int> queue1;
    Queue<int> queue2;
    queue1.push_back(5, 1);
    queue1.push_back(7, 2);
    queue1.push_back(1, 3);
    queue2.push_back(9, 1);
    queue2.push_back(30, 2);

    std::cout << "Queue 1: " << queue1.size() << " parametrs" << std::endl;
    std::cout << "Queue 2: " << queue2.size() << " parametrs" << std::endl;
    queue1.pop();
    std::cout << std::endl;
    std::cout << "Queue 1: " << queue1.size() << " parametrs" << std::endl;
    std::cout << "Queue 2: " << queue2.size() << " parametrs" << std::endl;
    std::cout << std::endl;
    std::cout << "Queue 1 info:\n" << queue1 << std::endl;
    std::cout << "Queue 2 info:\n" << queue2 << std::endl;

    std::cout << queue1.back();
    std::cout << std::endl;
    std::cout << queue2.front();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << (queue1 < queue2);

}
