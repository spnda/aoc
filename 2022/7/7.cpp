#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <vector>

struct FilesystemNode {
    // Size of all files in this directory, but not in subdirectories.
    uint64_t ownSize = 0;
    uint64_t fullSize = 0;
    FilesystemNode* parent;
    std::string name;
    std::vector<FilesystemNode*> children;
};

void updateSum(FilesystemNode* node, uint64_t* sum) {
    if (node->fullSize <= 100000) {
        *sum += node->fullSize;
    }

    for (auto& child : node->children) {
        updateSum(child, sum);
    }
}

void findSmallest(FilesystemNode* node, uint64_t* smallest, uint64_t target) {
    if (node->fullSize >= target && node->fullSize < *smallest) {
        *smallest = node->fullSize;
    }

    for (auto& child : node->children) {
        findSmallest(child, smallest, target);
    }
}

void freeMemory(FilesystemNode* node) {
    for (auto& child : node->children) {
        freeMemory(child);
        delete child;
    }
}

int main() {
    std::ifstream terminal("terminal.txt");

    std::string ln;
    FilesystemNode root = { .parent = nullptr, };
    FilesystemNode* cursor;
    while (std::getline(terminal, ln)) {
        auto cmd = ln.substr(2, 2);
        if (cmd == "cd") {
            if (ln[5] == '/' && ln.size() == 6) {
                cursor = &root;
            } else if (ln.substr(5, 2) == "..") {
                for (auto& child : cursor->children) {
                    cursor->fullSize += child->fullSize;
                }
                cursor = cursor->parent;
            } else {
                auto it = std::find_if(cursor->children.begin(), cursor->children.end(), [ln](FilesystemNode* node) {
                    return ln.substr(5) == node->name;
                });
                cursor = *it;
            }
        } else if (cmd == "ls") {
            while (std::getline(terminal, ln)) {
                if (ln.starts_with("dir")) {
                    auto node = new FilesystemNode();
                    node->name = ln.substr(4);
                    node->parent = cursor;
                    cursor->children.emplace_back(node);
                } else {
                    // Parse the file size and store it. We don't care about individual files.
                    cursor->ownSize += std::stoll(ln.substr(0, ln.find(' ')));
                    cursor->fullSize = cursor->ownSize;
                }
                if (!terminal.eof()) {
                    if ((char)terminal.peek() == '$')
                        break;
                }
            }
        }
    }

    // Go up the tree and update sizes.
    while (cursor) {
        for (auto& child : cursor->children) {
            cursor->fullSize += child->fullSize;
        }
        cursor = cursor->parent;
    }

    // Part one
    uint64_t sum = 0;
    cursor = &root; // Reset
    updateSum(cursor, &sum);
    std::cout << sum << std::endl;

    // Part two
    uint64_t spaceToFree = 30'000'000 - (70'000'000 - root.fullSize);
    uint64_t smallestDirectorySize = 70'000'000;
    findSmallest(&root, &smallestDirectorySize, spaceToFree);
    std::cout << smallestDirectorySize << std::endl;

    // Free memory
    freeMemory(&root);
}
