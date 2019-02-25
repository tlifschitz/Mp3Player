#ifndef GILI9341_H_
#define GILI9341_H_
#include "lvgl/lv_misc/lv_color.h"

void GILI9341_Init(void);
void GILI9341_Flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
void GILI9341_Fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t  color);
void GILI9341_Map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);


#endif /* GILI9341_H_ */
