/**
 * @author zouxiaoliang
 * @date 2021/7/28
 */
#ifndef DICT_H
#define DICT_H

/**
 * @brief 使用单链表结构实现简单的字典功能
 */
struct dict_t;

/**
 * @brief dict_init
 * @return
 */
extern struct dict_t* dict_init(void (*how_to_free_value)(void*));

/**
 * @brief dict_fini
 * @param dict
 */
extern void dict_fini(struct dict_t* dict);

/**
 * @brief dict_get
 * @param dict
 * @param key
 * @return
 */
extern void* dict_get(struct dict_t* dict, const char* key);

/**
 * @brief dict_del
 * @param dict
 * @param key
 */
extern void dict_del(struct dict_t* dict, const char* key);

/**
 * @brief dict_set
 * @param dict
 * @param key
 * @param value
 * @return
 */
extern int dict_set(struct dict_t* dict, const char* key, void* value);

/**
 * @brief for_each
 * @param dict
 */
extern void for_each(struct dict_t* dict,
                     void(show)(const char* key, const void* value));

#endif // DICT_H
