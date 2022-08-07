#ifndef __12864_H_
#define __12864_H_

#include"Arduino.h"  

class LCD
{
  private: 

  public:
			void Init();
			void Display_ASCII(uint8_t x, uint8_t y, String byte);
			void Display_Matrix(uint8_t x, uint8_t y, uint16_t matrixType, uint8_t *byte);
			void Display_MatrixClear(uint8_t x, uint8_t y, uint16_t matrixType);
			void Display_MatrixSave(uint8_t Num, uint8_t *byte);
			uint8_t Display_MatrixPicData(uint8_t row, uint8_t column, uint8_t cols, uint8_t *picdat);
};

#endif