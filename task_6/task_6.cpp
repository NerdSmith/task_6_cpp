#include <iostream>
#include <string>
#include <vector>

enum color {red, blue, black};

struct Item {
    Item(int id) {
        this->id = id;
    }
    ~Item() {}
    int id;
    union {
        struct {
            char title[30];
            int isbn;
            int pages;
        } book;
        struct {
            int rigidity;
            color color;
        } pencil;
    };
};


void print(Item* item, int nb) {
    if (item->id == 0) {
        std::cout << "____________________________\n";
        std::cout << "| # | TITLE | ISBN | Pages |\n";
        std::cout << "| " << nb << " | " << item->book.title << " | " << item->book.isbn << " | " << item->book.pages << " | \n";
        std::cout << "____________________________\n";
    }
    else if (item->id == 1) {
        std::string color;
        switch (item->pencil.color)
        {
        case red:
            color = "red";
            break;
        case blue:
            color = "blue";
            break;
        case black:
            color = "black";
            break;
        default:
            break;
        }
        std::cout << "________________________\n";
        std::cout << "| # | Rigidity | Color |\n";
        std::cout << "| " << nb << " | " << item->pencil.rigidity << " | " << color << " | \n";
        std::cout << "________________________\n";
    }
}

Item* create_new_item() {
    Item *new_item;
    int id;
    std::cout << "Enter the item type (0 for books, 1 for pencils): ";
    std::cin >> id;
    new_item = new Item(id);

    std::string color_s;
    if (new_item->id == 0) {
        std::cout << "Enter title, ISBN and number of pages of book: ";
        std::cin >> new_item->book.title >> new_item->book.isbn >> new_item->book.pages;
    }
    else if (new_item->id == 1) {
        std::cout << "Enter rigidity and color of pencil: ";
        std::cin >> new_item->pencil.rigidity >> color_s;
        if (color_s == "red") {
            new_item->pencil.color = red;
        }
        else if (color_s == "blue") {
            new_item->pencil.color = blue;
        }
        else if (color_s == "black") {
            new_item->pencil.color = black;
        }
    }
    return new_item;
}


void controller() {
    std::string command;
    bool flag = 1;
    std::vector<Item*> items;

    while (flag) {
        std::cout << "Enter command (SELECT, INSERT, DELETE, EXIT): ";
        std::cin >> command;
        if (command == "SELECT") {
            std::string filter;
            int id = -2;
            int counter = 0;
            std::cout << "Which elements SELECT (ALL or by ID)? ";
            std::cin >> filter;
            if (filter == "ALL") {
                id = -1;
            }
            else if (filter == "ID") {
                std::cout << "Enter ID: ";
                std::cin >> id;
            }
            if (id != -2) {
                for (Item* item : items) {
                    if (item->id == id or id == -1) {
                        print(item, counter);
                        counter++;
                    }
                }
            }
        }
        else if (command == "INSERT") {
            items.push_back(create_new_item());
        }
        else if (command == "DELETE") {
            int idx;
            std::cout << "Enter index: ";
            std::cin >> idx;
            if (idx >= 0 and idx < items.size()) {
                items.erase(items.begin() + idx);
            }
        }
        else if (command == "EXIT") {
            flag = 0;
        }
        else {
            std::cout << "Unknown command!" << std::endl;
        }
    }
}


int main()
{
    controller();
}
