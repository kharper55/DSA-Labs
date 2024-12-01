#ifndef TEXT_EDITOR_HPP
#define TEXT_EDITOR_HPP

#include <iostream>
#include "DLinkedList.hpp"

template <typename Elem>
class TextEditor : public DLinkedList<Elem> {
    private:
        DNode<Elem>* cursor;

    public:
        TextEditor() { // Constructor
            cursor = this->header->next;
        }

        // Insert the character c just after the cursor
        void insertChar(const Elem& e) {
            this->add(cursor, e);
        }

        // Delete the character to the right of the cursor (or do nothing if at the end)
        void deleteChar() {
            if (cursor != this->trailer) {
                DNode<Elem>* toDelete = cursor;
                cursor = cursor->next;
                this->remove(toDelete);
            } else {
                //throw std::runtime_error("Cannot delete at the end of the text.");
                std::cout << "Cannot delete at the end of the text.\n";
            }
        }

        // Move cursor left one character (or nothing if at the beginning)
        void moveCursorLeft() {
            if (cursor->prev != this->header) {
                cursor = cursor->prev;
            } else {
                std::cout << "Cursor is already at the beginning of the text.\n";
            }
        }

        // Move cursor right one character (or do nothing if at the end)
        void moveCursorRight() {
            if (cursor != this->trailer) {
                cursor = cursor->next;
            } else {
                std::cout << "Cursor is already at the end of the text.\n";
            }
        }

        // Print the text and include the cursor
        void displayText() const {
            DNode<Elem>* current = this->header->next;
            while (current != this->trailer) {
                if (current == cursor) {
                    std::cout << "|";
                }
                std::cout << current->elem;
                current = current->next;
            }
            if (cursor == this->trailer) {
                std::cout << "|";
            }
            std::cout << std::endl;
        }
};

#endif // TEXT_EDITOR_HPP
