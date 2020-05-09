#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
}lept_context;

static void lept_parse_whitespace(lept_context* c) {        //json的语法使 ws value ws，这个函数的作用就是跳过前面的ws
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_null(lept_context* c, lept_value* v) {    //判断是否是null这个字符串
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;                     //为了减少解析函数之间传递多个参数，把数据都放进一个结构体内
    v->type = LEPT_NULL;               //初始化v的type
    lept_parse_whitespace(&c);         //跳过前面的ws，用c读出输入字符串的value
    return lept_parse_value(&c, v);    //返回状态码，作用是检查输入的value是否合法
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
