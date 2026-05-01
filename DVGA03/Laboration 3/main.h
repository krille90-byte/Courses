#ifndef NODE_H
#define NODE_H

#define BLUE_TEXT  "\x1b[34m"
#define BOLD_TEXT  "\033[1m"
#define RESET_TEXT "\x1b[0m"

typedef struct nodeElement {
    int data;
    struct nodeElement * next;
} node;

#endif /* NODE_H */