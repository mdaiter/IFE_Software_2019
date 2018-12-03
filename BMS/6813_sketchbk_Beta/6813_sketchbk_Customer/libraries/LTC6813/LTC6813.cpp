/*!
  LTC6813-1 Multicell Battery Monitor
@verbatim
  The LTC6813 is a 3rd generation multicell battery stack
  monitor that measures up to 18 series connected battery
  cells with a total measurement error of less than 1.2mV. 
  
  Using the LTC6813-1, multiple devices are connected in
  a daisy-chain with one host processor connection for all
  devices.
@endverbatim
REVISION HISTORY
$Revision: 2000 $
$Date: 2017-4

Copyright (c) 2017, Linear Technology Corp.(LTC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Linear Technology Corp.

The Linear Technology Linduino is not affiliated with the official Arduino team.
However, the Linduino is only possible because of the Arduino team's commitment
to the open-source community.  Please, visit http://www.arduino.cc and
http://store.arduino.cc , and consider a purchase that will help fund their
ongoing work.

Copyright 2017 Linear Technology Corp. (LTC)
***********************************************************/
//! @defgroup LTC68131 LTC6813-1: Multicell Battery Monitor

/*! @file
    @ingroup LTC68131
    Library for LTC6813-1 Multicell Battery Monitor
*/

#include "stdint.h"
#include "LTC681x.h"
#include "LTC6813.h"

//Helper function to intialize register limits.
void LTC6813_init_reg_limits(uint8_t total_ic, cell_asic *ic)
{
    for(uint8_t cic=0; cic<total_ic; cic++)
    {
        ic[cic].ic_reg.cell_channels=18; 
        ic[cic].ic_reg.stat_channels=4;
        ic[cic].ic_reg.aux_channels=9;
        ic[cic].ic_reg.num_cv_reg=6; 
        ic[cic].ic_reg.num_gpio_reg=4;    
        ic[cic].ic_reg.num_stat_reg=2;     
    } 
}

//Helper function to intialize CFG variables.
void LTC6813_init_cfg(uint8_t total_ic, cell_asic *ic)
{
   LTC681x_init_cfg(total_ic,ic);
}
//Helper function to set CFGR variable
void LTC6813_set_cfgr(uint8_t nIC, cell_asic *ic, bool refon, bool adcopt, bool gpio[5],bool dcc[12],bool dcto[4], uint16_t uv, uint16_t  ov)
{
    LTC681x_set_cfgr_refon(nIC,ic,refon);
    LTC681x_set_cfgr_adcopt(nIC,ic,adcopt);
    LTC681x_set_cfgr_gpio(nIC,ic,gpio);
    LTC681x_set_cfgr_dis(nIC,ic,dcc);
	LTC681x_set_cfgr_uv(nIC, ic, uv);
    LTC681x_set_cfgr_ov(nIC, ic, ov);
}
//Helper function to set the REFON bit
void LTC6813_set_cfgr_refon(uint8_t nIC, cell_asic *ic, bool refon) 
{
  LTC681x_set_cfgr_refon(nIC,ic,refon);
}
//Helper function to set the adcopt bit
void LTC6813_set_cfgr_adcopt(uint8_t nIC, cell_asic *ic, bool adcopt)
{
  LTC681x_set_cfgr_adcopt(nIC,ic,adcopt);
}
//Helper function to set GPIO bits
void LTC6813_set_cfgr_gpio(uint8_t nIC, cell_asic *ic,bool gpio[5])
{  
  LTC681x_set_cfgr_gpio(nIC,ic,gpio);
}
//Helper function to control discharge
void LTC6813_set_cfgr_dis(uint8_t nIC, cell_asic *ic,bool dcc[12])
{  
  LTC681x_set_cfgr_dis(nIC,ic,dcc);
}
//Helper Function to set uv value in CFG register
void LTC6813_set_cfgr_uv(uint8_t nIC, cell_asic *ic,uint16_t uv)
{
    LTC681x_set_cfgr_uv(nIC, ic, uv);
}
//helper function to set OV value in CFG register
void LTC6813_set_cfgr_ov(uint8_t nIC, cell_asic *ic,uint16_t ov)
{
    LTC681x_set_cfgr_ov( nIC, ic, ov);
}
/*! Helper Function to initialize the CFGRB data structures*/
void LTC6813_init_cfgb(uint8_t total_ic,cell_asic *ic)
{
	for (uint8_t current_ic = 0; current_ic<total_ic;current_ic++)
    {
		for(int j =0; j<6;j++)
        {
            ic[current_ic].configb.tx_data[j] = 0;
        }  
    }
}

/* Helper Function to set the configuration register B */
void LTC6813_set_cfgrb(uint8_t nIC, cell_asic *ic,bool fdrf,bool dtmen,bool ps[2],bool gpiobits[4],bool dccbits[7])
{
    LTC6813_set_cfgrb_fdrf(nIC,ic,fdrf);
    LTC6813_set_cfgrb_dtmen(nIC,ic,dtmen);
    LTC6813_set_cfgrb_ps(nIC,ic,ps);
    LTC6813_set_cfgrb_gpio_b(nIC,ic,gpiobits);
	LTC6813_set_cfgrb_dcc_b(nIC,ic,dccbits);
}

//Helper function to set the FDRF bit
void LTC6813_set_cfgrb_fdrf(uint8_t nIC, cell_asic *ic, bool fdrf) 
{
  if(fdrf) ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]|0x40;
  else ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]&0xBF;
}

//Helper function to set the DTMEN bit
void LTC6813_set_cfgrb_dtmen(uint8_t nIC, cell_asic *ic, bool dtmen) 
{
  if(dtmen) ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]|0x08;
  else ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]&0xF7;
}
	
//Helper function to set the PATH SELECT bit
void LTC6813_set_cfgrb_ps(uint8_t nIC, cell_asic *ic, bool ps[]) 
{
  for(int i =0;i<2;i++)
  {
      if(ps[i])ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]|(0x01<<(i+4));
      else ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]&(~(0x01<<(i+4)));
  }
}
// Helper function to set the gpio bits in configb b register
void LTC6813_set_cfgrb_gpio_b(uint8_t nIC, cell_asic *ic, bool gpiobits[]) 
{
	for(int i =0;i<4;i++)
  {
      if(gpiobits[i])ic[nIC].configb.tx_data[0] = ic[nIC].configb.tx_data[0]|(0x01<<i);
      else ic[nIC].configb.tx_data[0] = ic[nIC].configb.tx_data[0]&(~(0x01<<i));
  }
}
// Helper function to set the dcc bits in configb b register
void LTC6813_set_cfgrb_dcc_b(uint8_t nIC, cell_asic *ic, bool dccbits[]) 
{
	for(int i =0;i<7;i++)
	{ 
		if(i==0)
		{
			if(dccbits[i])ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]|0x04;
			else ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]&0xFB;
		}
		if(i>0 and i<5)
		{	
			if(dccbits[i])ic[nIC].configb.tx_data[0] = ic[nIC].configb.tx_data[0]|(0x01<<(i+3));
			else ic[nIC].configb.tx_data[0] = ic[nIC].configb.tx_data[0]&(~(0x01<<(i+3)));
		}
		if(i>4 and i<7)
		{
			if(dccbits[i])ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]|(0x01<<(i-5));
			else ic[nIC].configb.tx_data[1] = ic[nIC].configb.tx_data[1]&(~(0x01<<(i-5)));	
		}
	}
}
 /*
   This command will write the configuration registers of the LTC6813-1s
   connected in a daisy chain stack. The configuration is written in descending
   order so the last device's configuration is written first.
  */
  void LTC6813_wrcfg(uint8_t total_ic, //The number of ICs being written to
                     cell_asic *ic //A two dimensional array of the configuration data that will be written
                    )
  {
    LTC681x_wrcfg(total_ic,ic);
  }


/*
   This command will write the configuration b registers of the LTC6813-1s
   connected in a daisy chain stack. The configuration is written in descending
   order so the last device's configuration is written first.
  */
void LTC6813_wrcfgb(uint8_t total_ic, //The number of ICs being written to
                    cell_asic *ic //A two dimensional array of the configuration data that will be written
                   )
{
    LTC681x_wrcfgb(total_ic,ic);
}

  /*
  Reads configuration registers of a LTC6813 daisy chain
  */
  int8_t LTC6813_rdcfg(uint8_t total_ic, //Number of ICs in the system
                       cell_asic *ic //A two dimensional array that the function stores the read configuration data.
                      )
  {
    int8_t pec_error = 0;
    pec_error = LTC681x_rdcfg(total_ic,ic);
    return(pec_error);
  }
 /*
  Reads configuration b registers of a LTC6813 daisy chain
  */
int8_t LTC6813_rdcfgb(uint8_t total_ic, //Number of ICs in the system
                   cell_asic *ic //A two dimensional array that the function stores the read configuration data.
                  )
{
    int8_t pec_error = 0;
    pec_error = LTC681x_rdcfgb(total_ic,ic);
    return(pec_error);
}

/*
Starts cell voltage conversion
*/
void LTC6813_adcv(uint8_t MD, //ADC Mode
				  uint8_t DCP, //Discharge Permit
				  uint8_t CH //Cell Channels to be measured
				 )
{
    LTC681x_adcv(MD,DCP,CH);
}
// Reads and parses the LTC6813 cell voltage registers.
uint8_t LTC6813_rdcv(uint8_t reg, // Controls which cell voltage register is read back.
                     uint8_t total_ic, // the number of ICs in the system
                     cell_asic *ic // Array of the parsed cell codes
                    )
{
	int8_t pec_error = 0;
	pec_error = LTC681x_rdcv(reg,total_ic,ic);
	return(pec_error);
}
//Start a GPIO and Vref2 Conversion
void LTC6813_adax(uint8_t MD, //ADC Mode
				  uint8_t CHG //GPIO Channels to be measured)
                 ) 
{
	LTC681x_adax(MD,CHG);
}
/*
The function is used
to read the  parsed GPIO codes of the LTC6813. This function will send the requested
read commands parse the data and store the gpio voltages in aux_codes variable
*/
int8_t LTC6813_rdaux(uint8_t reg, //Determines which GPIO voltage register is read back.
				     uint8_t total_ic,//the number of ICs in the system
				     cell_asic *ic//A two dimensional array of the gpio voltage codes.
				    )
{
	int8_t pec_error = 0;
	LTC681x_rdaux(reg,total_ic,ic);
	return (pec_error);
}
//Start a Status ADC Conversion
void LTC6813_adstat(uint8_t MD, //ADC Mode
					uint8_t CHST //GPIO Channels to be measured
)
{
	LTC681x_adstat(MD,CHST);
} 
/*
Reads and parses the LTC6813 stat registers.
The function is used
to read the  parsed stat codes of the LTC6813. This function will send the requested
read commands parse the data and store the stat voltages in stat_codes variable
*/
int8_t LTC6813_rdstat(uint8_t reg, //Determines which Stat  register is read back.
                      uint8_t total_ic,//the number of ICs in the system
                      cell_asic *ic
                       )
{
    int8_t pec_error = 0;
    pec_error = LTC681x_rdstat(reg,total_ic,ic);
    return (pec_error);
} 
// Starts cell voltage  and GPIO 1&2 conversion
void LTC6813_adcvax(uint8_t MD, //ADC Mode
					uint8_t DCP //Discharge Permit
					)
{
    LTC681x_adcvax(MD,DCP);
}  
//Starts cell voltage and SOC conversion
void LTC6813_adcvsc( uint8_t MD, //ADC Mode
                     uint8_t DCP //Discharge Permit
                   )
{
    LTC681x_adcvsc(MD,DCP);
}
//Starts the Mux Decoder diagnostic self test
void LTC6813_diagn()
{
     LTC681x_diagn();
}
//Starts cell voltage self test conversion
void LTC6813_cvst(uint8_t MD, //ADC Mode
                  uint8_t ST //Self Test
                 )
{
    LTC681x_cvst(MD,ST);
}

//Start an Auxiliary Register Self Test Conversion
void LTC6813_axst(uint8_t MD, //ADC Mode
				  uint8_t ST //Self Test
                 )
{
	LTC681x_axst(MD,ST);
}

//Start a Status Register Self Test Conversion
void LTC6813_statst(uint8_t MD, //ADC Mode
                    uint8_t ST //Self Test
)
{
    LTC681x_statst(MD,ST);
}
// Runs the Digital Filter Self Test
int16_t LTC6813_run_cell_adc_st(uint8_t adc_reg,uint8_t total_ic, cell_asic *ic,uint8_t md,bool adcopt)
{
	int16_t error = 0;
	error = LTC681x_run_cell_adc_st(adc_reg,total_ic,ic,md,adcopt);
	return(error);
}

//Starts cell voltage overlap conversion
void LTC6813_adol(uint8_t MD, //ADC Mode
                  uint8_t DCP //Discharge Permit
                 )
{
  LTC681x_adol(MD,DCP);
}
// Runs the ADC overlap test for the IC
uint16_t LTC6813_run_adc_overlap(uint8_t total_ic, cell_asic *ic)
{
	uint16_t error = 0;
	int32_t measure_delta =0;
	int16_t failure_pos_limit = 20;
	int16_t failure_neg_limit = -20;
	int32_t a, b;
	uint32_t conv_time=0;  
	wakeup_idle(total_ic);
	LTC681x_adol(MD_7KHZ_3KHZ,DCP_DISABLED);
	conv_time = LTC681x_pollAdc();
	Serial.print(F("cell conversion completed in:"));
	Serial.print(((float)conv_time/1000), 1);
	Serial.println(F("mS"));
	Serial.println();
	wakeup_idle(total_ic);
	error = LTC681x_rdcv(0, total_ic,ic);
	for (int cic = 0; cic<total_ic; cic++)
	{
		for (uint8_t i=0; i<18; i++)
	    {
			Serial.println(ic[cic].cells.c_codes[i]); 
		}

		measure_delta = (int32_t)ic[cic].cells.c_codes[6]-(int32_t)ic[cic].cells.c_codes[7]; 
		if ((measure_delta>failure_pos_limit) || (measure_delta<failure_neg_limit))
		{
		  error = error | (1<<(cic-1));
		}
		measure_delta = (int32_t)ic[cic].cells.c_codes[12]-(int32_t)ic[cic].cells.c_codes[13]; 
		if ((measure_delta>failure_pos_limit) || (measure_delta<failure_neg_limit))
		{
		  error = error | (1<<(cic-1));
		}
	}
	return(error);
}

//start GPIOs open wire adc conversion
void LTC6813_axow(uint8_t MD, //ADC Mode
				  uint8_t PUP //Discharge Permit
				 )
{
	uint8_t cmd[2];
	uint8_t md_bits;
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits + 0x10+ (PUP<<6) ;//+ CH;
	cmd_68(cmd);
}
// Start an open wire Conversion
void LTC6813_adow(uint8_t MD,uint8_t PUP,uint8_t CH,uint8_t DCP)
{
    LTC681x_adow(MD,PUP,CH,DCP);
}

//Runs the datasheet algorithm for open wire
void LTC6813_run_openwire(uint8_t total_ic, cell_asic *ic)
{
	LTC681x_run_openwire( total_ic, ic);
}

//Start an GPIO Redundancy test
void LTC6813_adaxd(uint8_t MD, //ADC Mode
				   uint8_t CHG //GPIO Channels to be measured)
                   )
{
	LTC681x_adaxd(MD,CHG);
}

// Start a Status register redundancy test Conversion
void LTC6813_adstatd(uint8_t MD, //ADC Mode
					 uint8_t CHST //GPIO Channels to be measured
                    )
{
 LTC681x_adstatd(MD,CHST);
}

//Runs the redundancy self test
int16_t LTC6813_run_adc_redundancy_st(uint8_t adc_mode, uint8_t adc_reg, uint8_t total_ic, cell_asic *ic)
{
	int16_t error = 0;
	LTC681x_run_adc_redundancy_st(adc_mode,adc_reg,total_ic,ic);
	return(error);
}
//Sends the poll adc command
uint8_t LTC6813_pladc()
{
	return(LTC681x_pladc());
}

//This function will block operation until the ADC has finished it's conversion
uint32_t LTC6813_pollAdc()
{
	return(LTC681x_pollAdc());
}

/*
The command clears the cell voltage registers and intiallizes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void LTC6813_clrcell()
{
	LTC681x_clrcell();
}

/*
The command clears the Auxiliary registers and initializes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void LTC6813_clraux()
{
	LTC681x_clraux();
}

/*
The command clears the Stat registers and intiallizes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void LTC6813_clrstat()
{
	LTC681x_clrstat();
}
/* Writes the pwm registers of a LTC6813 daisy chain */
void LTC6813_wrpwm(uint8_t total_ic,
				   uint8_t pwmReg,  //The number of ICs being written to
				   cell_asic *ic //A two dimensional array of the configuration data that will be written
				  )
{
	LTC681x_wrpwm(total_ic,pwmReg,ic);
}
/*  Reads pwm registers of a LTC6813 daisy chain */
int8_t LTC6813_rdpwm(uint8_t total_ic, //Number of ICs in the system
					 uint8_t pwmReg,
				     cell_asic *ic //A two dimensional array that the function stores the read configuration data.
				    )
{
	int8_t pec_error =0;
	pec_error = LTC681x_rdpwm(total_ic,pwmReg,ic);
	return(pec_error);
}
//Writes data in S control register the ltc6813-1  connected in a daisy chain stack. 
void LTC6813_wrsctrl(uint8_t total_ic, //!< number of ICs in the daisy chain
                     uint8_t sctrl_reg,
                     cell_asic *ic
                    )
{
	LTC681x_wrsctrl(total_ic, sctrl_reg, ic);
}
// Reads sctrl registers of a ltc6812 daisy chain   

int8_t LTC6813_rdsctrl(uint8_t total_ic, //!< number of ICs in the daisy chain
                       uint8_t sctrl_reg,
                       cell_asic *ic //!< a two dimensional array that the function stores the read pwm data
                      )
{
	LTC681x_rdsctrl( total_ic, sctrl_reg,ic );
}

/* Start Sctrl data communication        
This command will start the sctrl pulse communication over the spins
*/
void LTC6813_stsctrl()
{
	LTC681x_stsctrl();
}
/*
The command clears the Sctrl registers and initializes
all values to 0. The register will read back hexadecimal 0x00
after the command is sent.
*/
void LTC6813_clrsctrl()
{
	LTC681x_clrsctrl();
}

/* Writes the COMM registers of a LTC6813 daisy chain */
void LTC6813_wrcomm(uint8_t total_ic, //The number of ICs being written to
				    cell_asic *ic //A two dimensional array of the comm data that will be written
				   )
{
	LTC681x_wrcomm(total_ic,ic);
}
/* Reads COMM registers of a LTC6813 daisy chain */
int8_t LTC6813_rdcomm(uint8_t total_ic, //Number of ICs in the system
					  cell_asic *ic //A two dimensional array that the function stores the read configuration data.
				     )
{
	int8_t pec_error = 0;
	LTC681x_rdcomm(total_ic, ic);
	return(pec_error);
}

/* Shifts data in COMM register out over LTC6813 SPI/I2C port */
void LTC6813_stcomm()
{
    LTC681x_stcomm();
}

void LTC6813_set_discharge(int Cell, uint8_t total_ic, cell_asic *ic)
{
  for (int i=0; i<total_ic; i++)
  {
    if (Cell==0)
	{
	  ic[i].configb.tx_data[1] = ic[i].configb.tx_data[1] |(0x40);
	}
    else if (Cell<9)
    {
      ic[i].config.tx_data[4] = ic[i].config.tx_data[4] | (1<<(Cell-1));
    }
    else if (Cell < 13)
    {
      ic[i].config.tx_data[5] = ic[i].config.tx_data[5] | (1<<(Cell-9));
    }
    else if (Cell<17)
    {
      ic[i].configb.tx_data[0] = ic[i].configb.tx_data[0] | (1<<(Cell-9));
    }
    else if (Cell<19)
    {
      ic[i].configb.tx_data[1] = ic[i].configb.tx_data[1] | (1<<(Cell-17));
    }
  }
}
void LTC6813_clear_discharge(uint8_t total_ic,
                             cell_asic *ic)
{
    LTC681x_clear_discharge(total_ic,ic);

}

//Helper function that increments PEC counters
void LTC6813_check_pec(uint8_t total_ic,uint8_t reg, cell_asic *ic)
{
	LTC681x_check_pec(total_ic,reg,ic);
}

//Helper Function to reset PEC counters
void LTC6813_reset_crc_count(uint8_t total_ic, cell_asic *ic)
{
     LTC681x_reset_crc_count(total_ic,ic);
}

/* Write the 6813 PWM/S ctrl Register B */
void LTC6813_wrpsb(uint8_t total_ic,cell_asic *ic)
{
	uint8_t cmd[2];
	uint8_t write_buffer[256];
	uint8_t c_ic = 0;
	
	cmd[0] = 0x00;
	cmd[1] = 0x1C;
	for(uint8_t current_ic = 0; current_ic<total_ic;current_ic++)
	{
		if(ic->isospi_reverse == true){c_ic = current_ic;}
		else{c_ic = total_ic - current_ic - 1;}
		write_buffer[0] = ic[c_ic].pwmb.tx_data[0];
		write_buffer[1] = ic[c_ic].pwmb.tx_data[1];
		write_buffer[2]= ic[c_ic].pwmb.tx_data[2];
		write_buffer[3] = ic[c_ic].sctrlb.tx_data[3];
		write_buffer[4] = ic[c_ic].sctrlb.tx_data[4];
		write_buffer[5]= ic[c_ic].sctrlb.tx_data[5];
	}
	write_68(total_ic, cmd, write_buffer);	
}

// reading pwm/s control register b
uint8_t LTC6813_rdpsb(uint8_t total_ic, //!< number of ICs in the daisy chain
                      cell_asic *ic //!< a two dimensional array that the function stores the read pwm data
                      )	
{
    uint8_t cmd[4];
    uint8_t read_buffer[256];
    int8_t pec_error = 0;
    uint16_t data_pec;
    uint16_t calc_pec;
    uint8_t c_ic = 0;
	cmd[0] = 0x00;
	cmd[1] = 0x1E;
    pec_error = read_68(total_ic, cmd, read_buffer);

    for(uint8_t current_ic =0; current_ic<total_ic; current_ic++)
    {	
        if(ic->isospi_reverse == false){c_ic = current_ic;}
        else{c_ic = total_ic - current_ic - 1;}
        for(int byte=0; byte<8;byte++)
        {
            ic[c_ic].pwmb.rx_data[byte] = read_buffer[byte+(8*current_ic)]; 
            ic[c_ic].sctrlb.rx_data[byte] = read_buffer[byte+(8*current_ic)];			
        }	
        calc_pec = pec15_calc(6,&read_buffer[8*current_ic]);
        data_pec = read_buffer[7+(8*current_ic)] | (read_buffer[6+(8*current_ic)]<<8);
        if(calc_pec != data_pec )
        {
            ic[c_ic].sctrlb.rx_pec_match = 1;
			ic[c_ic].pwmb.rx_pec_match = 1;
        }
        else 
		{
			ic[c_ic].sctrlb.rx_pec_match = 0;
			ic[c_ic].pwmb.rx_pec_match = 0;
		}
    }
    return(pec_error);
}
//Mutes the LTC6813 discharge transistors
void LTC6813_mute()
{
	uint8_t cmd[2];

	cmd[0] = 0x00;
	cmd[1] = 0x28;

	cmd_68(cmd);
}
//Clears the LTC6813 Mute Discharge
void LTC6813_unmute()
{
	uint8_t cmd[2];

	cmd[0] = 0x00;
	cmd[1] = 0x29;
	cmd_68(cmd);
}