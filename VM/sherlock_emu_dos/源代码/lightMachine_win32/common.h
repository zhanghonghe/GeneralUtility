#ifndef _COMMON_H
#define _COMMON_H
#include <assert.h>

typedef unsigned char U1;
typedef char S1;
typedef unsigned short U2;
typedef short S2;
typedef unsigned int U4;
typedef int S4;
typedef void* UnKnown;
typedef U4 COLOR;
U2 byte2Word(const U1 byte[]);
enum FileError{notFoundError, readError, OK };
U1 bool2Data(bool f);
enum DataTypeLength{dataType_U1=1, dataType_S1=1, dataType_U2=2, dataType_S2=2, dataType_U4=4, dataType_S4=4};
enum FontType{font_8x8, font_8x14, font_9x16, font_8x16, font_9x14};
#define SIZE_SECTOR 512


#define MASK_00000000  0
#define MASK_00000001  1
#define MASK_00000010  2
#define MASK_00000011  3
#define MASK_00000100  4
#define MASK_00000101  5
#define MASK_00000110  6
#define MASK_00000111  7
#define MASK_00001000  8
#define MASK_00001001  9
#define MASK_00001010  10
#define MASK_00001011  11
#define MASK_00001100  12
#define MASK_00001101  13
#define MASK_00001110  14
#define MASK_00001111  15
#define MASK_00010000  16
#define MASK_00010001  17
#define MASK_00010010  18
#define MASK_00010011  19
#define MASK_00010100  20
#define MASK_00010101  21
#define MASK_00010110  22
#define MASK_00010111  23
#define MASK_00011000  24
#define MASK_00011001  25
#define MASK_00011010  26
#define MASK_00011011  27
#define MASK_00011100  28
#define MASK_00011101  29
#define MASK_00011110  30
#define MASK_00011111  31
#define MASK_00100000  32
#define MASK_00100001  33
#define MASK_00100010  34
#define MASK_00100011  35
#define MASK_00100100  36
#define MASK_00100101  37
#define MASK_00100110  38
#define MASK_00100111  39
#define MASK_00101000  40
#define MASK_00101001  41
#define MASK_00101010  42
#define MASK_00101011  43
#define MASK_00101100  44
#define MASK_00101101  45
#define MASK_00101110  46
#define MASK_00101111  47
#define MASK_00110000  48
#define MASK_00110001  49
#define MASK_00110010  50
#define MASK_00110011  51
#define MASK_00110100  52
#define MASK_00110101  53
#define MASK_00110110  54
#define MASK_00110111  55
#define MASK_00111000  56
#define MASK_00111001  57
#define MASK_00111010  58
#define MASK_00111011  59
#define MASK_00111100  60
#define MASK_00111101  61
#define MASK_00111110  62
#define MASK_00111111  63
#define MASK_01000000  64
#define MASK_01000001  65
#define MASK_01000010  66
#define MASK_01000011  67
#define MASK_01000100  68
#define MASK_01000101  69
#define MASK_01000110  70
#define MASK_01000111  71
#define MASK_01001000  72
#define MASK_01001001  73
#define MASK_01001010  74
#define MASK_01001011  75
#define MASK_01001100  76
#define MASK_01001101  77
#define MASK_01001110  78
#define MASK_01001111  79
#define MASK_01010000  80
#define MASK_01010001  81
#define MASK_01010010  82
#define MASK_01010011  83
#define MASK_01010100  84
#define MASK_01010101  85
#define MASK_01010110  86
#define MASK_01010111  87
#define MASK_01011000  88
#define MASK_01011001  89
#define MASK_01011010  90
#define MASK_01011011  91
#define MASK_01011100  92
#define MASK_01011101  93
#define MASK_01011110  94
#define MASK_01011111  95
#define MASK_01100000  96
#define MASK_01100001  97
#define MASK_01100010  98
#define MASK_01100011  99
#define MASK_01100100  100
#define MASK_01100101  101
#define MASK_01100110  102
#define MASK_01100111  103
#define MASK_01101000  104
#define MASK_01101001  105
#define MASK_01101010  106
#define MASK_01101011  107
#define MASK_01101100  108
#define MASK_01101101  109
#define MASK_01101110  110
#define MASK_01101111  111
#define MASK_01110000  112
#define MASK_01110001  113
#define MASK_01110010  114
#define MASK_01110011  115
#define MASK_01110100  116
#define MASK_01110101  117
#define MASK_01110110  118
#define MASK_01110111  119
#define MASK_01111000  120
#define MASK_01111001  121
#define MASK_01111010  122
#define MASK_01111011  123
#define MASK_01111100  124
#define MASK_01111101  125
#define MASK_01111110  126
#define MASK_01111111  127
#define MASK_10000000  128
#define MASK_10000001  129
#define MASK_10000010  130
#define MASK_10000011  131
#define MASK_10000100  132
#define MASK_10000101  133
#define MASK_10000110  134
#define MASK_10000111  135
#define MASK_10001000  136
#define MASK_10001001  137
#define MASK_10001010  138
#define MASK_10001011  139
#define MASK_10001100  140
#define MASK_10001101  141
#define MASK_10001110  142
#define MASK_10001111  143
#define MASK_10010000  144
#define MASK_10010001  145
#define MASK_10010010  146
#define MASK_10010011  147
#define MASK_10010100  148
#define MASK_10010101  149
#define MASK_10010110  150
#define MASK_10010111  151
#define MASK_10011000  152
#define MASK_10011001  153
#define MASK_10011010  154
#define MASK_10011011  155
#define MASK_10011100  156
#define MASK_10011101  157
#define MASK_10011110  158
#define MASK_10011111  159
#define MASK_10100000  160
#define MASK_10100001  161
#define MASK_10100010  162
#define MASK_10100011  163
#define MASK_10100100  164
#define MASK_10100101  165
#define MASK_10100110  166
#define MASK_10100111  167
#define MASK_10101000  168
#define MASK_10101001  169
#define MASK_10101010  170
#define MASK_10101011  171
#define MASK_10101100  172
#define MASK_10101101  173
#define MASK_10101110  174
#define MASK_10101111  175
#define MASK_10110000  176
#define MASK_10110001  177
#define MASK_10110010  178
#define MASK_10110011  179
#define MASK_10110100  180
#define MASK_10110101  181
#define MASK_10110110  182
#define MASK_10110111  183
#define MASK_10111000  184
#define MASK_10111001  185
#define MASK_10111010  186
#define MASK_10111011  187
#define MASK_10111100  188
#define MASK_10111101  189
#define MASK_10111110  190
#define MASK_10111111  191
#define MASK_11000000  192
#define MASK_11000001  193
#define MASK_11000010  194
#define MASK_11000011  195
#define MASK_11000100  196
#define MASK_11000101  197
#define MASK_11000110  198
#define MASK_11000111  199
#define MASK_11001000  200
#define MASK_11001001  201
#define MASK_11001010  202
#define MASK_11001011  203
#define MASK_11001100  204
#define MASK_11001101  205
#define MASK_11001110  206
#define MASK_11001111  207
#define MASK_11010000  208
#define MASK_11010001  209
#define MASK_11010010  210
#define MASK_11010011  211
#define MASK_11010100  212
#define MASK_11010101  213
#define MASK_11010110  214
#define MASK_11010111  215
#define MASK_11011000  216
#define MASK_11011001  217
#define MASK_11011010  218
#define MASK_11011011  219
#define MASK_11011100  220
#define MASK_11011101  221
#define MASK_11011110  222
#define MASK_11011111  223
#define MASK_11100000  224
#define MASK_11100001  225
#define MASK_11100010  226
#define MASK_11100011  227
#define MASK_11100100  228
#define MASK_11100101  229
#define MASK_11100110  230
#define MASK_11100111  231
#define MASK_11101000  232
#define MASK_11101001  233
#define MASK_11101010  234
#define MASK_11101011  235
#define MASK_11101100  236
#define MASK_11101101  237
#define MASK_11101110  238
#define MASK_11101111  239
#define MASK_11110000  240
#define MASK_11110001  241
#define MASK_11110010  242
#define MASK_11110011  243
#define MASK_11110100  244
#define MASK_11110101  245
#define MASK_11110110  246
#define MASK_11110111  247
#define MASK_11111000  248
#define MASK_11111001  249
#define MASK_11111010  250
#define MASK_11111011  251
#define MASK_11111100  252
#define MASK_11111101  253
#define MASK_11111110  254
#define MASK_11111111  255

#endif