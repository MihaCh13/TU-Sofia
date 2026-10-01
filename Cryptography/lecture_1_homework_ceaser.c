#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

static const wchar_t *alphabet = L"абвгдежзийклмнопрстуфхцчшщъьюя";

static wchar_t *encrypt(const wchar_t *text, int shift) {
    size_t len = wcslen(text);
    wchar_t *result = malloc((len + 1) * sizeof(wchar_t));
    if (result == NULL) {
        return NULL;
    }

    size_t alphabet_len = wcslen(alphabet);

    for (size_t i = 0; i < len; i++) {
        const wchar_t *ptr = wcschr(alphabet, text[i]);
        if (ptr != NULL) {
            size_t index = (size_t)(ptr - alphabet);
            size_t new_index = (index + (size_t)shift) % alphabet_len;
            result[i] = alphabet[new_index];
        } else {
            result[i] = text[i];
        }
    }

    result[len] = L'\0'; 
    return result;
}

static wchar_t *decrypt(const wchar_t *text, int shift) {
    size_t len = wcslen(text);
    wchar_t *result = malloc((len + 1) * sizeof(wchar_t));
    if (result == NULL) {
        return NULL;
    }

    size_t alphabet_len = wcslen(alphabet);

    for (size_t i = 0; i < len; i++) {
        const wchar_t *ptr = wcschr(alphabet, text[i]);
        if (ptr != NULL) {
            size_t index = (size_t)(ptr - alphabet);
            size_t new_index = (index + alphabet_len - (size_t)shift) % alphabet_len;
            result[i] = alphabet[new_index];
        } else {
            result[i] = text[i];
        }
    }

    result[len] = L'\0';
    return result;
}

int main() {
    setlocale(LC_ALL, "");

    wchar_t *encrypted = encrypt(L"Искам да излезем на кафе.", 3);
    wprintf(L"%ls\n", encrypted);

    wchar_t *decrypted = decrypt(encrypted, 3);
    wprintf(L"%ls\n", decrypted);

    free(encrypted);
    free(decrypted);

    return 0;
}