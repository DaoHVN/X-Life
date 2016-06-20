/**************************************************** Key_Board.h ***************************************************/
/* 01-03-2013*/       /*  DaoHVN : Create new */
/******************************************************************************************************************/
#ifndef KEY_BOARD_H
#define KEY_BOARD_H

#include "PREDEFINE.h"

#if (KEYBOARD_CONTROL == ENABLE)

/* define key in pin */

#define PIN_KEY_1       PINC0
#define PIN_KEY_2       PINC1
#define PIN_KEY_3       PINC2
#define PIN_KEY_4       PINC3

/////////////////////////////////////////  

/* Define Status of Key */
#define KEY_ON          0       
#define KEY_OFF         1       
/////////////////////////////////////////

/* Define Event of Key */
#define EVT_KEY_ON        0      
#define EVT_KEY_OFF       1      
#define EVT_KEY_REPEAT    2      
#define EVT_KEY_NO        3      
////////////////////////////////////////

/* Define time Repeat Key */
#define TIME_KEY_REPEAT_FIRST   0x1E    /* = 30 x 100ms Job */        
#define TIME_KEY_REPEAT_SECOND  0x0A    /* = 10 x 100ms Job */        
//////////////////////////////////////////////////////////

// Define Key on, off Value
#define KEY_ON_VALUE      0x03                 
#define KEY_OFF_VALUE     0x00                 

// Define Index of Keys                              
#define KEY_01          0                    
#define KEY_02          1                    
#define KEY_03          2                    
#define KEY_04          3                    
#define KEY_05          4                    
#define KEY_06          5                    
#define KEY_07          6                    
#define KEY_08          7                    
#define KEY_09          8                    
#define KEY_10          9                    
#define KEY_11          10                   
#define KEY_12          11                   
#define KEY_13          12                   
#define KEY_14          13                   
#define KEY_15          14                   
#define KEY_16          15                   

/* Define Mode of keyboard */
#define NORM_MODE         0

///////////////////////////////////////

extern void KeyBoard_Soft_Init(void);
extern void KeyBoard_Hard_Init(void);
extern void KeyBoard_Cal(void);
extern void UpdateKeyBoard(void);

#endif  /* KEYBOARD_CONTROL == ENABLE */

#endif  /* KEYBOARD_H */
/******************* end keyboard.h *********************/


