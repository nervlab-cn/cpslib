/**
 * @author zouxiaoliang
 * @date 2021/7/28
 */

#include <stdlib.h>
#include <string.h>

// memory public function
void* dict_alloc(size_t __count, size_t __sizet) {
    return calloc(__count, __sizet);
}

void dict_free(void* ptr) {
    if (NULL != ptr) {
        free(ptr);
    }
}

// dict function
typedef struct _dict_node {
    char* key;
    void* value;
    struct _dict_node* next;
} dict_node_t;

void dict_fini_node(dict_node_t* n) {
    if (NULL != n) {
        if (NULL != n->key) {
            dict_free(n->key);
        }
        dict_free(n);
    }
}

typedef struct _dict {
    dict_node_t* root;
    void (*free_value)(void*);
} dict_t;

dict_t* dict_init(void (*how_to_free_value)(void*)) {
    dict_t* d = dict_alloc(1, sizeof(dict_t));
    if (NULL != d) {
        d->free_value = how_to_free_value;
    }

    return d;
}

void dict_fini(dict_t* dict) {
    if (NULL != dict) {
        if (NULL != dict->root) {
            dict_node_t* ptr;
            for (; NULL != dict->root;) {
                ptr = dict->root;

                // remove from the link
                dict->root = dict->root->next;

                // free value
                if (NULL != dict->free_value) {
                    dict->free_value(ptr->value);
                }
                // free node
                dict_fini_node(ptr);
            }
        }
        dict_free(dict);
    }
}

void* dict_get(dict_t* dict, const char* key) {
    if (NULL == dict || NULL == key)
        return NULL;

    dict_node_t* ptr;
    for (ptr = dict->root; ptr != NULL; ptr = ptr->next) {
        if (0 == strcmp(ptr->key, key)) {
            return ptr->value;
        }
    }
    return NULL;
}

void dict_del(dict_t* dict, const char* key) {
    if (NULL == dict || NULL == dict->root || NULL == key) {
        return;
    }

    dict_node_t *ptr, *prev;
    for (ptr = dict->root, prev = NULL; ptr != NULL;
         prev = ptr, ptr = ptr->next) {
        if (strcmp(ptr->key, key) == 0) {
            // remove from link
            if (ptr->next != NULL) {
                if (prev == NULL) {
                    dict->root = ptr->next;
                } else {
                    prev->next = ptr->next;
                }
            } else if (prev != NULL) {
                prev->next = NULL;
            } else {
                dict->root = NULL;
            }

            // free value
            if (NULL != dict->free_value) {
                dict->free_value(ptr->value);
            }

            // from key and node
            dict_fini_node(ptr);

            return;
        }
    }
}

int dict_set(dict_t* dict, const char* key, void* value) {
    if (NULL == dict || NULL == key || NULL == value) {
        return -1;
    }

    dict_del(dict,
             key); /* If we already have a item with this key, delete it. */

    dict_node_t* d = dict_alloc(1, sizeof(dict_node_t));
    if (NULL == d) {
        return -2;
    }

    d->key = dict_alloc(1, strlen(key) + 1);
    if (NULL == d->key) {
        dict_free(d);
        return -3;
    }

    strncpy(d->key, key, strlen(key));
    d->key[strlen(key)] = '\0';
    d->value = value;
    d->next = dict->root;
    dict->root = d;

    return 0;
}

void for_each(dict_t* dict, void show(const char*, const void*)) {
    if (NULL == dict || NULL == show) {
        return;
    }

    dict_node_t* ptr;
    for (ptr = dict->root; NULL != ptr; ptr = ptr->next) {
        show(ptr->key, ptr->value);
    }
}
