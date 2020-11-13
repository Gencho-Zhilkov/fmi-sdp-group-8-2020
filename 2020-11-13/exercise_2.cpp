/*
(1.25 т) Задача 2. Имаме свързан списък L от циклични списъци от уникални в рамките на съответния цикличен списък
символи, както и текстов файл, в който е записано изречение. Да се имплементира външна функция, която приема един
такъв списък и проверява дали изречението от файла може да се прочете в рамките на L, като първата дума от
изречението трябва да може да се прочете в рамките на първия цикличен списък, втората дума от изречението във
втория цикличен списък и т.н. Думите са с максимална дължина до 20 символа.

Забележки:
    1. Приемаме, че една дума може да се прочете в рамките на един цикличен списък, ако буквите на думата се
    намират в последователни елементи на цикличния списък. Например, ако в списъка имаме последователно
    символите ‘c’, ‘h’, ‘a’ и ‘r’, то една дума, която може да се прочете в него е “arch”.
    2. В рамките на текстовия файл изречението може да има следните препинателни знаци - ‘.’ (точка) ‘,’ (запетая),
    ‘:’ (две точки), ‘;’(точка и запетая), ‘?’ и ‘!’. Знаците НЕ участват при проверката в рамките на цикличните
    списъци.
*/
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>


struct CNode {
    CNode *next;
    char letter;
};

class CircularList {
private:
    CNode *head;

public:
    // За тестване: не е необходимо да го имплементирате.
    CircularList(const std::string& word): head(nullptr) {
        CNode *last = nullptr;
        for(auto c: word) {
            auto node = new CNode();
            node->letter = c;
            if(last != nullptr) {
                last->next = node;
            } else {
                assert(head == nullptr);
                head = node;
            }
            last = node;
        }
        last->next = head;
    }

    CNode *find(const char c) {
        if (head == nullptr) {
            return nullptr;
        }

        auto node = head;
        do {
            if (node->letter == c) {
                return node;
            }
            node = node->next;
        } while(node != head);

        // not found
        return nullptr;
    }

    // Дефинирана по този начин, списъкът 'b' -> 'a',
    // ще прочете успешно думата "baba"
    bool canReadWord(const std::string& word) {
        assert(!word.empty());

        auto it = find(word[0]);
        if (it == nullptr) {
            return false;
        }

        for(auto c: word) {
            if (c != it->letter) {
                return false;
            }
            it = it->next;
        }
        return true;
    }
};


std::string readSentence(std::string filename) {
    std::string sentence = "";
    std::ifstream myfile(filename);
    assert(myfile.is_open()); // TODO: raise error

    std::string line;
    while(std::getline(myfile, line)) {
        sentence += line + " ";
    }
    myfile.close();
    return sentence;
}

std::deque<std::string> splitIntoWords(std::string sentence) {
    std::deque<std::string> words;
    auto word_start = sentence.begin(), it = sentence.begin();

    for(; it != sentence.end(); ++it) {
        switch(*it) {
            case ' ':
            case ',':
            case ':':
            case ';':
            case '.':
            case '?':
            case '!':
                if (word_start != it) {
                    words.push_back(std::string(word_start, it));
                }
                word_start = (it+1);
                break;
            default: // Приемаме, че всички други символи са малки или главни букви.
                assert(('a' <= *it && *it <= 'z') || ('A' <= *it && *it <= 'Z'));
                break;
        }
    }

    // проверка за последна дума, в случай, че sentence не завършва с препинателен знак
    if(word_start != sentence.end()) {
        words.push_back(std::string(word_start, sentence.end()));
    }
    return words;
}

bool canReadSentence(std::string filename, std::list<CircularList> lists) {
    auto sentence = readSentence(filename);
    auto words = splitIntoWords(sentence);

    auto wordIt = words.begin();
    for(auto lIt = lists.begin(); wordIt != words.end() && lIt != lists.end(); ++wordIt, ++lIt) {
        if (!lIt->canReadWord(*wordIt)) {
            return false;
        }
    }
    return (wordIt == words.end()); // проверка дали сме прочели всички думи от изречението
}


int main() {
    using namespace std;

    auto sentence = "To sleep, perchance to dream? Aye";
    for(auto word: splitIntoWords(sentence)) {
        cout << word << ' ';
    }
    cout << endl;

    CircularList l1("slept"), l2("eptsl"), l3("eplts");
    cout << l1.canReadWord("slept") << endl;
    cout << l2.canReadWord("slept") << endl;
    cout << l3.canReadWord("slept") << endl;

    return 0;
}
