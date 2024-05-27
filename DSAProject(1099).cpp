                          //Rehana Kousar
                          //BSCS 3rd 2M 
                          //roll no: 1099



#include <iostream>
#include <stack>
#include <string>

class TextEditor {
private:
    std::string text;
    std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;
    int cursor;

public:
    TextEditor() : cursor(0) {}

    void insertCharacter(char c) {
        // Save current state to undo stack
        undoStack.push(text);
        // Clear redo stack on new action
        while (!redoStack.empty()) redoStack.pop();

        // Insert character at the current cursor position
        text.insert(cursor, 1, c);
        cursor++;
    }

    void deleteCharacter() {
        if (cursor > 0 && cursor <= text.length()) {
            // Save current state to undo stack
            undoStack.push(text);
            // Clear redo stack on new action
            while (!redoStack.empty()) redoStack.pop();

            // Delete character at the cursor position
            text.erase(cursor - 1, 1);
            cursor--;
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            // Save current state to redo stack
            redoStack.push(text);

            // Restore state from undo stack
            text = undoStack.top();
            undoStack.pop();

            // Update cursor position
            cursor = text.length();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            // Save current state to undo stack
            undoStack.push(text);

            // Restore state from redo stack
            text = redoStack.top();
            redoStack.pop();

            // Update cursor position
            cursor = text.length();
        }
    }

    void next() {
        if (cursor < text.length()) cursor++;
    }

    void previous() {
        if (cursor > 0) cursor--;
    }

    void start() {
        cursor = 0;
    }

    void end() {
        cursor = text.length();
    }

    void curr_position(int pos) {
        if (pos >= 0 && pos <= text.length()) {
            cursor = pos;
        }
    }

    std::string getText() const {
        return text;
    }
};

int main() {
    TextEditor editor;
    editor.insertCharacter('r');
    editor.insertCharacter('o');
    editor.insertCharacter('m');
    editor.insertCharacter('a');
    editor.insertCharacter('n');

    std::cout << editor.getText() << std::endl; // Expected output: roman

    editor.undo();
    std::cout << editor.getText() << std::endl; // Expected output: roma

    editor.redo();
    std::cout << editor.getText() << std::endl; // Expected output: roman

    editor.start();
    editor.insertCharacter('A');
    std::cout << editor.getText() << std::endl; // Expected output: Aroman

    editor.end();
    editor.deleteCharacter();
    std::cout << editor.getText() << std::endl; // Expected output: Aroma

    editor.curr_position(1);
    editor.insertCharacter('B');
    std::cout << editor.getText() << std::endl; // Expected output: ABroma

    return 0;
}
