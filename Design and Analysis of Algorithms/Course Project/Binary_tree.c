//Включваме основни библиотеки на C.

#include <stdio.h>      // За вход/изход (printf) и дефиниция на NULL.
#include <stdlib.h>     // За динамично заделяне на памет (malloc, free).
#include <stdbool.h>    // За използване на тип 'bool' (true/false)

/**
 ============================= * ЧАСТ 1: ДЕФИНИЦИЯ НА СТРУКТУРИТЕ * =============================
 */

/**
 Структура за върховете на ОРИГИНАЛНОТО двоично дърво.
 Това е дървото, което получаваме като вход на задачата.
 */

struct TreeNode {
    int value;               // Стойността (ключът), която съхранява върхът.
    struct TreeNode *left;   // Указател към лявото дете (поддърво).
    struct TreeNode *right;  // Указател към дясното дете (поддърво).
};

/* * Структура за върховете на ПОМОЩНОТО дърво (нашето "Множество/Set").
 * Използваме го като Двоично Дърво за Търсене (BST),
 * за да следим кои стойности вече сме срещнали.
 */
struct VisitedNode {
 int value;                 // Стойността, която сме "видели".
 struct VisitedNode *left;  // Указател към по-малките "видени" стойности.
 struct VisitedNode *right; // Указател към по-големите "видени" стойности.
};

/*
 * ===================================================================
 * ЧАСТ 2: ПОМОЩНИ ФУНКЦИИ (за създаване на дърветата)
 * ===================================================================
 */

/* Създава нов връх за оригиналното дърво */
/* * Помощна функция за създаване на нов връх за ОРИГИНАЛНОТО дърво.
 * Тази функция не е част от алгоритъма, а само за демонстрация.
 */
struct TreeNode* createTreeNode(int value) {
    // Заделяме динамично памет за новия връх.
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {      // Проверка за грешка при заделяне на памет
        perror("Failed to allocate TreeNode");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;     // Задаваме стойността на върха.
    newNode->left = NULL;       // Инициализираме лявото дете като празно (NULL).
    newNode->right = NULL;      // Инициализираме дясното дете като празно (NULL).
    return newNode;             // Връщаме указател към новосъздадения връх.
}

/* Създава нов връх за помощното BST */
/* * Помощна функция за създаване на нов връх за ПОМОЩНОТО BST.
 * Тази функция е част от нашия алгоритъм (вместо "HashSet.add()").
 */
struct VisitedNode* createVisitedNode(int value) {
    // Заделяме памет за новия връх в нашето "множество".
    struct VisitedNode* newNode = (struct VisitedNode*)malloc(sizeof(struct VisitedNode));
    if (newNode == NULL) {      // Добавена проверка за грешка при заделяне на памет
        perror("Failed to allocate VisitedNode");
        exit(EXIT_FAILURE);
    }
 newNode->value = value;        // Задаваме стойността.
 newNode->left = NULL;          // Инициализираме децата като празни.
    newNode->right = NULL;
 return newNode;                // Връщаме новия връх.
}


//Освобождаване на паметта, заета от ПОМОЩНОТО BST.
 
void freeVisitedTree(struct VisitedNode* node) {
    if (node == NULL) {
        return;
}

    // 1. Освобождаваме децата
    freeVisitedTree(node->left);
    freeVisitedTree(node->right);

    // 2. Освобождаваме текущия възел
    free(node);
    }

 // Освобождаване на паметта, заета от ОРИГИНАЛНОТО дърво.

void freeTree(struct TreeNode* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// Принтира предварително дефинирани ASCII визуализации
void printSimplifiedTree(struct TreeNode* root) {

    // Разпознаване на структурата на Test 1 (с дубликат)
    if (root != NULL && //Уверяваме се, че дървото изобщо съществува.
        root->value == 10 &&
        root->left != NULL && // Проверяваме дали има ляво дете.
        root->left->left != NULL &&
        root->left->left->left != NULL &&
        root->left->left->left->value == 7) {

        printf("      10\n"
               "     /  \\\n"
               "    5   15\n"
               "   / \\\n"
               "  3   7\n"
               " / \n"
               "7 <--- Duplicate\n");

    }
    // Разпознаване на структурата на Test 2 (без дубликати)
    else if (root != NULL &&
             root->value == 10 &&
             root->left != NULL &&
             root->left->right != NULL &&
             root->left->right->value == 8) {

        printf("      10\n"
               "     /  \\\n"
               "    5   15\n"
               "   / \\\n"
               "  3   8 (All values are unique)\n");

    }
    // Непозната структура
    else {
        printf("Unknown structure\n");
    }
}



/*
 ============================= * ЧАСТ 3: ЯДРО НА АЛГОРИТЪМА (Логика за проверка) * =============================
 */

/**
 * Функция за вмъкване на стойност в нашето помощно BST (множество).
 * Това е КЛЮЧОВАТА функция, която заменя "HashSet.contains()".
 * @param visitedRoot Двоен указател към корена на нашето BST.
 * (Нужен е двоен указател, за да можем да променим 
 * указателя 'root' на извикващата функция).
 * @param value Стойността, която се опитваме да вмъкнем.
 * @return 'true', ако вмъкването е УСПЕШНО (нова стойност).
 * 'false', ако стойността ВЕЧЕ СЪЩЕСТВУВА (дубликат!).
 **/

bool insertIntoVisitedBST(struct VisitedNode** visitedRoot, int value) {
    // 1. Базов случай на рекурсията: Намерили сме празно място (NULL).
    if (*visitedRoot == NULL) {
        // Стойността не съществува. Създаваме нов връх за нея.
        *visitedRoot = createVisitedNode(value);
        // Връщаме 'true', защото вмъкването беше успешно (това НЕ Е дубликат).
        return true;
    }

    // 2. Проверка за дубликат: Стойността вече съществува в дървото.
    if (value == (*visitedRoot)->value) {
        // НАМЕРЕН Е ДУБЛИКАТ!
        // Връщаме 'false', за да сигнализираме, че вмъкването е НЕУСПЕШНО.
        return false;
    }

    // 3. Рекурсивно търсене на място за вмъкване (Логика на BST).
    if (value < (*visitedRoot)->value) {
        // Ако стойността е по-малка, отиваме в лявото поддърво.
        return insertIntoVisitedBST(&((*visitedRoot)->left), value);
    } else {
        // Ако стойността е по-голяма, отиваме в дясното поддърво.
        return insertIntoVisitedBST(&((*visitedRoot)->right), value);
    }
}

/**
 * Главна рекурсивна функция за обхождане на ОРИГИНАЛНОТО дърво (Preorder).
 *
 * @param originalNode Указател към текущия връх от ОРИГИНАЛНОТО дърво.
 * @param visitedRoot Двоен указател към корена на ПОМОЩНОТО BST.
 * @return 'true', ако е намерен дубликат, иначе 'false'.
 */

bool checkDuplicatesRecursive(struct TreeNode* originalNode, struct VisitedNode** visitedRoot) {
    // 1. Базов случай: Достигнали сме край на клон (NULL) в оригиналното дърво.
    if (originalNode == NULL) {
        // Тук няма дубликат, връщаме 'false'.
        return false;
    }

 // 2. Обработваме текущия връх като се опитваме да вмъкнем стойност в помощното дърво
    if (insertIntoVisitedBST(visitedRoot, originalNode->value) == false) {
  // Ако функцията върне 'false' - стойността вече е била там. НАМЕРИХМЕ ДУБЛИКАТ!
        return true; // Незабавно прекратяваме и връщаме 'true'.
    }

 // 3. Рекурсивно проверяваме лявото поддърво.
    if (checkDuplicatesRecursive(originalNode->left, visitedRoot)) {
  return true;  // При намерен дубликат, предаваме 'true' нагоре по веригата.
    }

 // 4. Рекурсивно проверяваме дясното поддърво.
    if (checkDuplicatesRecursive(originalNode->right, visitedRoot)) {
        // Ако вдясно е намерен дубликат, предаваме 'true' нагоре по веригата.
        return true;
    }

 // 5. Ако  не е намерен дубликат в този клон, връщаме 'false'.
    return false;
}

/**
 ============================= * ЧАСТ 4: ГЛАВНА ФУНКЦИЯ И ДЕМОНСТРАЦИЯ * =============================

 * Публична "обвиваща" (wrapper) функция, която стартира процеса.
 * @param root Коренът на ОРИГИНАЛНОТО дърво за проверка.
 * @return 'true', ако има дубликати, 'false', ако няма.
 *
 */

bool containsDuplicateValues(struct TreeNode* root) {
    // Създаваме празно помощно BST (използваме го като множество).
    // Коренът му е NULL.
    struct VisitedNode* visitedRoot = NULL;

    // 2. Извикваме рекурсивната функция, която ще обходи
    // оригиналното дърво и ще пълни помощното BST.
    bool result = checkDuplicatesRecursive(root, &visitedRoot);

    // 3. (Почистване) Трябва да освободим паметта, заета от
    // помощното BST. Тази функция не е показана тук,
    // но е задължителна за коректна програма (free_visited_tree(visitedRoot)).

    // Почистваме паметта на помощното BST
    freeVisitedTree(visitedRoot);

    // 4. Връщаме крайния резултат.
    return result;
}


// Главна функция на програмата за демонстрация.
int main() {
    bool actual_result;    // Резултатът, върнат от тестваната функция
    bool expected_result;  // Очакваният правилен резултат за теста
    char* test_status;     // Текстово съобщение „PASS“ или „FAIL“


    printf("--- Test 1: Tree With Duplicates (Expected: TRUE) ---\n");
    printf("Tree Structure:\n");

    struct TreeNode* rootWithDuplicates = createTreeNode(10);
    rootWithDuplicates->left = createTreeNode(5);
    rootWithDuplicates->right = createTreeNode(15);
    rootWithDuplicates->left->left = createTreeNode(3);
    rootWithDuplicates->left->right = createTreeNode(7); // Първа 7-ца
    rootWithDuplicates->left->left->left = createTreeNode(7); // Втора 7-ца (Дубликат!)

    // Използваме твърдо кодираното принтиране
    printSimplifiedTree(rootWithDuplicates);
    printf("\n");

    expected_result = true;
    actual_result = containsDuplicateValues(rootWithDuplicates);

    if (actual_result == expected_result) {
        test_status = "SUCCESS!";
    } else {
        test_status = "FAILURE!";
    }

    if (actual_result) {
        printf("Check Result: Duplicate found (TRUE)\n");
    } 
    else {
        printf("Check Result: No duplicate found (FALSE)\n");
    }

    printf("Test 1 STATUS: %s\n", test_status);

    // Почистваме паметта на тестовото дърво 1
    freeTree(rootWithDuplicates);


    // --- Test 2: Дърво БЕЗ Дубликати ---
    printf("\n--- Test 2: Tree WITHOUT Duplicates (Expected: FALSE) ---\n");
    printf("Tree Structure:\n");
    struct TreeNode* rootWithoutDuplicates = createTreeNode(10);
    rootWithoutDuplicates->left = createTreeNode(5);
    rootWithoutDuplicates->right = createTreeNode(15);
    rootWithoutDuplicates->left->left = createTreeNode(3);
    rootWithoutDuplicates->left->right = createTreeNode(8); // Всички са уникални

    // Използваме твърдо кодираното принтиране
    printSimplifiedTree(rootWithoutDuplicates);
    printf("\n");

    expected_result = false;
    actual_result = containsDuplicateValues(rootWithoutDuplicates);

    if (actual_result == expected_result) {
        test_status = "SUCCESS!";
    } else {
        test_status = "FAILURE!";
    }

    if (actual_result) {
    printf("Check Result: Duplicate found (TRUE)\n");
    } else {
    printf("Check Result: No duplicate found (FALSE)\n");
    }
    printf("Test 2 STATUS: %s\n", test_status);

    freeTree(rootWithoutDuplicates);

    return 0;
}
