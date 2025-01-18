#include "MyList.h"

template <typename T>
MyList<T>::~MyList() {
    while (!empty()) {
        pop_back();
    }
}

template <typename T>
void MyList<T>::push_back(T val) {
    Node<T>* newNode = new Node<T>(val);
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    list_size++;
}

template <typename T>
void MyList<T>::push_front(T val) {
    Node<T>* newNode = new Node<T>(val);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    list_size++;
}

template <typename T>
void MyList<T>::pop_back() {
    if (empty()) return;
    Node<T>* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    list_size--;
}

template <typename T>
void MyList<T>::pop_front() {
    if (empty()) return;
    Node<T>* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    list_size--;
}

template <typename T>
void MyList<T>::print() const {
    Node<T>* current = head;
    while (current) {
        std::cout << current->data;
        if (current->next) std::cout << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void MyList<T>::reverse() {
    if (empty()) return;
    Node<T>* current = head;
    Node<T>* temp = nullptr;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp) head = temp->prev;
}

template <typename T>
void MyList<T>::merge(MyList<T>& other) {
    if (empty()) {
        head = other.head;
        tail = other.tail;
    } else if (!other.empty()) {
        tail->next = other.head;
        other.head->prev = tail;
        tail = other.tail;
    }
    list_size += other.size();
}

template <typename T>
void MyList<T>::remove_duplicates() {
    if (empty()) return;
    Node<T>* current = head;
    while (current) {
        Node<T>* nextDistinct = current->next;
        while (nextDistinct && nextDistinct->data == current->data) {
            Node<T>* temp = nextDistinct;
            nextDistinct = nextDistinct->next;
            delete temp;
            list_size--;
        }
        current->next = nextDistinct;
        if (nextDistinct) nextDistinct->prev = current;
        current = nextDistinct;
    }
    tail = current ? current->prev : nullptr;
}

template <typename T>
T MyList<T>::sum() const {
    T sum = 0;
    Node<T>* current = head;
    while (current) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

template <typename T>
void MyList<T>::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    Node<T>* current = head;
    while (current) {
        file << current->data << " ";
        current = current->next;
    }
}

template <typename T>
void MyList<T>::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    T value;
    while (file >> value) {
        push_back(value);
    }
}

template <typename T>
void MyList<T>::print(const std::string& format) const {
    Node<T>* current = head;
    if (format == "JSON") {
        std::cout << "[";
        while (current) {
            std::cout << "\"" << current->data << "\"";
            if (current->next) std::cout << ", ";
            current = current->next;
        }
        std::cout << "]" << std::endl;
    } else if (format == "XML") {
        std::cout << "<list>";
        while (current) {
            std::cout << "<item>" << current->data << "</item>";
            current = current->next;
        }
        std::cout << "</list>" << std::endl;
    } else {
        print();  // Default printing in space-separated format
    }
}
