#ifndef LEPTJSON_H__
#define LEPTJSON_H__

typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

typedef struct {
    lept_type type;
}lept_value;

enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,         //只有空白
    LEPT_PARSE_INVALID_VALUE,        //若值不是那三种字面值（null，ture，false）
    LEPT_PARSE_ROOT_NOT_SINGULAR     //语法不规范，在空白之后还有其他字符
};

int lept_parse(lept_value* v, const char* json); //解析器，返回状态码

lept_type lept_get_type(const lept_value* v);  //访问结果的函数，即获取类型

#endif /* LEPTJSON_H__ */
