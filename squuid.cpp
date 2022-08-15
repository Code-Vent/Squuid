#include"squuid.h"

#define Clock_kHz()

#ifndef Delay_us
#define Delay_us(x)
#endif

#ifndef EEPROM_Read
unsigned short EEPROM_Read(unsigned short add) { return 0; }
#endif

union Params
{
	char char_val;
	unsigned char uchar_val;
	unsigned short ushort_val;
	unsigned char* uchar_ptr;
	int int_val;
	unsigned int uint_val;
	unsigned int* uint_ptr;
}arg1, arg2, arg3, arg4, arg5, return0, return1;

unsigned char* srf;
unsigned long tick = 0;
unsigned short event_index = 0;
unsigned long event_ticks[2], seconds;
unsigned char tmr0_reg, tmr0_interrupt_reg, tmr0_resolution;
unsigned char tmr0_interrupt_flag_reset;



#define Squuid_Pin_To_ADC_Channel(Port,pin) (Squuid_Get_ADC_Channels_Map + 4 * Port + pin)


#define Squuid_EEPROM_Read(address) EEPROM_Read(address)

void interrupt()
{
	//DISABLE_INTERRUPT;
	if (0/*EXTERNAL_INTERRUPT*/)
	{
		//CLEAR_EXTERNAL_INTERRUPT;
		//CLEAR_GPIO_CHANGE_INTERRUPT;
		return;
	}
	else if (0/*GPIO_CHANGE_INTERRUPT*/)
	{
		//CLEAR_GPIO_CHANGE_INTERRUPT;
		//CLEAR_EXTERNAL_INTERRUPT;
	}
	//ENABLE_INTERRUPT;
}

void Squuid_Register_Value_Pair_12_() {
	srf = (unsigned char*)Squuid_EEPROM_Read(arg1.ushort_val);
	*srf = Squuid_EEPROM_Read(arg2.uchar_val);
}

void Squuid_Load_Register_12_() {
	srf = (unsigned char*)Squuid_EEPROM_Read(arg1.ushort_val);
	*srf = arg2.uchar_val;
}

void Squuid_Unload_Register_1_0() {
	srf = (unsigned char*)Squuid_EEPROM_Read(arg1.ushort_val);
	return0.uchar_val = *srf;
}

void Squuid_Register_Setmask_Pair_12_() {
	srf = (unsigned char*)Squuid_EEPROM_Read(arg1.ushort_val);
	*srf |= Squuid_EEPROM_Read(arg2.uchar_val);
}

void Squuid_Register_Resetmask_Pair_12_() {
	srf = (unsigned char*)Squuid_EEPROM_Read(arg1.ushort_val);
	*srf &= Squuid_EEPROM_Read(arg2.uchar_val);
}

void Squuid_Is_Bit_Reset_12_0() {
	srf = (unsigned char*)Squuid_EEPROM_Read(arg1.ushort_val);
	return0.ushort_val = (*srf & arg2.uchar_val) == 0;
}

/*unsigned short srfAddr, unsigned char mask*/
void Squuid_Is_Bit_Set_12_0() {
	srf = (unsigned char*)Squuid_EEPROM_Read(arg1.ushort_val);
	return0.ushort_val = (*srf & arg2.uchar_val) > 0;
}

void Squuid_Load_Sub_Register_123_() {	
	Squuid_Register_Resetmask_Pair_12_();
	arg2.uchar_val = arg3.uchar_val;
	Squuid_Register_Setmask_Pair_12_();
}

/*unsigned char Vref, unsigned char clock*/
void Squuid_Configure_ADC_45_() {
	//Justification
	//Reference Voltage
	//Clock Source
	//Interrupt if eventID != 0
	//Turn on ADC
	arg1.ushort_val = Squuid_Get_ADC_Config_Vref_Register;
	arg2.uchar_val = Squuid_Get_ADC_Config_Vref_Mask;
	arg3.uchar_val = Squuid_Get_ADC_Config_Vref_Map + arg4.uchar_val;
	Squuid_Load_Sub_Register_123_();

	arg1.ushort_val = Squuid_Get_ADC_Config_Clk_Src_Register;
	arg2.uchar_val = Squuid_Get_ADC_Config_Clk_Src_Mask;
	arg3.uchar_val = Squuid_Get_ADC_Config_Clk_Src_Map + arg5.uchar_val;
	Squuid_Load_Sub_Register_123_();

	arg1.ushort_val = Squuid_Get_ADC_Config_Justification_Bit_Register;
	arg2.uchar_val = Squuid_Get_ADC_Config_Justification_SetBitMask;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_ADC_Config_Interrupt_Enable_Register;
	arg2.uchar_val = Squuid_Get_ADC_Config_Interrupt_Enable_SetBitMask;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_ADC_ON_Register;
	arg2.uchar_val = Squuid_Get_ADC_ON_SetBitmask;
	Squuid_Register_Setmask_Pair_12_();
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Do_ADC_Conversion_45_() {
	//Select Channel
	//Start Conversion

	arg1.ushort_val = Squuid_Get_ADC_Channel_Select_Register;
	arg2.uchar_val = Squuid_Get_ADC_Channel_Select_Mask;
	arg3.uchar_val = Squuid_Pin_To_ADC_Channel(arg4.uchar_val, arg5.uchar_val);
	Squuid_Load_Sub_Register_123_();

	Delay_us(10);

	arg1.ushort_val = Squuid_Get_ADC_Start_Conversion_Register;
	arg2.uchar_val = Squuid_Get_ADC_Start_Conversion_SetBitMask;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_ADC_Start_Conversion_Register;
	arg2.uchar_val = Squuid_Get_ADC_Start_Conversion_SetBitMask;
Loop:
	Squuid_Is_Bit_Reset_12_0();
	if (return0.uchar_val)
		return;
	goto Loop;
}

/*unsigned char Vref, unsigned char mode*/
void Squuid_Configure_Comparator_45_() {
	
	arg1.ushort_val = Squuid_Get_Comparator_Vref_Register;
	arg2.uchar_val = Squuid_Get_Comparator_Vref_Mask;
	arg3.uchar_val = Squuid_Get_Comparator_Vref_Map + arg4.uchar_val;
	Squuid_Load_Sub_Register_123_();

	arg1.ushort_val = Squuid_Get_Comparator_Mode_Select_Register;
	arg2.uchar_val = Squuid_Get_Comparator_Mode_Select_Mask;
	arg3.uchar_val = Squuid_Get_Comparator_Mode_Select_Map + arg5.uchar_val;
	Squuid_Load_Sub_Register_123_();

	arg1.ushort_val = Squuid_Get_Comparator_Interrupt_Enable_Register;
	arg2.uchar_val = Squuid_Get_Comparator_Interrupt_Enable_SetBitMask;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_Comparator_ON_Register;
	arg2.uchar_val = Squuid_Get_Comparator_ON_SetBitmask;
	Squuid_Register_Setmask_Pair_12_();
}

/*unsigned char Vref*/
void Squuid_Set_Comparator_Threshold_4_() {

	arg1.ushort_val = Squuid_Get_Comparator_Vref_Register;
	arg2.uchar_val = Squuid_Get_Comparator_Vref_Mask;
	arg3.uchar_val = Squuid_Get_Comparator_Vref_Map + arg4.uchar_val;
	Squuid_Load_Sub_Register_123_();
}

/*unsigned char Vref, unsigned char mode*/
void Squuid_Configure_DAC_45_() {	

	arg1.ushort_val = Squuid_Get_DAC_Vref_Register;
	arg2.uchar_val = Squuid_Get_DAC_Vref_Mask;
	arg3.uchar_val = Squuid_Get_DAC_Vref_Map + arg4.uchar_val;
	Squuid_Load_Sub_Register_123_();

	arg1.ushort_val = Squuid_Get_DAC_Vref_Register;
	arg2.uchar_val = Squuid_Get_DAC_Vref_Mask;
	arg3.uchar_val = Squuid_Get_DAC_Vref_Map + arg5.uchar_val;
	Squuid_Load_Sub_Register_123_();
}

/*unsigned char Byte*/
void Squuid_Do_DAC_Conversion_3_() {
	arg1.ushort_val = Squuid_Get_DAC_Input_Register;
	arg2.uchar_val = arg3.uchar_val;
	Squuid_Load_Register_12_();

	arg1.ushort_val = Squuid_Get_DAC_Output_Enable_Register;
	arg2.uchar_val = Squuid_Get_DAC_Output_Enable_SetBitMask;
	Squuid_Register_Setmask_Pair_12_();
}

void Squuid_Get_Comparator_Output_0_0() {
	arg1.ushort_val = Squuid_Get_Comparator_Output_Bit_Register;
	arg2.uchar_val = Squuid_Get_Comparator_Output_Bit_Mask;
	Squuid_Is_Bit_Set_12_0();
}

void* Squuid_Get_System_Function(unsigned char sema) {
	switch (arg1.uchar_val)
	{
	case Squuid_Write_Analog_Actuator:
		Squuid_Do_DAC_Conversion_3_();
		return 0;
	case Squuid_Write_Threshold_Actuator:
		Squuid_Set_Comparator_Threshold_4_();
		return 0;
	case Squuid_Read_Threshold_Sensor:
		Squuid_Get_Comparator_Output_0_0();
		return 0;
	case Squuid_Read_Digital_Sensor:
		Squuid_Read_Digital_Pin_34_0();
		return 0;
	case Squuid_Read_Analog_Sensor:
		arg4.uchar_val = 0;
		arg5.uchar_val = 0;
		Squuid_Read_Analog_Pin_45_0();
		return 0;
	case Squuid_Active_High:
		Squuid_Write_Digital_Pin_High_34_();
		return 0;
	case Squuid_Active_Low:
		arg3.uchar_val = 0;
		arg4.uchar_val = 0;
		Squuid_Write_Digital_Pin_Low_34_();
		return 0;
	case Squuid_Write_Digital_Actuator_High:
		Squuid_Write_Digital_Pin_High_34_();
		return 0;
	case Squuid_Write_Digital_Actuator_Low:
		Squuid_Write_Digital_Pin_Low_34_();
		return 0;
	case 9:
		Squuid_Timer_Tick_0_();
		return 0;
	default:
		return 0;
	}
}

/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Analog_Output_Pin_34_() {

	arg1.ushort_val = Squuid_Get_Direction_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_ResetBitmask + arg4.uchar_val;
	Squuid_Register_Resetmask_Pair_12_();
	
	arg1.ushort_val = Squuid_Get_Analog_Select_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg4.uchar_val = 0;
	arg5.uchar_val = 0;
	Squuid_Configure_DAC_45_();
}

/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Analog_Input_Pin_34_() {

	arg1.ushort_val = Squuid_Get_Direction_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_Analog_Select_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg4.uchar_val = 0;
	arg5.uchar_val = 7;
	Squuid_Configure_ADC_45_();
}

/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Threshold_Input_Pin_34_() {

	arg1.ushort_val = Squuid_Get_Direction_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_Analog_Select_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg4.uchar_val = 0;
	arg5.uchar_val = 0;
	Squuid_Configure_Comparator_45_();
}


/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Threshold_Output_Pin_34_() {

	arg1.ushort_val = Squuid_Get_Direction_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_ResetBitmask + arg4.uchar_val;
	Squuid_Register_Resetmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_Analog_Select_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg4.uchar_val = 0;
	arg5.uchar_val = 1;
	Squuid_Configure_Comparator_45_();
}

/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Digital_Input_Pin_34_() {

	arg1.ushort_val = Squuid_Get_Direction_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_Analog_Select_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_ResetBitmask + arg4.uchar_val;
	Squuid_Register_Resetmask_Pair_12_();
}

/*unsigned char Port, unsigned char pin*/
void Squuid_Make_Digital_Input_Pin_With_IOC_34_() {

	arg1.ushort_val = Squuid_Get_Direction_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_Analog_Select_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_ResetBitmask + arg4.uchar_val;
	Squuid_Register_Resetmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_IOC_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();
}


/**
unsigned char Port, unsigned char pin
*/
void Squuid_Make_Digital_Output_Pin_34_() {

	arg1.ushort_val = Squuid_Get_Direction_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_ResetBitmask + arg4.uchar_val;
	Squuid_Register_Resetmask_Pair_12_();

	arg1.ushort_val = Squuid_Get_Analog_Select_Register + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_ResetBitmask + arg4.uchar_val;
	Squuid_Register_Resetmask_Pair_12_();
}

void Squuid_Start_Timer_0_() {

	arg1.ushort_val = Squuid_Get_TMR0_Resolution_Register;
	arg2.uchar_val = Squuid_Get_TMR0_Resolution;
	Squuid_Load_Register_12_();

	arg1.ushort_val = Squuid_Get_TMR0_Interrupt_Register;
	arg2.uchar_val = Squuid_Get_TMR0_Interrupt_Enable_SetBitMask;
	Squuid_Register_Setmask_Pair_12_();
}

void Squuid_Stop_Timer_0_() {

	arg1.ushort_val = Squuid_Get_TMR0_Interrupt_Register;
	arg2.uchar_val = Squuid_Get_TMR0_Interrupt_Enable_ResetBitMask;
	Squuid_Register_Setmask_Pair_12_();
	tick = 0;
}

void Squuid_Timer_Tick_0_() {

	*(unsigned char*)tmr0_reg = tmr0_resolution;
	*(unsigned char*)tmr0_interrupt_reg = *(unsigned char*)tmr0_interrupt_reg & tmr0_interrupt_flag_reset;

	++tick;
}

void Squuid_Pause_Timer_0_() {

	arg1.ushort_val = Squuid_Get_TMR0_Interrupt_Register;
	arg2.uchar_val = Squuid_Get_TMR0_Interrupt_Enable_ResetBitMask;
	Squuid_Register_Setmask_Pair_12_();
}

void Squuid_Configure_System_Timer_0_() {

	arg1.ushort_val = Squuid_Get_TMR0_Config_Register;
	arg2.uchar_val = Squuid_Get_TMR0_Config;
	Squuid_Load_Register_12_();

	arg1.ushort_val = Squuid_Get_TMR0_Resolution_Register;
	Squuid_Unload_Register_1_0();
	tmr0_reg = return0.uchar_val;

	arg1.ushort_val = Squuid_Get_TMR0_Resolution;
	Squuid_Unload_Register_1_0();
	tmr0_resolution = return0.uchar_val;

	arg1.ushort_val = Squuid_Get_TMR0_Interrupt_Register;
	Squuid_Unload_Register_1_0();
	tmr0_interrupt_reg = return0.uchar_val;

	arg1.ushort_val = Squuid_Get_TMR0_Interrupt_Flag_ResetBitMask;
	Squuid_Unload_Register_1_0();
	tmr0_interrupt_flag_reset = return0.uchar_val;
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Write_Digital_Pin_Low_34_() {

	arg1.ushort_val = Squuid_Get_Port_Address + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_ResetBitmask + arg4.uchar_val;
	Squuid_Register_Resetmask_Pair_12_();
}


/**
unsigned char Port, unsigned char pin
*/
void Squuid_Write_Digital_Pin_High_34_() {

	arg1.ushort_val = Squuid_Get_Port_Address + arg3.uchar_val;
	arg2.uchar_val = Squuid_Get_SetBitmask + arg4.uchar_val;
	Squuid_Register_Setmask_Pair_12_();
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Digital_Pin_34_0() {

	arg1.ushort_val = Squuid_Get_Port_Address + arg3.uchar_val;
	Squuid_Unload_Register_1_0();
	return0.uchar_val = (return0.uchar_val >> arg4.uchar_val) & 0b00000001;
}




/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Analog_Pin_45_0() {

	Squuid_Do_ADC_Conversion_45_();
	*return0.uint_ptr = Squuid_EEPROM_Read(Squuid_Get_ADC_High_Byte);
	*return0.uint_ptr = (*return0.uint_ptr << 8) | Squuid_EEPROM_Read(Squuid_Get_ADC_Low_Byte);
}


/**
unsigned char Port, unsigned char pin0
*/
void Squuid_Write_Port_12_() {

	arg1.uchar_val += Squuid_Get_Port_Address;
	Squuid_Load_Register_12_();
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Port_1_0() {

	arg1.uchar_val += Squuid_Get_Port_Address;
	Squuid_Unload_Register_1_0();
}

void Squuid_Event_0_() {
	event_ticks[event_index++ % 2] = tick;
}

void Squuid_Time_Between_Last_Events_0_0() {
	return0.uint_val = event_ticks[0] - event_ticks[1];
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Reset_OneWire_Comm_34_0() {
	Squuid_Make_Digital_Output_Pin_34_();
	Squuid_Write_Digital_Pin_Low_34_();
	Delay_us(480);
	Squuid_Write_Digital_Pin_High_34_();
	Delay_us(50);
	Squuid_Make_Digital_Input_Pin_34_();
	Delay_us(20);
	Squuid_Read_Digital_Pin_34_0();
	Delay_us(200);
	Squuid_Make_Digital_Output_Pin_34_();
	Squuid_Write_Digital_Pin_High_34_();
	Delay_us(210);
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Write_One_OneWire_Comm_34_() {
	Squuid_Make_Digital_Output_Pin_34_();
	Squuid_Write_Digital_Pin_Low_34_();
	Delay_us(6);
	Squuid_Write_Digital_Pin_High_34_();
	Delay_us(54);
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Write_Zero_OneWire_Comm_34_() {
	Squuid_Make_Digital_Output_Pin_34_();
	Squuid_Write_Digital_Pin_Low_34_();
	Delay_us(60);
	Squuid_Write_Digital_Pin_High_34_();
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_OneWire_Comm_34_0() {
	Squuid_Make_Digital_Output_Pin_34_();
	Squuid_Write_Digital_Pin_Low_34_();
	Delay_us(6);
	Squuid_Write_Digital_Pin_High_34_();
	Delay_us(10);
	Squuid_Make_Digital_Input_Pin_34_();
	Delay_us(10);
	Squuid_Read_Digital_Pin_34_0();
	Delay_us(45);
	Squuid_Make_Digital_Output_Pin_34_();
	Squuid_Write_Digital_Pin_High_34_();
}

/**
unsigned char Port, unsigned char pin
*/
void Squuid_Read_Byte_OneWire_Comm_34_1() {
	return1.uchar_val = 0x00;
	Squuid_Read_OneWire_Comm_34_0();
	if (return0.uchar_val)
		return1.uchar_val |= 0x01;
	if (return0.uchar_val)
		return1.uchar_val |= 0x02;
	if (return0.uchar_val)
		return1.uchar_val |= 0x04;
	if (return0.uchar_val)
		return1.uchar_val |= 0x08;
	if (return0.uchar_val)
		return1.uchar_val |= 0x10;
	if (return0.uchar_val)
		return1.uchar_val |= 0x20;
	if (return0.uchar_val)
		return1.uchar_val |= 0x40;
	if (return0.uchar_val)
		return1.uchar_val |= 0x80;
}

/**
unsigned char byte, unsigned char Port, unsigned char pin
*/
void Squuid_Write_Byte_OneWire_Comm_234_() {
	(arg2.uchar_val & 0x01) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
	(arg2.uchar_val & 0x02) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
	(arg2.uchar_val & 0x04) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
	(arg2.uchar_val & 0x08) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
	(arg2.uchar_val & 0x10) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
	(arg2.uchar_val & 0x20) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
	(arg2.uchar_val & 0x40) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
	(arg2.uchar_val & 0x80) ? Squuid_Write_One_OneWire_Comm_34_() :
		Squuid_Write_Zero_OneWire_Comm_34_();
}

//GP3 (input pin) is the com receiver
//GP5 (output pin) is the com transmitter
//GP4 (input pin) interrupt on change calls Squuid_System_Call() -> exclusive to squuid com
//GP2 (output pin) Ready for com pin

void main() {
	int i = Squuid_ram[0];
	arg3.uchar_val = 0;
	arg4.uchar_val = 0;
	Squuid_Make_Digital_Input_Pin_With_IOC_34_();
	arg3.uchar_val = 0;
	arg4.uchar_val = 2;
	Squuid_Make_Digital_Output_Pin_34_();
	arg3.uchar_val = 0;
	arg4.uchar_val = 3;
	Squuid_Make_Digital_Input_Pin_34_();
	arg3.uchar_val = 0;
	arg4.uchar_val = 5;
	Squuid_Make_Digital_Output_Pin_34_();

	arg3.uchar_val = 0;
	arg4.uchar_val = 2;
	Squuid_Make_Analog_Output_Pin_34_();
	arg3.uchar_val = 0;
	arg4.uchar_val = 3;
	Squuid_Make_Analog_Input_Pin_34_();
	arg3.uchar_val = 0;
	arg4.uchar_val = 5;
	Squuid_Make_Analog_Output_Pin_34_();
	
	while (1)
	{
		//Run Program
		Squuid_Event_0_();
		Squuid_Get_System_Function(++i % 10);
		Squuid_Program_Loop();
	}
}