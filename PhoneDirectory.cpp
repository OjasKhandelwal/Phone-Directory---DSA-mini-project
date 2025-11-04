#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
    Contact* left;
    Contact* right;

    Contact(string n, string p) {
        name = n;
        phone = p;
        left = right = nullptr;
    }
};

class PhoneDirectory {
private:
    Contact* root;

    Contact* insert(Contact* root, string name, string phone) {
        if (!root)
            return new Contact(name, phone);

        if (name < root->name)
            root->left = insert(root->left, name, phone);
        else if (name > root->name)
            root->right = insert(root->right, name, phone);
        else
            cout << "Contact with this name already exists!\n";

        return root;
    }

    Contact* search(Contact* root, string name) {
        if (!root || root->name == name)
            return root;

        if (name < root->name)
            return search(root->left, name);
        else
            return search(root->right, name);
    }

    Contact* findMin(Contact* root) {
        while (root && root->left)
            root = root->left;
        return root;
    }

    Contact* remove(Contact* root, string name) {
        if (!root) return nullptr;

        if (name < root->name)
            root->left = remove(root->left, name);
        else if (name > root->name)
            root->right = remove(root->right, name);
        else {
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            }
            else if (!root->left) {
                Contact* temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right) {
                Contact* temp = root->left;
                delete root;
                return temp;
            }
            else {
                Contact* temp = findMin(root->right);
                root->name = temp->name;
                root->phone = temp->phone;
                root->right = remove(root->right, temp->name);
            }
        }
        return root;
    }

    void inorder(Contact* root) {
        if (!root) return;
        inorder(root->left);
        cout << "Name: " << root->name << " | Phone: " << root->phone << endl;
        inorder(root->right);
    }

public:
    PhoneDirectory() {
        root = nullptr;
    }

    void addContact(string name, string phone) {
        root = insert(root, name, phone);
        cout << "Contact added successfully!\n";
    }

    void searchContact(string name) {
        Contact* res = search(root, name);
        if (res)
            cout << "Found! " << res->name << " -> " << res->phone << endl;
        else
            cout << "Contact not found!\n";
    }

    void deleteContact(string name) {
        root = remove(root, name);
        cout << "Contact deleted (if it existed).\n";
    }

    void displayAll() {
        cout << "\n--- Phone Directory (Alphabetical Order) ---\n";
        inorder(root);
        cout << "-------------------------------------------\n";
    }
};

int main() {
    PhoneDirectory directory;
    int choice;
    string name, phone;

    do {
        cout << "\n===== PHONE DIRECTORY MENU =====\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phone);
                directory.addContact(name, phone);
                break;

            case 2:
                cout << "Enter name to search: ";
                getline(cin, name);
                directory.searchContact(name);
                break;

            case 3:
                cout << "Enter name to delete: ";
                getline(cin, name);
                directory.deleteContact(name);
                break;

            case 4:
                directory.displayAll();
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
