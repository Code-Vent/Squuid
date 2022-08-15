
#ifndef SQUUID_H
#define SQUUID_H

static char Squuid_ram[25];


#define Squuid_Get_Port_Address 0x00
#define Squuid_Get_SetBitmask 0x03
#define Squuid_Get_ResetBitmask 0x0B
#define Squuid_Get_Direction_Register 0x13
#define Squuid_Get_Analog_Select_Register 0x16
#define Squuid_Get_IOC_Register 0x19
/************ADC*****************/
#define Squuid_Get_ADC_Low_Byte 0x1C
#define Squuid_Get_ADC_High_Byte 0x1D
#define Squuid_Get_ADC_Config_Vref_Register 0x1E
#define Squuid_Get_ADC_Config_Vref_Mask 0x1E
#define Squuid_Get_ADC_Config_Vref_Map 0x1E
#define Squuid_Get_ADC_Config_Clk_Src_Register 0x1E
#define Squuid_Get_ADC_Config_Clk_Src_Mask 0x1E
#define Squuid_Get_ADC_Config_Clk_Src_Map 0x1E
#define Squuid_Get_ADC_Config_Justification_Bit_Register 0x1E
#define Squuid_Get_ADC_Config_Justification_SetBitMask 0x1E
#define Squuid_Get_ADC_Config_Interrupt_Enable_Register 0x1E
#define Squuid_Get_ADC_Config_Interrupt_Enable_SetBitMask 0x1E

#define Squuid_Get_ADC_Channel_Select_Register 0x16
#define Squuid_Get_ADC_Channel_Select_Mask 0x16
#define Squuid_Get_ADC_Channels_Map 0x16
#define Squuid_Get_ADC_ON_Register 0x20
#define Squuid_Get_ADC_ON_SetBitmask 0x20
#define Squuid_Get_ADC_Start_Conversion_Register 0x20
#define Squuid_Get_ADC_Start_Conversion_SetBitMask 0x20
/************ADC*****************/
/************Comparator*****************/
#define Squuid_Get_Comparator_ON_Register 0x20
#define Squuid_Get_Comparator_ON_SetBitmask 0x20
#define Squuid_Get_Comparator_Vref_Register 0x20
#define Squuid_Get_Comparator_Vref_Mask 0x20
#define Squuid_Get_Comparator_Vref_Map 0x20
#define Squuid_Get_Comparator_Mode_Select_Register 0x20
#define Squuid_Get_Comparator_Mode_Select_Mask 0x20
#define Squuid_Get_Comparator_Mode_Select_Map 0x20
#define Squuid_Get_Comparator_Interrupt_Enable_Register 0x1E
#define Squuid_Get_Comparator_Interrupt_Enable_SetBitMask 0x1E
#define Squuid_Get_Comparator_Output_Bit_Register 0x1E
#define Squuid_Get_Comparator_Output_Bit_Mask 0x1E
/************Comparator*****************/
/************DAC*****************/
#define Squuid_Get_DAC_ON_Register 0x20
#define Squuid_Get_DAC_ON_SetBitmask 0x20
#define Squuid_Get_DAC_Vref_Register 0x20
#define Squuid_Get_DAC_Vref_Mask 0x20
#define Squuid_Get_DAC_Vref_Map 0x20
#define Squuid_Get_DAC_Mode_Select_Register 0x20
#define Squuid_Get_DAC_Mode_Select_Mask 0x20
#define Squuid_Get_DAC_Mode_Select_Map 0x20
#define Squuid_Get_DAC_Input_Register 0x1E
#define Squuid_Get_DAC_Output_Enable_Register 0x1E
#define Squuid_Get_DAC_Output_Enable_SetBitMask 0x1E
/************DAC*****************/
/************Timer*****************/
#define Squuid_Get_TMR0_Config_Register 0x20
#define Squuid_Get_TMR0_Config		    0x20
#define Squuid_Get_TMR0_Interrupt_Register 0x20
#define Squuid_Get_TMR0_Interrupt_Enable_SetBitMask		    0x20
#define Squuid_Get_TMR0_Interrupt_Enable_ResetBitMask		    0x20
#define Squuid_Get_TMR0_Interrupt_Flag_ResetBitMask		    0x20
#define Squuid_Get_TMR0_Resolution_Register		    0x20
#define Squuid_Get_TMR0_Resolution		    0x20
/************Timer*****************/

/*unsigned char Vref, unsigned char clock*/
void Squuid_Configure_PWM_45_();
/*unsigned char Vref, unsigned char mode*/
void Squuid_Configure_Comparator_45_();
/*unsigned char Vref, unsigned char clock*/
void Squuid_Configure_ADC_45_();
/**
unsigned char Port, unsigned char pin
*/
void Squuid_Do_ADC_Conversion_45_();
/*unsigned char Vref, unsigned char mode*/
void Squuid_Configure_DAC_45_();
/*unsigned char Byte*/
void Squuid_Do_DAC_Conversion_3_();
/**/
void Squuid_Get_Comparator_Output_0_0();

/*unsigned char Vref*/
void Squuid_Set_Comparator_Threshold_4_();

/**/
void Squuid_Configure_System_Timer_0_();
/**/
void Squuid_Start_Timer_0_();
/**/
void Squuid_Pause_Timer_0_();
/**/
void Squuid_Stop_Timer_0_();
/**/
void Squuid_Timer_Tick_0_();


void Squuid_Events();


//********Implemented
/**
unsigned char Port, unsigned char pin
*/
void Squuid_Make_Digital_Output_Pin_34_();
/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Digital_Input_Pin_34_();
/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Analog_Output_Pin_34_();
/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Analog_Input_Pin_34_();
/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Threshold_Input_Pin_34_();
/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Threshold_Output_Pin_34_();
/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Digital_Input_Pin_With_IOC_34_();
/*unsigned char Port, unsigned char pin*/
void Squuid_Make_PWM_Output_Pin_34_();

/**
unsigned char Port, unsigned char pin0
*/
void Squuid_Write_Digital_Pin_High_34_();
/**
unsigned char Port, unsigned char pin
*/
void Squuid_Write_Digital_Pin_Low_34_();
/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Analog_Pin_45_0();
/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Digital_Pin_34_0();
/**
unsigned char Port, unsigned char pin0
*/
void Squuid_Write_Port_12_();
/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Port_1_0();

//Implemented********

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Reset_OneWire_Comm_34_0();

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Write_One_OneWire_Comm_34_();
/**
unsigned char Port, unsigned char pin
*/
void Squuid_Write_Zero_OneWire_Comm_34_();

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_OneWire_Comm_34_0();

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Byte_OneWire_Comm_34_1();
/**
unsigned char byte, unsigned char Port, unsigned char pin
*/
void Squuid_Write_Byte_OneWire_Comm_234_();


#define Squuid_Write_Analog_Actuator 0//Squuid_Set_DAC_Input
#define Squuid_Write_Threshold_Actuator 1//Squuid_Set_Comparator_Threshold
#define Squuid_Read_Threshold_Sensor 2//Squuid_Get_Comparator_Output
#define Squuid_Read_Digital_Sensor 3//Squuid_Read_Digital_Pin
#define Squuid_Read_Analog_Sensor 4//Squuid_Read_Analog_Pin
#define Squuid_Active_High 5//Squuid_Write_Digital_Pin_High
#define Squuid_Active_Low 6//Squuid_Write_Digital_Pin_Low
#define Squuid_Write_Digital_Actuator_High 7//Squuid_Write_Digital_Pin_High
#define Squuid_Write_Digital_Actuator_Low 8//Squuid_Write_Digital_Pin_Low


void Squuid_Event_0_();
void Squuid_Time_Between_Last_Events_0_0();
void Squuid_System_Call() {}
void Squuid_Program_Setup() {}
void Squuid_Program_Loop() {}


#endif