#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>

/*
Задача 1. Нека е даден следният шаблон на структура:
*/
template <class T>
struct Node {
    T data;
    Node<T> *next;

    Node(const T& data, Node<T> *next = nullptr):
        data(data), next(next) {}
};

/*
Да се реализира функция reduce, която приема два параметъра: указател към първия елемент на линеен едносвързан списък L
с възли от тип Node и двуместна функция F от тип (const T&, const T&) → T. Резултатът от изпълнението на reduce да е
стойността при приложението на ляво-асоциативния оператор F последователно над елементите на L, или
 F(...F(F(l1,l2), l3) ...,lk), където l1,...,lk са елементите на списъка L.

При K = 0 да се генерира подходяща грешка (изключение), а при K = 1 стойността на функцията да е l1.

Пример:
Нека имаме списъка L с елементи 1024, 16, 4, 2. Нека d(x,y) = x/y.
Тогава резултатът от reduce (L,d) ще бъде 8, тъй като div(div(div(1024, 16), 4), 2) = 8
*/
template <class T>
T reduce(const Node<T> *head, T(*op)(const T&, const T&)) {
    if(head == nullptr) {
        throw std::domain_error("Empty list!");
    }

    auto res = head->data;
    for(auto node = head->next; node != nullptr; node = node->next) {
        res = op(res, node->data);
    }
    return res;
}

/*
Задача 2. При условията на горната задача, нека е даден списък L с елементи стекове. Възлите на L са от тип
Node<std::stack<T>>> (или друга готова реализация на стек, с която разполагате). Да се дефинира подходящо
параметризирана функция equalize(L), която размества елементите на стековете така, че да няма два стека в L
с разлика в броя на елементите, по-голяма от 1.
*/
// Ще я ползваме и в зад. 3.
template <class T>
size_t length(const Node<T> *head) {
    size_t res = 0;
    for(auto node = head; node != nullptr; node = node->next) {
        res ++;
    }
    return res;
}

template <class T>
void move(std::stack<T> &src, std::stack<T> &dst) {
    assert(!src.empty());
    const auto x = src.top();
    src.pop();
    dst.push(x);
}

template <class T>
void equalize(Node<std::stack<T>> *head) {
    size_t totalNumberOfElements = 0;
    for(auto node = head; node != nullptr; node = node->next) {
        totalNumberOfElements += node->data.size();
    }
    size_t numberOfStacks = length(head);
    size_t averageElementsPerStack = totalNumberOfElements / numberOfStacks;

    std::stack<T> temp;
    // Обхождаме всички и добавяме в temp, ако имаме повече от средния брой
    for(auto node = head; node != nullptr; node = node->next) {
        std::stack<T> &current = node->data;
        while(current.size() > averageElementsPerStack) {
            move(current, temp);
        }
    }

    // Обхождаме всички и добавяме от temp, където има по-малко от необходимото
    for(auto node = head; node != nullptr; node = node->next) {
        std::stack<T> &current = node->data;
        while(current.size() < averageElementsPerStack) {
            move(temp, current);
        }
    }

    // Разпределяме останалите в temp елементи
    assert(temp.size() < numberOfStacks);
    for(auto node = head; node != nullptr && !temp.empty(); node = node->next) {
        move(temp, node->data);
    }
}

/*
Задача 3. Нека е даден списък L с N елемента. Да се дефинира подходящо параметризирана функция shuffle,
която получава адреса на първия елемент на списъка. Функцията да пренарежда възлите на списъка така, че
елементите от втората половина на списъка да се преместят в началото на списъка, но в обратен ред (при
списъци с нечетен брой елементи считаме средния елемент за принадлежащ към първата половина на списъка).

Пример:
L1 → L2 → L3 → L4 → L5  се преобразува до L5 → L4 → L1 → L2 → L3

При решението на задачата да не се изтриват или заделят нови възли, а да се използват съществуващите.
Могат да се използват други изучени структури от данни.
*/
template <class T>
Node<T> *shuffle(Node<T> *head) {
    const auto half = length(head) / 2;

    // Намираме средата
    auto middle = head;
    for(auto i = 0; i < half; i++) {
        middle = middle->next;
    }

    if(middle) {
        // Хубаво място да добави един cout, докато дебъгваме кода.
        // std::cout << "middle=" << middle->data << std::endl;
        // Отделяме втората половина от първата
        auto node = middle->next;
        middle->next = nullptr;

        // Обхождаме втората половина и добавяме елементите
        // в началото на списъка. Това обръща реда им.
        while(node) {
            auto temp = node->next;
            node->next = head;
            head = node;
            node = temp;
        }
    }

    return head;
}


// Тестове:
template <class T>
void print(const Node<T> *head) {
    for(auto n = head; n != nullptr; n = n->next) {
        std::cout << n->data << ' ';
    }
    std::cout << std::endl;
}

int div(const int& a, const int& b) {
    return a / b;
}

int add(const int& a, const int& b) {
    return a + b;
}

void testEx1() {
    Node<int> *l1 = new Node(1024, new Node(16, new Node(4, new Node(2))));
    assert(reduce(l1, div) == 8);
    assert(reduce(l1, add) == 1046);

    Node<int> *l2 = new Node(1);
    assert(reduce(l2, div) == 1);
    assert(reduce(l2, add) == 1);
}

void testEx2() {
    using namespace std;
    auto n4 = new Node(stack<int>({12}));
    auto n3 = new Node(stack<int>({8, 9, 10, 11}), n4);
    auto n2 = new Node(stack<int>({6, 7}), n3);
    auto n1 = new Node(stack<int>({1, 2, 3, 4, 5}), n2);
    equalize(n1);
    for(auto node = n1; node != nullptr; node = node->next) {
        assert(node->data.size() == 3);
    }
}

void testEx3() {
    Node<int> *l1 = nullptr;
    Node<int> *l2 = new Node(1);
    Node<int> *l3 = new Node(1, new Node(2, new Node(3, new Node(4))));
    Node<int> *l4 = new Node(1, new Node(2, new Node(3, new Node(4, new Node(5)))));
    print(shuffle(l1));
    print(shuffle(l2));
    print(shuffle(l3));
    print(shuffle(l4));
}

int main() {
    testEx1();
    testEx2();
    testEx3();
    return 0;
}
