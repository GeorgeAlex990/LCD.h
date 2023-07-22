By George

This library is used for Arduino graphic displays.
Require to include <avr/pgmspace.h>.

Commands:

	void Init(); // Initiate the LCD
	void Display_ASCII(uint8_t x, uint8_t y, String byte); // Write characters
	void Display_Matrix(uint8_t x, uint8_t y, uint16_t matrixType, uint8_t *byte);
	void Display_MatrixClear(uint8_t x, uint8_t y, uint16_t matrixType); // Clear character with coordinates (x, y)
 	void Display_Clear(uint16_t matrixType); // Clear the entire display
	void Display_MatrixSave(uint8_t Num, uint8_t *byte);
	uint8_t Display_MatrixPicData(uint8_t row, uint8_t column, uint8_t cols, uint8_t *picdat);
