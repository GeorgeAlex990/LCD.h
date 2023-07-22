#include "LCD.h"
#include "Wire.h"


/* LCD initialization */
void LCD::Init(void)
{
	Wire.begin();	
	delay(20);
}


/* single character display */
void LCD::Display_ASCII(uint8_t x, uint8_t y, String byte)
{
	uint8_t buf[22];
	uint8_t datalength;
	
	datalength = byte.length();
	
	byte.toCharArray(buf,datalength+1);
	
	Wire.beginTransmission(2);
	Wire.write(1);
	Wire.write(datalength);
	Wire.write(x);
	Wire.write(y);
	Wire.write(buf,datalength);
	Wire.endTransmission();
	if(datalength>12)
	{
		delay(10);
	}
	else
	{
		delay(5);
	}
}

void LCD::Display_Matrix(uint8_t x, uint8_t y, uint16_t matrixType, uint8_t *byte)
{
	uint16_t datalength;
	uint8_t  datatype;
	
	/* 8*8 matrix */
	if(matrixType==88)
	{
		datatype = 2;
		datalength = 8;
	}
	/* 8*16 matrix */
	else if(matrixType==816)
	{
		datatype = 3;
		datalength = 16;
	}
	/* 16*16 matrix */
	else if(matrixType==1616)
	{
		datatype = 4;
		datalength = 32;
	}
	/* 1*8 matrix */
	else if(matrixType==18)
	{
		datatype = 5;
		datalength = 1;		
	}
	/* custom matrix */
	else if((matrixType>>4)==0x0e)
	{
		datatype = matrixType;
		datalength = 1;
	}	
	
	Wire.beginTransmission(2);			//I2C address
	Wire.write(datatype);				//display data type
	Wire.write(datalength);				//display data lenght
	Wire.write(x);						//display content X coordinate
	Wire.write(y);						//display content Y coordinate
	if((matrixType>>4)!=0x0e)			//custom graphics, do not send display data
	{
		Wire.write(byte,datalength);	//display data
	}	
	Wire.endTransmission();
	

	if(datatype==2)
	{
		delay(5);
	}
	if(datatype==3)
	{
		delay(6);
	}
	else if(datatype==4)
	{
		delay(8);
	}
	else if(datatype==5)
	{
		 //delay(5);
		 delayMicroseconds(500); 
		
	}	
	else if((datatype>0xe0)&&(datatype<0xe9))
	{
		delay(40);
	}
	else if((datatype>0xe8)&&(datatype<0xed))
	{
		delay(70);
	}
}


void LCD::Display_MatrixClear(uint8_t x, uint8_t y, uint16_t matrixType)
{
	uint8_t  datatype;
	
	// 8*8 matrix
	if(matrixType==88)
	{
		datatype = 2;
	}
	// 8*16 matrix
	else if(matrixType==816)
	{
		datatype = 3;
	}
	// 16*16 matrix
	else if(matrixType==1616)
	{
		datatype = 4;
	}
	// 1*8 matrix
	else if(matrixType==18)
	{
		datatype = 5;		
	}
	// define figure flower
	else if((matrixType>>4)==0x0e)
	{
		datatype = matrixType;
	}
	// clear screen
	else if((matrixType>>4)==0x0c)
	{
		datatype = matrixType;
	}
	
	
	Wire.beginTransmission(2);			//I2C address
	Wire.write(datatype);				//display data type
	Wire.write(0);						//display data lenght
	Wire.write(x);						//display content X coordinate
	Wire.write(y);						//display content Y coordinate
	Wire.endTransmission();	
	
	if(datatype==0xc0)
	{
		delay(30);
	}
	else
	{
		delay(3);
	}
}

void LCD:Display_Clear(uint16_t matrixType) {

	uint8_t  datatype;
	uint8_t	 maxW, maxH;

	// 8*8 matrix
	if(matrixType==88)
	{
		datatype = 2;
		maxW = 8;
		maxH = 8;
	}
	// 8*16 matrix
	else if(matrixType==816)
	{
		datatype = 3;
		maxW = 16;
		maxH = 8;
	}
	// 16*16 matrix
	else if(matrixType==1616)
	{
		datatype = 4;
		maxW = 16;
		maxH = 16;
	}
	// 1*8 matrix
	else if(matrixType==18)
	{
		datatype = 5;	
		maxW = 8;
		maxH = 1;
	}
	// define figure flower
	else if((matrixType>>4)==0x0e)
	{
		datatype = matrixType;
	}
	// clear screen
	else if((matrixType>>4)==0x0c)
	{
		datatype = matrixType;
	}

	for (uint8_t x = 0; x <= maxW; ++x) {
		for (uint8_t y = 0; y <= maxH; ++y) {
			Wire.beginTransmission(2);			//I2C address
			Wire.write(datatype);				//display data type
			Wire.write(0);						//display data lenght
			Wire.write(x);						//display content X coordinate
			Wire.write(y);						//display content Y coordinate
			Wire.endTransmission();	
		}
	}
	
	if(datatype==0xc0)
	{
		delay(30);
	}
	else
	{
		delay(3);
	}
}

void LCD::Display_MatrixSave(uint8_t Num, uint8_t *byte)
{
	uint8_t datalength;

	/* Custom graphics */
	if(Num<9)
	{
		datalength = 16;
	}	
	else 
	{
		datalength = 32;
	}
	
	Wire.beginTransmission(2);			//I2C address
	Wire.write(Num|0xf0);				//display data type
	Wire.write(datalength);				//display data lenght
	Wire.write(0);						//display content X coordinate
	Wire.write(0);						//diplay content Y coordinate
	Wire.write(byte,datalength);		//display data			
	Wire.endTransmission();
	
	delay(50);

}


uint8_t LCD::Display_MatrixPicData(uint8_t row, uint8_t column, uint8_t cols, uint8_t *picdat)
{
	uint16_t num;
	uint8_t dat;
	uint8_t dataddr;
	
	num = (row-1)*cols + column;
	dat = pgm_read_byte_near(picdat + num-1);
	
	// dataddr = &dat;
	
	return dat;
}






