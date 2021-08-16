#define  ENCODER_OPTIMIZE_INTERRUPTS
#include <Wire.h>
#include <Encoder.h>


//CV
float CV_IN = 512;//CV_IN
float old_CV_IN = 512;//
int CV_INr = 512;//CV_IN
int CV_INh = 10;
int i = 0; //
long old_CV_OUT = 0;


static int DOUBLE_CLICK_TIME = 500;  //Max time beetween double click detection in ms

//slide
int slide_CV = 0 ; //slide_knob
int slide_time = 1 ;
int scale = 1;
int scale_enc = 1;
int scale_CV = 0;
int rotate = 0;
int rotate_enc = 0;
int rotate_CV = 0;
int control = 0;
int control_mode = 0;
byte enc_switch_in = 0;
unsigned long enc_switch_timer = 0;
bool enc_switch_latch = false;
byte enc_switch_counter = 0;
byte enc_switch = 0;
byte slide = 0;//0=OFF,1=ON
byte toggle_switch = 0;//0=EXT,1=ON
int j = 0;


int CV_transpose = 0;




int LED_Brightness = 50;


Encoder myEnc(2, 3);
float oldPosition1  = -999;
float newPosition1 = -999;

float oldPosition2 = -999;
float newPosition2 = -999;

float oldPosition3 = -999;
float newPosition3 = -999;





//------------------------------------scale list begin ---------------------------------------









//0=major
const static word DAC_LSB_C_maj[61] PROGMEM = {
0, 136, 272, 340, 476, 612, 748, 816, 952, 1088,  1156,  1292,  1428,  1564,  1632,  1768,  1904,  1972,  2108,  2244,  2380,  2448,  2584,  2720,  2788,  2924,  3060,  3196,  3264,  3400,  3536,  3604,  3740 , 3876 , 4012 , 4080
};
const static word CVIN_th_C_maj[62] PROGMEM = {
0, 17,  51,  77,  102, 136, 170, 196, 221, 255, 281, 306, 340, 374, 400, 425, 459, 485, 510, 544, 578, 604, 629, 663, 689, 714, 748, 782, 808, 833, 867, 893, 918, 952, 986, 1012
};






const static word DAC_LSB_CS_maj[61] PROGMEM = {
0, 68, 204,  340,  408,  544,  680,  816,  884,  1020, 1156, 1224, 1360, 1496, 1632, 1700, 1836, 1972, 2040, 2176, 2312, 2448, 2516, 2652, 2788, 2856, 2992, 3128, 3264, 3332, 3468, 3604, 3672, 3808, 3944, 4080
};
const static word CVIN_th_CS_maj[62] PROGMEM = {
0, 9,  34, 68, 94, 119,  153,  187,  213,  238,  272,  298,  323,  357,  391,  417,  442,  476,  502,  527,  561,  595,  621,  646,  680,  706,  731,  765,  799,  825,  850,  884,  910,  935,  969,  1003
};







const static word DAC_LSB_D_maj[61] PROGMEM = {
68,  136,  272,  408,  476,  612,  748,  884,  952,  1088, 1224, 1292, 1428, 1564, 1700, 1768, 1904, 2040, 2108, 2244, 2380, 2516, 2584, 2720, 2856, 2924, 3060, 3196, 3332, 3400, 3536, 3672, 3740, 3876, 4012                                                    
};
const static word CVIN_th_D_maj[62] PROGMEM = {
0,  26, 51, 85, 111,  136,  170,  204,  230,  255,  289,  315,  340,  374,  408,  434,  459,  493,  519,  544,  578,  612,  638,  663,  697,  723,  748,  782,  816,  842,  867,  901,  927,  952,  986                                                     
};







const static word DAC_LSB_DS_maj[61] PROGMEM = {
0,  136,  204,  340,  476,  544,  680,  816,  952,  1020, 1156, 1292, 1360, 1496, 1632, 1768, 1836, 1972, 2108, 2176, 2312, 2448, 2584, 2652, 2788, 2924, 2992, 3128, 3264, 3400, 3468, 3604, 3740, 3808, 3944, 4080                                                    
};
const static word CVIN_th_DS_maj[62] PROGMEM = {
0,  17, 43, 68, 102,  128,  153,  187,  221,  247,  272,  306,  332,  357,  391,  425,  451,  476,  510,  536,  561,  595,  629,  655,  680,  714,  740,  765,  799,  833,  859,  884,  918,  944,  969,  1003                                                    
};







const static word DAC_LSB_E_maj[61] PROGMEM = {
68,  204,  272,  408,  544,  612,  748,  884,  1020, 1088, 1224, 1360, 1428, 1564, 1700, 1836, 1904, 2040, 2176, 2244, 2380, 2516, 2652, 2720, 2856, 2992, 3060, 3196, 3332, 3468, 3536, 3672, 3808, 3876, 4012                                                    
};
const static word CVIN_th_E_maj[62] PROGMEM = {
0,  34, 60, 85, 119,  145,  170,  204,  238,  264,  289,  323,  349,  374,  408,  442,  468,  493,  527,  553,  578,  612,  646,  672,  697,  731,  757,  782,  816,  850,  876,  901,  935,  961,  986                                                   
};







const static word DAC_LSB_F_maj[61] PROGMEM = {
0,  136,  272,  340,  476,  612,  680,  816,  952,  1088, 1156, 1292, 1428, 1496, 1632, 1768, 1904, 1972, 2108, 2244, 2312, 2448, 2584, 2720, 2788, 2924, 3060, 3128, 3264, 3400, 3536, 3604, 3740, 3876, 3944, 4080                                                  
};
const static word CVIN_th_F_maj[62] PROGMEM = {
0,  17, 51, 77, 102,  136,  162,  187,  221,  255,  281,  306,  340,  366,  391,  425,  459,  485,  510,  544,  570,  595,  629,  663,  689,  714,  748,  774,  799,  833,  867,  893,  918,  952,  978,  1003                                                   
};







const static word DAC_LSB_FS_maj[61] PROGMEM = {
68,  204,  340,  408,  544,  680,  748,  884,  1020, 1156, 1224, 1360, 1496, 1564, 1700, 1836, 1972, 2040, 2176, 2312, 2380, 2516, 2652, 2788, 2856, 2992, 3128, 3196, 3332, 3468, 3604, 3672, 3808, 3944, 4012                                                    
};
const static word CVIN_th_FS_maj[62] PROGMEM = {
0,  34, 68, 94, 119,  153,  179,  204,  238,  272,  298,  323,  357,  383,  408,  442,  476,  502,  527,  561,  587,  612,  646,  680,  706,  731,  765,  791,  816,  850,  884,  910,  935,  969,  995                                                    
};







const static word DAC_LSB_G_maj[61] PROGMEM = {
0,  136,  272,  408,  476,  612,  748,  816,  952,  1088, 1224, 1292, 1428, 1564, 1632, 1768, 1904, 2040, 2108, 2244, 2380, 2448, 2584, 2720, 2856, 2924, 3060, 3196, 3264, 3400, 3536, 3672, 3740, 3876, 4012, 4080                                                   
};
const static word CVIN_th_G_maj[62] PROGMEM = {
0,  17, 51, 85, 111,  136,  170,  196,  221,  255,  289,  315,  340,  374,  400,  425,  459,  493,  519,  544,  578,  604,  629,  663,  697,  723,  748,  782,  808,  833,  867,  901,  927,  952,  986,  1012                                                    
};







const static word DAC_LSB_GS_maj[61] PROGMEM = {
0,  68, 204,  340,  476,  544,  680,  816,  884,  1020, 1156, 1292, 1360, 1496, 1632, 1700, 1836, 1972, 2108, 2176, 2312, 2448, 2516, 2652, 2788, 2924, 2992, 3128, 3264, 3332, 3468, 3604, 3740, 3808, 3944, 4080                                                    
};
const static word CVIN_th_GS_maj[62] PROGMEM = {
0,  9,  34, 68, 102,  128,  153,  187,  213,  238,  272,  306,  332,  357,  391,  417,  442,  476,  510,  536,  561,  595,  621,  646,  680,  714,  740,  765,  799,  825,  850,  884,  918,  944,  969,  1003                                                    
};







const static word DAC_LSB_A_maj[61] PROGMEM = {
68,  136,  272,  408,  544,  612,  748,  884,  952,  1088, 1224, 1360, 1428, 1564, 1700, 1768, 1904, 2040, 2176, 2244, 2380, 2516, 2584, 2720, 2856, 2992, 3060, 3196, 3332, 3400, 3536, 3672, 3808, 3876, 4012                                                      
};
const static word CVIN_th_A_maj[62] PROGMEM = {
0,  26, 51, 85, 119,  145,  170,  204,  230,  255,  289,  323,  349,  374,  408,  434,  459,  493,  527,  553,  578,  612,  638,  663,  697,  731,  757,  782,  816,  842,  867,  901,  935,  961,  986                                                     
};







const static word DAC_LSB_AS_maj[61] PROGMEM = {
0,  136,  204,  340,  476,  612,  680,  816,  952,  1020, 1156, 1292, 1428, 1496, 1632, 1768, 1836, 1972, 2108, 2244, 2312, 2448, 2584, 2652, 2788, 2924, 3060, 3128, 3264, 3400, 3468, 3604, 3740, 3876, 3944, 4080                                                    
};
const static word CVIN_th_AS_maj[62] PROGMEM = {
0,  17, 43, 68, 102,  136,  162,  187,  221,  247,  272,  306,  340,  366,  391,  425,  451,  476,  510,  544,  570,  595,  629,  655,  680,  714,  748,  774,  799,  833,  859,  884,  918,  952,  978,  1003                                                   
};







const static word DAC_LSB_B_maj[61] PROGMEM = {
68,  204,  272,  408,  544,  680,  748,  884,  1020, 1088, 1224, 1360, 1496, 1564, 1700, 1836, 1904, 2040, 2176, 2312, 2380, 2516, 2652, 2720, 2856, 2992, 3128, 3196, 3332, 3468, 3536, 3672, 3808, 3944, 4012                                                    
};
const static word CVIN_th_B_maj[62] PROGMEM = {
0,  34, 60, 85, 119,  153,  179,  204,  238,  264,  289,  323,  357,  383,  408,  442,  468,  493,  527,  561,  587,  612,  646,  672,  697,  731,  765,  791,  816,  850,  876,  901,  935,  969,  995                                                    
};



















//1=major_pentatonic
const static word DAC_LSB_C_mp[61] PROGMEM = {
0, 136, 272, 476, 612, 816, 952, 1088,  1292,  1428,  1632,  1768,  1904,  2108,  2244,  2448,  2584,  2720,  2924,  3060,  3264,  3400,  3536,  3740,  3876,  4080
};
const static word CVIN_th_C_mp[62] PROGMEM = {
0, 17,  51,  94,  136, 179, 221, 255, 298, 340, 383, 425, 459, 502, 544, 587, 629, 663, 706, 748, 791, 833, 867, 910, 952, 995
};








const static word DAC_LSB_CS_mp[61] PROGMEM = {
68,  204,  340,  544,  680,  902,  1020, 1156, 1360, 1496, 1718, 1836, 1972, 2176, 2312, 2534, 2652, 2788, 2992, 3128, 3350, 3468, 3604, 3808, 3944
};
const static word CVIN_th_CS_mp[62] PROGMEM = {
0,  34, 68, 111,  153,  198,  240,  272,  315,  357,  402,  444,  476,  519,  561,  606,  648,  680,  723,  765,  810,  852,  884,  927,  969
};







const static word DAC_LSB_D_mp[61] PROGMEM = {
136,  272,  408,  612,  748,  952,  1088, 1224, 1428, 1564, 1768, 1904, 2040, 2244, 2380, 2584, 2720, 2856, 3060, 3196, 3400, 3536, 3672, 3876, 4012                                                                        
};
const static word CVIN_th_D_mp[62] PROGMEM = {
0,  51, 85, 128,  170,  213,  255,  289,  332,  374,  417,  459,  493,  536,  578,  621,  663,  697,  740,  782,  825,  867,  901,  944,  986                                                                       
};







const static word DAC_LSB_DS_mp[61] PROGMEM = {
0,  204,  340,  476,  680,  816,  1020, 1156, 1292, 1496, 1632, 1836, 1972, 2108, 2312, 2448, 2652, 2788, 2924, 3128, 3264, 3468, 3604, 3740, 3944, 4080                                                                      
};
const static word CVIN_th_DS_mp[62] PROGMEM = {
0,  26, 68, 102,  145,  187,  230,  272,  306,  349,  391,  434,  476,  510,  553,  595,  638,  680,  714,  757,  799,  842,  884,  918,  961,  1003                                                                      
};







const static word DAC_LSB_E_mp[61] PROGMEM = {
68,  272,  408,  544,  748,  884,  1088, 1224, 1360, 1564, 1700, 1904, 2040, 2176, 2380, 2516, 2720, 2856, 2992, 3196, 3332, 3536, 3672, 3808, 4012                                                                        
};
const static word CVIN_th_E_mp[62] PROGMEM = {
0,  43, 85, 119,  162,  204,  247,  289,  323,  366,  408,  451,  493,  527,  570,  612,  655,  697,  731,  774,  816,  859,  901,  935,  978                                                                       
};







const static word DAC_LSB_F_mp[61] PROGMEM = {
0,  136,  340,  476,  612,  816,  952,  1156, 1292, 1428, 1632, 1768, 1972, 2108, 2244, 2448, 2584, 2788, 2924, 3060, 3264, 3400, 3604, 3740, 3876, 4080                                                                      
};
const static word CVIN_th_F_mp[62] PROGMEM = {
0,  17, 60, 102,  136,  179,  221,  264,  306,  340,  383,  425,  468,  510,  544,  587,  629,  672,  714,  748,  791,  833,  876,  918,  952,  995                                                                     
};







const static word DAC_LSB_FS_mp[61] PROGMEM = {
68,  204,  408,  544,  680,  884,  1020, 1224, 1360, 1496, 1700, 1836, 2040, 2176, 2312, 2516, 2652, 2856, 2992, 3128, 3332, 3468, 3672, 3808, 3944                                                                        
};
const static word CVIN_th_FS_mp[62] PROGMEM = {
0,  34, 77, 119,  153,  196,  238,  281,  323,  357,  400,  442,  485,  527,  561,  604,  646,  689,  731,  765,  808,  850,  893,  935,  969                                                                       
};







const static word DAC_LSB_G_mp[61] PROGMEM = {
136,  272,  476,  612,  748,  952,  1088, 1292, 1428, 1564, 1768, 1904, 2108, 2244, 2380, 2584, 2720, 2924, 3060, 3196, 3400, 3536, 3740, 3876, 4012                                                                        
};
const static word CVIN_th_G_mp[62] PROGMEM = {
0,  51, 94, 136,  170,  213,  255,  298,  340,  374,  417,  459,  502,  544,  578,  621,  663,  706,  748,  782,  825,  867,  910,  952,  986                                                                       
};







const static word DAC_LSB_GS_mp[61] PROGMEM = {
0,  204,  340,  544,  680,  816,  1020, 1156, 1360, 1496, 1632, 1836, 1972, 2176, 2312, 2448, 2652, 2788, 2992, 3128, 3264, 3468, 3604, 3808, 3944, 4080                                                                      
};
const static word CVIN_th_GS_mp[62] PROGMEM = {
0,  26, 68, 111,  153,  187,  230,  272,  315,  357,  391,  434,  476,  519,  561,  595,  638,  680,  723,  765,  799,  842,  884,  927,  969,  1003                                                                      
};







const static word DAC_LSB_A_mp[61] PROGMEM = {
68,  272,  408,  612,  748,  884,  1088, 1224, 1428, 1564, 1700, 1904, 2040, 2244, 2380, 2516, 2720, 2856, 3060, 3196, 3332, 3536, 3672, 3876, 4012                                                                        
};
const static word CVIN_th_A_mp[62] PROGMEM = {
0,  43, 85, 128,  170,  204,  247,  289,  332,  374,  408,  451,  493,  536,  578,  612,  655,  697,  740,  782,  816,  859,  901,  944,  986                                                                       
};







const static word DAC_LSB_AS_mp[61] PROGMEM = {
0,  136,  340,  476,  680,  816,  952,  1156, 1292, 1496, 1632, 1768, 1972, 2108, 2312, 2448, 2584, 2788, 2924, 3128, 3264, 3400, 3604, 3740, 3944, 4080                                                                      
};
const static word CVIN_th_AS_mp[62] PROGMEM = {
0,  17, 60, 102,  145,  187,  221,  264,  306,  349,  391,  425,  468,  510,  553,  595,  629,  672,  714,  757,  799,  833,  876,  918,  961,  1003                                                                      
};







const static word DAC_LSB_B_mp[61] PROGMEM = {
68,  204,  408,  544,  748,  884,  1020, 1224, 1360, 1564, 1700, 1836, 2040, 2176, 2380, 2516, 2652, 2856, 2992, 3196, 3332, 3468, 3672, 3808, 4012                                                                        
};
const static word CVIN_th_B_mp[62] PROGMEM = {
0,  34, 77, 119,  162,  204,  238,  281,  323,  366,  408,  442,  485,  527,  570,  612,  646,  689,  731,  774,  816,  850,  893,  935,  978                                                                       
};















//2=major_pentatonic+7
const static word DAC_LSB_C_mp7[61] PROGMEM = {
 0, 136, 272, 476, 612, 748, 816, 952, 1088,  1292,  1428,  1564,  1632,  1768,  1904,  2108,  2244,  2380,  2448 , 2584 , 2720 , 2924 , 3060  ,3196 , 3264 , 3400,  3536 , 3740,  3876 , 4012 , 4080
};
const static word CVIN_th_C_mp7[62] PROGMEM = {
0,  17,  51,  94,  136, 170, 196, 221, 255, 298, 340, 374, 400, 425, 459, 502, 544, 578, 604, 629, 663, 706, 748, 782, 808, 833, 867, 910, 952, 986, 1012
};







const static word DAC_LSB_CS_mp7[61] PROGMEM = {
0,  68, 204,  340,  544,  680,  816,  884,  1020, 1156, 1360, 1496, 1632, 1700, 1836, 1972, 2176, 2312, 2448, 2516, 2652, 2788, 2992, 3128, 3264, 3332, 3468, 3604, 3808, 3944, 4080
};
const static word CVIN_th_CS_mp7[62] PROGMEM = {
0,  9,  34, 68, 111,  153,  187,  213,  238,  272,  315,  357,  391,  417,  442,  476,  519,  561,  595,  621,  646,  680,  723,  765,  799,  825,  850,  884,  927,  969,  1003
};







const static word DAC_LSB_D_mp7[61] PROGMEM = {
68,  136,  272,  408,  612,  748,  884,  952,  1088, 1224, 1428, 1564, 1700, 1768, 1904, 2040, 2244, 2380, 2516, 2584, 2720, 2856, 3060, 3196, 3332, 3400, 3536, 3672, 3876, 4012                                                              

};
const static word CVIN_th_D_mp7[62] PROGMEM = {
0,  26, 51, 85, 128,  170,  204,  230,  255,  289,  332,  374,  408,  434,  459,  493,  536,  578,  612,  638,  663,  697,  740,  782,  816,  842,  867,  901,  944,  986                                                             

};







const static word DAC_LSB_DS_mp7[61] PROGMEM = {
0,  136,  204,  340,  476,  680,  816,  952,  1020, 1156, 1292, 1496, 1632, 1768, 1836, 1972, 2108, 2312, 2448, 2584, 2652, 2788, 2924, 3128, 3264, 3400, 3468, 3604, 3740, 3944, 4080                                                            

};
const static word CVIN_th_DS_mp7[62] PROGMEM = {
0,  17, 43, 68, 102,  145,  187,  221,  247,  272,  306,  349,  391,  425,  451,  476,  510,  553,  595,  629,  655,  680,  714,  757,  799,  833,  859,  884,  918,  961,  1003                                                            

};







const static word DAC_LSB_E_mp7[61] PROGMEM = {
68,  204,  272,  408,  544,  748,  884,  1020, 1088, 1224, 1360, 1564, 1700, 1836, 1904, 2040, 2176, 2380, 2516, 2652, 2720, 2856, 2992, 3196, 3332, 3468, 3536, 3672, 3808, 4012                                                              

};
const static word CVIN_th_E_mp7[62] PROGMEM = {
0,  34, 60, 85, 119,  162,  204,  238,  264,  289,  323,  366,  408,  442,  468,  493,  527,  570,  612,  646,  672,  697,  731,  774,  816,  850,  876,  901,  935,  978                                                             

};







const static word DAC_LSB_F_mp7[61] PROGMEM = {
0,  136,  272,  340,  476,  612,  816,  952,  1088, 1156, 1292, 1428, 1632, 1768, 1904, 1972, 2108, 2244, 2448, 2584, 2720, 2788, 2924, 3060, 3264, 3400, 3536, 3604, 3740, 3876, 4080                                                            

};
const static word CVIN_th_F_mp7[62] PROGMEM = {
0,  17, 51, 77, 102,  136,  179,  221,  255,  281,  306,  340,  383,  425,  459,  485,  510,  544,  587,  629,  663,  689,  714,  748,  791,  833,  867,  893,  918,  952,  995                                                           

};







const static word DAC_LSB_FS_mp7[61] PROGMEM = {
68,  204,  340,  408,  544,  680,  884,  1020, 1156, 1224, 1360, 1496, 1700, 1836, 1972, 2040, 2176, 2312, 2516, 2652, 2788, 2856, 2992, 3128, 3332, 3468, 3604, 3672, 3808, 3944                                                              

};
const static word CVIN_th_FS_mp7[62] PROGMEM = {
0,  34, 68, 94, 119,  153,  196,  238,  272,  298,  323,  357,  400,  442,  476,  502,  527,  561,  604,  646,  680,  706,  731,  765,  808,  850,  884,  910,  935,  969                                                             

};







const static word DAC_LSB_G_mp7[61] PROGMEM = {
136,  272,  408,  476,  612,  748,  952,  1088, 1224, 1292, 1428, 1564, 1768, 1904, 2040, 2108, 2244, 2380, 2584, 2720, 2856, 2924, 3060, 3196, 3400, 3536, 3672, 3740, 3876, 4012                                                              

};
const static word CVIN_th_G_mp7[62] PROGMEM = {
0,  51, 85, 111,  136,  170,  213,  255,  289,  315,  340,  374,  417,  459,  493,  519,  544,  578,  621,  663,  697,  723,  748,  782,  825,  867,  901,  927,  952,  986                                                             

};







const static word DAC_LSB_GS_mp7[61] PROGMEM = {
0,  204,  340,  476,  544,  680,  816,  1020, 1156, 1292, 1360, 1496, 1632, 1836, 1972, 2108, 2176, 2312, 2448, 2652, 2788, 2924, 2992, 3128, 3264, 3468, 3604, 3740, 3808, 3944, 4080                                                            

};
const static word CVIN_th_GS_mp7[62] PROGMEM = {
0,  26, 68, 102,  128,  153,  187,  230,  272,  306,  332,  357,  391,  434,  476,  510,  536,  561,  595,  638,  680,  714,  740,  765,  799,  842,  884,  918,  944,  969,  1003                                                            

};







const static word DAC_LSB_A_mp7[61] PROGMEM = {
68,  272,  408,  544,  612,  748,  884,  1088, 1224, 1360, 1428, 1564, 1700, 1904, 2040, 2176, 2244, 2380, 2516, 2720, 2856, 2992, 3060, 3196, 3332, 3536, 3672, 3808, 3876, 4012                                                              

};
const static word CVIN_th_A_mp7[62] PROGMEM = {
0,  43, 85, 119,  145,  170,  204,  247,  289,  323,  349,  374,  408,  451,  493,  527,  553,  578,  612,  655,  697,  731,  757,  782,  816,  859,  901,  935,  961,  986                                                             

};







const static word DAC_LSB_AS_mp7[61] PROGMEM = {
0,  136,  340,  476,  612,  680,  816,  952,  1156, 1292, 1428, 1496, 1632, 1768, 1972, 2108, 2244, 2312, 2448, 2584, 2788, 2924, 3060, 3128, 3264, 3400, 3604, 3740, 3876, 3944, 4080                                                            

};
const static word CVIN_th_AS_mp7[62] PROGMEM = {
0,  17, 60, 102,  136,  162,  187,  221,  264,  306,  340,  366,  391,  425,  468,  510,  544,  570,  595,  629,  672,  714,  748,  774,  799,  833,  876,  918,  952,  978,  1003                                                            

};







const static word DAC_LSB_B_mp7[61] PROGMEM = {
68,  204,  408,  544,  680,  748,  884,  1020, 1224, 1360, 1496, 1564, 1700, 1836, 2040, 2176, 2312, 2380, 2516, 2652, 2856, 2992, 3128, 3196, 3332, 3468, 3672, 3808, 3944, 4012                                                              

};
const static word CVIN_th_B_mp7[62] PROGMEM = {
0,  34, 77, 119,  153,  179,  204,  238,  281,  323,  357,  383,  408,  442,  485,  527,  561,  587,  612,  646,  689,  731,  765,  791,  816,  850,  893,  935,  969,  995                                                             

};















//3=natural minor , derived from major scales list
//4=minor pentatonic , derived from major pentatonic scales list
















//5=chromatic 
const static word DAC_LSB_chr[61] PROGMEM = {
 0, 68,  136, 204, 272, 340, 408, 476, 544, 612, 680, 748, 816, 884, 952, 1020,  1088,  1156,  1224,  1292,  1360,  1428,  1496,  1564,  1632,  1700,  1768,  1836,  1904,  1972,  2040 , 2108,  2176,  2244,  2312 , 2380,  2448,  2516,  2584,  2652 , 2720,  2788,  2856,  2924,  2992,  3060 , 3128,  3196,  3264,  3332,  3400 , 3468 , 3536 , 3604,  3672,  3740,  3808,  3876,  3944,  4012,  4080
};
const static word CVIN_th_chr[62] PROGMEM = {
0 , 9 ,26,  43,  60,  77,  94,  111, 128, 145, 162, 179, 196, 213, 230, 247, 264, 281, 298, 315, 332, 349, 366, 383, 400, 417, 434, 451, 468, 485, 502, 519, 536, 553, 570 ,587, 604, 621, 638, 655, 672, 689, 706, 723, 740, 757, 774, 791, 808, 825, 842, 859 ,876, 893, 910, 927, 944, 961, 978, 995, 1012
};












//6=octave
const static word DAC_LSB_C_oct[61] PROGMEM = {
0,  816, 1632,  2448,  3264,  4080
};
const static word CVIN_th_C_oct[62] PROGMEM = {
 0, 102, 306, 510, 714, 918
};





const static word DAC_LSB_CS_oct[61] PROGMEM = {
68,  884,  1700, 2516, 3332
};
const static word CVIN_th_CS_oct[62] PROGMEM = {
0,  119,  323,  527,  731
};





const static word DAC_LSB_D_oct[61] PROGMEM = {
136,  952,  1768, 2584, 3400
};
const static word CVIN_th_D_oct[62] PROGMEM = {
0,  136,  340,  544,  748
};





const static word DAC_LSB_DS_oct[61] PROGMEM = {
204,  1020, 1836, 2652, 3468
};
const static word CVIN_th_DS_oct[62] PROGMEM = {
0,  153,  357,  561,  765
};




const static word DAC_LSB_E_oct[61] PROGMEM = {
272,  1088, 1904, 2720, 3536
};
const static word CVIN_th_E_oct[62] PROGMEM = {
0,  170,  374,  578,  782
};




const static word DAC_LSB_F_oct[61] PROGMEM = {
340,  1156, 1972, 2788, 3604
};
const static word CVIN_th_F_oct[62] PROGMEM = {
0,  187,  391,  595,  799
};





const static word DAC_LSB_FS_oct[61] PROGMEM = {
408,  1224, 2040, 2856, 3672
};
const static word CVIN_th_FS_oct[62] PROGMEM = {
0,  204,  408,  612,  816
};





const static word DAC_LSB_G_oct[61] PROGMEM = {
476,  1292, 2108, 2924, 3740
};
const static word CVIN_th_G_oct[62] PROGMEM = {
0,  221,  425,  629,  833
};





const static word DAC_LSB_GS_oct[61] PROGMEM = {
544,  1360, 2176, 2992, 3808
};
const static word CVIN_th_GS_oct[62] PROGMEM = {
0,  238,  442,  646,  850
};





const static word DAC_LSB_A_oct[61] PROGMEM = {
612,  1428, 2244, 3060, 3876
};
const static word CVIN_th_A_oct[62] PROGMEM = {
0,  255,  459,  663,  867
};





const static word DAC_LSB_AS_oct[61] PROGMEM = {
680,  1496, 2312, 3128, 3944
};
const static word CVIN_th_AS_oct[62] PROGMEM = {
0,  272,  476,  680,  884
};





const static word DAC_LSB_B_oct[61] PROGMEM = {
748,  1564, 2380, 3196, 4012
};
const static word CVIN_th_B_oct[62] PROGMEM = {
0,  289,  493,  697,  901
};





// ------------------------SCale List DONE !--------------------------











void setup() {

       pinMode(9, OUTPUT); //Color_LED_R
       pinMode(11, OUTPUT); //Color_LED_G
       pinMode(10, OUTPUT); //Color_LED_B
       pinMode(5, OUTPUT); //gate_out
       pinMode(6, INPUT_PULLUP); //Encoder Button 
       pinMode(7, INPUT_PULLUP); //switch
      
      
       Serial.begin(9600);
       Wire.begin();

}





void loop() {






 enc_switch_in  = !digitalRead(6);

 if ((enc_switch_in == true) && (enc_switch_latch == false)) {  //Count Times Button Pressed
    enc_switch_counter++;
    enc_switch_timer = millis();
    enc_switch_latch = true;
  }
  else if (enc_switch_in == false) {
    enc_switch_latch = false;
  }


  if ((millis() >= enc_switch_timer + DOUBLE_CLICK_TIME) && (enc_switch_in == false)) {  //Reset Count when no Button Pressed
    enc_switch_counter = 0;
  }




  if ((enc_switch_in == true) && (enc_switch_counter == 1)) {
    enc_switch = 1;
  }

  else if ((enc_switch_in == true) && (enc_switch_counter >= 2)) {
    enc_switch = 2;
  }

  else if ((enc_switch_counter == 0) && (enc_switch_in == false)) {
    enc_switch = 0;
  }

  
  
  
Serial.println(enc_switch_latch);

  
 old_CV_IN = CV_IN;


 if (enc_switch == 0) {
 newPosition1 = myEnc.read();
 if ( (newPosition1 - 3) / 4  > oldPosition1 / 4) {
   oldPosition1 = newPosition1;
   oldPosition2 = newPosition1;
   oldPosition3 = newPosition1;
   scale_enc = scale_enc - 1;
 }

 else if ( (newPosition1 + 3) / 4  < oldPosition1 / 4 ) {
   oldPosition1 = newPosition1;
   oldPosition2 = newPosition1;
   oldPosition3 = newPosition1;
   scale_enc = scale_enc + 1;
 }

 if ( scale_enc < 0) {
   scale_enc = 6;
 }
 else if ( scale_enc >= 7 ) {
   scale_enc = 0;
 }

scale = scale_enc + scale_CV;
      if (scale >= 7) {
        scale = scale - 7;
      }


 }



 else if (enc_switch == 1) {

  newPosition2 = myEnc.read();
 if ( (newPosition2 - 3) / 4  > oldPosition2 / 4) { 
   oldPosition2 = newPosition2;
   oldPosition1 = newPosition2;
   oldPosition3 = newPosition2;
   rotate_enc = rotate_enc - 1;
 }

 else if ( (newPosition2 + 3) / 4  < oldPosition2 / 4 ) {
   oldPosition2 = newPosition2;
   oldPosition1 = newPosition2;
   oldPosition3 = newPosition2;
   rotate_enc = rotate_enc + 1;
 }

 if ( rotate_enc < 0) {
   rotate_enc = 11;
 }
 else if ( rotate_enc >= 12 ) {
   rotate_enc = 0;
 }
 }

       rotate = rotate_enc + rotate_CV;
      if (rotate >= 12) {
        rotate = rotate - 12;
      }





  else if (enc_switch == 2) {

  newPosition3 = myEnc.read();
 if ( (newPosition3 - 3) / 4  > oldPosition3 / 4) {
   oldPosition3 = newPosition3;
   oldPosition1 = newPosition3;
   oldPosition2 = newPosition3;
   control_mode = control_mode - 1;
 }

 else if ( (newPosition3 + 3) / 4  < oldPosition3 / 4 ) {
   oldPosition3 = newPosition3;
   oldPosition1 = newPosition3;
   oldPosition2 = newPosition3;
   control_mode = control_mode + 1;
 }

 if ( control_mode < 0) {
   control_mode = 6;
 }
 else if ( control_mode >= 7 ) {
   control_mode = 0;
 }
 
 }



 
 

 //-------------------LED----------------------

if (enc_switch == 0) {
 
 switch (scale) {
   case 0://紫
     LED(255, 0, 0);
     break;

   case 1://青
     LED(255, 127, 0);
     break;

   case 2://水色
     LED(0, 255, 0);
     break;

   case 3://緑
     LED(0, 255, 255);
     break;

   case 4://黄色
     LED(0, 0, 255);
     break;

   case 5://赤
     LED(255, 0, 255);
     break;

   case 6://白
     LED(255, 255, 255);
     break;
 }
}

else if (enc_switch == 1) {
  
  switch (rotate) {
   case 0:
     LED(255, 0, 0);
     break;

   case 1:
     LED(255, 127, 0);
     break;

   case 2:
     LED(255, 255, 0);
     break;

   case 3:
     LED(127, 255, 0);
     break;

   case 4:
     LED(0, 255, 0);
     break;

   case 5:
     LED(0, 255, 127);
     break;

   case 6:
     LED(0, 255, 255);
     break;

   case 7:
     LED(0, 127, 255);
     break;

   case 8:
     LED(0, 0, 255);
     break;

   case 9:
     LED(127, 0, 255);
     break;

   case 10:
     LED(255, 0, 255);
     break;

   case 11:
     LED(255, 0, 127);
     break;
 }
}




else if (enc_switch == 2) {
  
  switch (control_mode) {
   case 0://
     LED(255, 0, 0);
     break;

   case 1://
     LED(255, 127, 0);
     break;

   case 2://
     LED(0, 255, 0);
     break;

   case 3://
     LED(0, 255, 255);
     break;

   case 4://
     LED(0, 0, 255);
     break;

   case 5://
     LED(255, 0, 255);
     break;

   case 6://
     LED(255, 255, 255);
     break;
 }
}





 //--------------slide--------------------------------------
 toggle_switch = digitalRead(7);
 slide_CV = analogRead(0);
 control = analogRead(3);
 slide_time = pow(slide_CV / 50, 2) + 1;

switch (control_mode) {

  
  case 0:   //CV controlling Slide ON/OFF
   if (toggle_switch == 0 ) {
   
    if (control > 255) {
     slide = 1;
    }
    
    else {
     slide = 0;
    }   
   }
 
   else if (toggle_switch == 1 ) {
    slide = 1;
   }
  break;





  case 1:   //CV controlling Slide Time
    
    if (toggle_switch == 0 ) {
     slide = 1;
     slide_CV = slide_CV + control;
     slide_time = pow(slide_CV / 50, 2) + 1;
    }
 
    else if (toggle_switch == 1 ) {
     slide = 1;
    } 
  break;





  case 2:   //CV controlling Scales
    if (toggle_switch == 0 ) {
      scale_CV = map(control,0,1023,0,7);
      slide = 1;
    }
 
    else if (toggle_switch == 1 ) {
      slide = 1;
      scale_CV = 0;
    } 
  break;





  case 3:   //CV controlling Rotation (C to B)
    if (toggle_switch == 0 ) {
        rotate_CV = map(control,0,1023,0,12);
      slide = 1;
    }
 
    else if (toggle_switch == 1 ) {
      slide = 1;
      rotate_CV=0;
    } 
  break;





  case 4:   //CV transposing in Semitones
    if (toggle_switch == 0 ) {
      CV_transpose = 17*map(control,0,1023,0,60);
      slide = 1;
    }
 
    else if (toggle_switch == 1 ) {
      CV_transpose = 0;
      slide = 1;
    } 
  break;





  case 5:   //CV transposing in Fifths (7 Semitones)
    if (toggle_switch == 0 ) {
      CV_transpose = 119*map(control,0,1023,0,8);
      slide = 1;
    }
 
    else if (toggle_switch == 1 ) {
      CV_transpose = 0;
      slide = 1;
    } 
  break;



  
  case 6:   //CV transposing in Octaves (12 Semitones) 
    if (toggle_switch == 0 ) {
      CV_transpose = 204*map(control,0,1023,0,5);
      slide = 1;
    }
 
    else if (toggle_switch == 1 ) {
      CV_transpose = 0;
      slide = 1;
    } 
  break;


 
}



 

 //----------------CV--------------------------------------
 CV_IN = analogRead(7)+CV_transpose;

 if ( abs(old_CV_IN - CV_IN ) > 10 ) {//ノ

   j = 0;//slide reset

   for ( i = 0; i <= 61 ; i++ ) {
     switch (scale) {





       case 0://0=chromatic
         if ( CV_IN >= (pgm_read_word(&(CVIN_th_chr[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_chr[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_chr[CV_INh])));
           goto DAC_done;
         }
         break;











       case 1://1=major
        switch (rotate) {
          
          case 0:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_C_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_C_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_C_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 1:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_CS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_CS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_CS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 2:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_D_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_D_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_D_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 3:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_DS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_DS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_DS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 4:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_E_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_E_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_E_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 5:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_F_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_F_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_F_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 6:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_FS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_FS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_FS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 7:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_G_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_G_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_G_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 8:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_GS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_GS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_GS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 9:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_A_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_A_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_A_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 10:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_AS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_AS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_AS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 11:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_B_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_B_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_B_maj[CV_INh])));
           goto DAC_done;
           }
          break;
        }
         
         break;










       case 2://2=major_pentatonic
        switch (rotate) {
          
          case 0:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_C_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_C_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_C_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 1:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_CS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_CS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_CS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 2:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_D_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_D_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_D_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 3:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_DS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_DS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_DS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 4:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_E_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_E_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_E_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 5:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_F_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_F_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_F_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 6:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_FS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_FS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_FS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 7:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_G_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_G_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_G_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 8:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_GS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_GS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_GS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 9:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_A_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_A_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_A_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 10:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_AS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_AS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_AS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 11:
            if ( CV_IN >= (pgm_read_word(&(CVIN_th_B_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_B_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_B_mp[CV_INh])));
           goto DAC_done;
           }
          break;
        }
         
         break;






       case 3://3=major_pentatonic+7

        switch (rotate) {
          case 0:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_C_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_C_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_C_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 1:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_CS_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_CS_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_CS_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 2:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_D_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_D_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_D_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 3:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_DS_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_DS_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_DS_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 4:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_E_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_E_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_E_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 5:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_F_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_F_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_F_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 6:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_FS_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_FS_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_FS_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 7:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_G_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_G_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_G_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 8:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_GS_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_GS_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_GS_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 9:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_A_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_A_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_A_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 10:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_AS_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_AS_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_AS_mp7[CV_INh])));
           goto DAC_done;
          }
          break;

          case 11:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_B_mp7[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_B_mp7[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_B_mp7[CV_INh])));
           goto DAC_done;
          }
          break;
        }
         
         break;






       case 4://4=natural minor

        switch (rotate) {
          case 0:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_DS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_DS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_DS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 1:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_E_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_E_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_E_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 2:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_F_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_F_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_F_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 3:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_FS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_FS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_FS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 4:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_G_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_G_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_G_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 5:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_GS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_GS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_GS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 6:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_A_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_A_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_A_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 7:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_AS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_AS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_AS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 8:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_B_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_B_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_B_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 9:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_C_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_C_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_C_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 10:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_CS_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_CS_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_CS_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          case 11:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_D_maj[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_D_maj[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_D_maj[CV_INh])));
           goto DAC_done;
           }
          break;

          
          
        }
        
         
         break;






       case 5://5=minor_pentatonic

        switch (rotate) {
          case 0:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_DS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_DS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_DS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 1:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_E_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_E_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_E_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 2:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_F_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_F_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_F_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 3:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_FS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_FS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_FS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 4:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_G_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_G_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_G_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 5:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_GS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_GS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_GS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 6:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_A_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_A_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_A_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 7:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_AS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_AS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_AS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 8:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_B_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_B_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_B_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 9:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_C_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_C_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_C_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 10:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_CS_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_CS_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_CS_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          case 11:
          if ( CV_IN >= (pgm_read_word(&(CVIN_th_D_mp[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_D_mp[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_D_mp[CV_INh])));
           goto DAC_done;
           }
          break;

          
        }
        
        
         break;







       case 6://6=octave
        switch (rotate) {
          case 0:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_C_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_C_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_C_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 1:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_CS_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_CS_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_CS_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 2:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_D_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_D_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_D_oct[CV_INh])));
           goto DAC_done;

           case 3:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_DS_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_DS_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_DS_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 4:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_E_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_E_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_E_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 5:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_F_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_F_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_F_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 6:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_FS_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_FS_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_FS_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 7:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_G_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_G_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_G_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 8:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_GS_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_GS_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_GS_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 9:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_A_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_A_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_A_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 10:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_AS_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_AS_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_AS_oct[CV_INh])));
           goto DAC_done;
           }
          break;

          case 11:
           if ( CV_IN >= (pgm_read_word(&(CVIN_th_B_oct[i]))) && CV_IN < (pgm_read_word(&(CVIN_th_B_oct[i + 1])))) {
           CV_INh = i;
           DAC(pgm_read_word(&(DAC_LSB_B_oct[CV_INh])));
           goto DAC_done;
           }
          break;
          
           }
          break;
        }
         
         break;


         

     }
   }
 }
DAC_done: ;


}


void DAC(long CV_OUT) { //CV_12bit_0-4095
 digitalWrite(5, HIGH);//gateON

 //-----------slide OFFCV------------------
 if ( slide == 0 || slide_time <= 3) {
   Wire.beginTransmission(0x60);
   Wire.write((CV_OUT >> 8) & 0x0F);
   Wire.write(CV_OUT);
   Wire.endTransmission();
   delay(5);
   digitalWrite(5, LOW);

 }

 //-----------slide ONCV------------------
 else if ( slide == 1 && slide_time > 3 ) {

   if ( old_CV_OUT <= CV_OUT) {
     while ( j <= slide_time) {
       Wire.beginTransmission(0x60);
       Wire.write((old_CV_OUT + (CV_OUT - old_CV_OUT) * j / slide_time >> 8) & 0x0F);
       Wire.write(old_CV_OUT + (CV_OUT - old_CV_OUT) * j / slide_time);
       Wire.endTransmission();
       delay(5);
       j++;

     }
   }

   else if (old_CV_OUT > CV_OUT) {
     while ( j <= slide_time) {
       Wire.beginTransmission(0x60);
       Wire.write((old_CV_OUT - (old_CV_OUT - CV_OUT) * j / slide_time >> 8) & 0x0F);
       Wire.write(old_CV_OUT - (old_CV_OUT - CV_OUT) * j / slide_time);
       Wire.endTransmission();
       delay(5);
       j++;

     }
   }

   old_CV_OUT = CV_OUT;
 }
 digitalWrite(5, LOW) ;//gateOFF
}

void LED(byte R, byte G, byte B) {


 analogWrite(9,255-map(R,0,255,0,LED_Brightness));
 analogWrite(11,255-map(G,0,255,0,LED_Brightness));
 analogWrite(10,255-map(B,0,255,0,LED_Brightness));
}
