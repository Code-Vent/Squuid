#ifndef	_12F683
#define _12F683

#define Squuid_Get_Port_Address 0x00
#define Squuid_Get_SetBitmask 0x03
#define Squuid_Get_ResetBitmask 0x0B
#define Squuid_Get_Direction_Register 0x13
#define Squuid_Get_Analog_Select_Register 0x16
#define Squuid_Get_IOC_Register 0x19
#define Squuid_Get_ADC_Low_Byte 0x1C
#define Squuid_Get_ADC_High_Byte 0x1D

extern void Squuid_Configure_ADC_Channel(unsigned char eventID);
extern void Squuid_Configure_DAC_Channel(unsigned char eventID);
extern void Squuid_Configure_Comparator_Channel(unsigned char eventID);
extern void Squuid_Configure_Comparator_Channel_With_Output(unsigned char eventID);
extern void Squuid_Configure_IOC(unsigned char eventID);
//extern char* Squuid_Get_IOC_Register();
extern void Squuid_Do_ADC_Conversion();
//extern char Squuid_Get_ADC_Low_Byte();
//extern char Squuid_Get_ADC_High_Byte();
extern char Squuid_Get_Comparator_Output(unsigned char* value);
extern void Squuid_Set_DAC_Input(unsigned char value);
extern void Squuid_Set_Comparator_Threshold(unsigned char value);
extern void Squuid_Configure_System_Timer(unsigned char eventID);
extern void Squuid_Enable_Events(void(*event_callback)(unsigned char));

#endif
