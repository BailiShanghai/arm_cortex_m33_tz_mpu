#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "bk7236_fpga.h"        // Interface API

#include "bk_te200.h"        // Interface API




const uint8_t oled_paset_cmd[8]  = {0x2, 0x0, 0x28, 0x0,  0x12, 0x34, 0x56, 0x78};
const uint8_t oled_caset_cmd[8]  = {0x2, 0x0, 0x2a, 0x0,  0x2, 0x3, 0x4, 0x5};
const uint8_t oled_rdid1_cmd[4]  = {0x3, 0x0, 0xda, 0x0};



//#define TEST_DMA2D_QSPI
////////////////////////////////////////////////////////////////////////
// QSPI
////////////////////////////////////////////////////////////////////////

uint8 qspi_cmd_done_falg = 0;

void wait_qspi_rx_done(void){
	do{
	}
    while ( (addQSPI_Reg0x19 & 0x1) == 0) ;
	addQSPI_Reg0x21 = 0x1;
	addQSPI_Reg0x21 = 0x0;

}
void wait_qspi_tx_done(void){


	do{
	}
    while ( (addQSPI_Reg0x19 & 0x2) == 0) ;
	addQSPI_Reg0x21 = 0x2;
	addQSPI_Reg0x21 = 0x0;

}

void wait_qspi_cmd_done(void){

#if  1

	do{
	}
    while ( (addQSPI_Reg0x22 & 0x4) == 0) ;
	addQSPI_Reg0x21 = 0x4;
	addQSPI_Reg0x21 = 0x0;

#else
  	do{
	}
    while (qspi_cmd_done_falg == 0) ;
	qspi_cmd_done_falg = 0;
#endif

}

void entry_quad_mode_APS6404L(void){

	addQSPI_Reg0x9 = 0x35;
	addQSPI_Reg0xa = 0xc;
	addQSPI_Reg0xb = 0x01;
	wait_qspi_cmd_done();
}



void exit_quad_mode_APS6404L(void){
	addQSPI_Reg0x9 = 0xf5;
	addQSPI_Reg0xa = 0xe;
	addQSPI_Reg0xb = 0x1;
	wait_qspi_cmd_done();
}


void cpu_qpi_fast_read_quad_APS6404L (void){

	addQSPI_Reg0x5 = 0xEB;
	addQSPI_Reg0x6 = 0x3AA;
	addQSPI_Reg0x7 = 0x4068000;
}

void cpu_qpi_quad_write_APS6404L (void){
	addQSPI_Reg0x1 = 0x38;
	addQSPI_Reg0x2 = 0x3AA;
	addQSPI_Reg0x3 = 0x8002;
}

void cpu_qpi_quad_write_OLED (void){
	addQSPI_Reg0x1 = 0x002c0012;
	addQSPI_Reg0x2 = 0x3A8;
	addQSPI_Reg0x3 = 0x80008000;
}


void cpu_spi_write_APS6404L (void){
	addQSPI_Reg0x1 = 0x02;
	addQSPI_Reg0x2 = 0x300;
	addQSPI_Reg0x3 = 0x0;
}


void cpu_spi_fast_read_APS6404L (void){
	addQSPI_Reg0x5 = 0xeb;
	addQSPI_Reg0x6 = 0x3a8;
	addQSPI_Reg0x7 = 0x4068000;
}




void read_id_APS6404L (void){
	uint32 tmp;
    uint32_t *bit_32;

	addQSPI_Reg0xd  = 0x9f;
	addQSPI_Reg0xe  = 0x300;
	addQSPI_Reg0xf  = 0x19;
	wait_qspi_cmd_done();


 	tmp = addQSPI_Reg0x40;

	if (tmp != 0x405d0d){
		DbgPrintf(" read_id_APS6404L fail !\r\n");
		DbgPrintf(" should be  0x405d0d !\r\n");
		DbgPrintf(" read data = %x  !\r\n", tmp);
        while(1);
	}
	else{
		DbgPrintf(" read_id_APS6404L pass !\r\n");
	}

}

void qspi_init_aps6404 (void){

	uint16_t sck_div;

	sck_div = 0x00;    // clk/1
	//sck_div = 0x01;  // clk/2
	addQSPI_Reg0x1c =0x01000000 |  0x9 | ( sck_div << 8); //enable spi & io2/io3


}


void qspi_gpio_config (void){

	
}



void rw_mem_32b_aps6404(uint32_t test_addr){

	uint32_t *bit_32;
    uint16_t *bit_16;
    uint8_t *bit_8;
    uint32_t test_data;
    uint32_t i;
    DbgPrintf("wr psram data .. \r\n" );
	test_data = 0x13572468;
	bit_32 = (uint32_t *)test_addr;
	for (i=0;i<128;i++)
	  {
	    *bit_32 = i+ test_data;
	  	bit_32++;
	  }
	DbgPrintf("rd psram data .. \r\n" );
    bit_32 = (uint32_t *)test_addr;
  	for (i=0; i<128; i++)
  	{
	  	if (*bit_32 != (i + test_data)   ){
	  	  DbgPrintf("QSPI rw PSRAM Error at i = %d\r\n", i);
  		  while(1);
  	  }
		  bit_32++;
	}
}



void test_psram_aps6404(void){
    uint32_t *bit_32;
    uint16_t *bit_16;
    uint8_t *bit_8;
    uint32_t test_data;
    uint32_t i, test_addr;

    qspi_gpio_config();
	qspi_init_aps6404();
	read_id_APS6404L();

#if 1
	DbgPrintf("Test QSPI mode \r\n");
	entry_quad_mode_APS6404L();
	cpu_qpi_quad_write_APS6404L();
	cpu_qpi_fast_read_quad_APS6404L();

	test_addr = BASEADDR_QSPI_DEV;
	rw_mem_32b_aps6404(test_addr);
	DbgPrintf("QSPI mode R/W PASS !\r\n");

#endif

#if 1
	DbgPrintf("Test SPI mode \r\n");
	exit_quad_mode_APS6404L();
  cpu_spi_write_APS6404L();

	cpu_spi_fast_read_APS6404L();

	test_addr = BASEADDR_QSPI_DEV+ 0x100000;


	rw_mem_32b_aps6404(test_addr);


	DbgPrintf("SPI mode R/W PASS !\r\n");

#endif


}

void test_dma2d_psram_aps6404(void){
    uint32_t *bit_32;
    uint16_t *bit_16;
    uint8_t *bit_8;
    uint32_t test_data;
    uint32_t i, test_addr;

    qspi_gpio_config();
	qspi_init_aps6404();
	read_id_APS6404L();

#if 1
	DbgPrintf("Test QSPI mode \r\n");
	entry_quad_mode_APS6404L();
	cpu_qpi_quad_write_APS6404L();
	cpu_qpi_fast_read_quad_APS6404L();
#endif

}


void test_dma2d_oled(void){
    uint32_t *bit_32;
    uint16_t *bit_16;
    uint8_t *bit_8;
    uint32_t test_data;
    uint32_t i, test_addr;

    qspi_gpio_config();
	qspi_init_aps6404();

#if 1
	DbgPrintf("Test QSPI mode \r\n");
	cpu_qpi_quad_write_OLED();
#endif

}


void qspi_init_gb25q32b (void){

	uint16_t sck_div;
	sck_div = 0x00;    // clk/1
	//sck_div = 0x01;  // clk/2
	addQSPI_Reg0x1c =0x01000000 |  0x9 | ( sck_div << 8); //enable spi & io2/io3

	//addSYSTEM_Reg0x9 |= 0xc0;  // 320m/4 = 80M
	//addSYSTEM_Reg0x9 &= 0xfffffcff;  // 320m/4 = 80M

}



void read_id_gb25q32b (void){
	uint32 volatile tmp;
  uint32_t *bit_32;


	addQSPI_Reg0xd  = 0x9f;
	addQSPI_Reg0xe  = 0xc;
	addQSPI_Reg0xf  = 0x11;
	wait_qspi_cmd_done();


 	tmp = addQSPI_Reg0x40;

	if (tmp != 0xc81640c8){
		DbgPrintf(" read_id_gb25q32bL fail !\r\n");
		DbgPrintf(" should be  0xc81640c8 !\r\n");
		DbgPrintf(" read data = %x  !\r\n", tmp);
        while(1);
	}
	else{
		DbgPrintf(" read_id_gb25q32bL pass !\r\n");
	}

}


void wait_wip_done (void){
	uint32 volatile tmp;
  uint32_t *bit_32;


	addQSPI_Reg0xd  = 0x5;
	addQSPI_Reg0xe  = 0xc;

	do {
	  addQSPI_Reg0xf  = 0x5;
	  wait_qspi_cmd_done();
 	  tmp = addQSPI_Reg0x40 & 0x1;
 	   // '1' is busy, '0' is program finish
	}while(tmp == 1);


}

void wren_gd25q32b(void){

	addQSPI_Reg0x9 = 0x06;
	addQSPI_Reg0xa = 0xc;
	addQSPI_Reg0xb = 0x1;
	wait_qspi_cmd_done();
}

void set_page_write_gb25q32b(void){
	addQSPI_Reg0x1 = 0x32;
	addQSPI_Reg0x2 = 0x300;
	addQSPI_Reg0x3 = 0x8000; // data is 4 line
}

void set_page_read_gb25q32b(void){
	addQSPI_Reg0x5 = 0xeb;
	addQSPI_Reg0x6 = 0xea8;  // cmd 1 line, addr 4 line
	addQSPI_Reg0x7 = 0x5048000; // data  4 line
}



void io_rw_mem_32b_gd25q32b(uint32_t test_addr){
	uint8_t *bit_8;

	uint16_t i;
	uint32_t *bit_32, test_data, rdata, tmp_data;
	uint32_t tmp_data1, tmp_data2, tmp_data3;

	bit_32 = (uint32_t *) ( BASEADDR_QSPI + 0x40 *4);

	
  EIP_DEBUG=0x20;

	// fill tx fifo
	test_data = 0x03020100;
	for (i = 0 ; i < 1; i++) {
		*bit_32 = test_data;
		test_data += 0x04040404 ;
		bit_32++;
	}
	wren_gd25q32b();
  EIP_DEBUG=0x21;

	tmp_data1  =  (test_addr & 0xff0000) >> 8;
	tmp_data2 =  (test_addr & 0x00ff00) << 8;
	tmp_data3 =  (test_addr & 0x0000ff) << 16;

	EIP_DEBUG=0x22;
	                                                      // cmd
	addQSPI_Reg0x9 =  tmp_data1 | tmp_data2 | tmp_data3 | 0x32;


	addQSPI_Reg0xa = 0x300;
	//addQSPI_Reg0xb = 0x8401; // data is 4 line , 256 bytes
	addQSPI_Reg0xb = 0x8011; // data is 4 line , 4 bytes
	EIP_DEBUG=0x23;
	wait_qspi_cmd_done();
	EIP_DEBUG=0x24;
  wait_wip_done();
  EIP_DEBUG=0x25;	

                                                         // cmd
  addQSPI_Reg0xd =  tmp_data1 | tmp_data2 | tmp_data3 | 0xeb;


	addQSPI_Reg0xe = 0xea8;    // cmd 1 line, addr 4 line
	//addQSPI_Reg0xf = 0x5048401; // data  4 line
	addQSPI_Reg0xf = 0x5048011; // data  4 line

	  //101 0 0000100     10 00  0100000000 01
	  //101 0000 0100     1000  0100 0000 0001
  EIP_DEBUG=0x26;
	wait_qspi_cmd_done();
  EIP_DEBUG=0x27;
	bit_32 = (uint32_t *) ( BASEADDR_QSPI + 0x40 *4);



	test_data = 0x03020100;
	for (i = 0 ; i < 1; i++) {
		rdata = *bit_32;
	  	if (rdata !=  test_data   ){
	  	  DbgPrintf("IO mode Flash Error at i = %d\r\n", i);
	  	  DbgPrintf("golden =  %x \r\n",  (i + test_data) );
	  	  DbgPrintf("hw =  %x \r\n", rdata);
		  while(1);
        }
		test_data += 0x04040404 ;
	  	bit_32++;

	}
  EIP_DEBUG=0x271;


   DbgPrintf("io mode rw  flash PASS \r\n");


    bit_8 = (uint8_t *)test_addr;
 	for (i=0; i< 256; i++)
 	{
 		rdata = (*bit_8 & 0xff);
	  	if (rdata != i ){
	  	  DbgPrintf(" flash read Error at i = %d\r\n", i);
	  	  DbgPrintf("golden =  %x \r\n", i );
	  	  DbgPrintf("hw =  %x \r\n", rdata);
		  while(1);
       }
		bit_8++;
	}
}

void rw_mem_32b_gd25q32b(uint32_t test_addr){

	uint32_t *bit_32;
    uint16_t *bit_16;
    uint8_t *bit_8;
    uint32_t test_data, rdata;
    uint32_t i;
    DbgPrintf("wr data to flash .. \r\n" );
	test_data = 0x13572468;
	bit_32 = (uint32_t *)test_addr;

	for (i=0;i< 4;i++)
	  {
		wren_gd25q32b();
	    *bit_32 = i+ test_data;
	    wait_wip_done();
	  	bit_32++;
	  }
	DbgPrintf("rd data from flash.. \r\n" );
    bit_32 = (uint32_t *)test_addr;
  	for (i=0; i< 4; i++)
  	{
  		rdata = *bit_32;
	  	if (rdata != (i + test_data)   ){
	  	  DbgPrintf("QSPI rw flash Error at i = %d\r\n", i);
	  	  DbgPrintf("golden =  %x \r\n",  (i + test_data) );
	  	  DbgPrintf("hw =  %x \r\n", rdata);
		  while(1);
        }
		bit_32++;
	}

    DbgPrintf("mem mode rw  flash PASS \r\n");

}


void test_rd_flash_GD25Q32B(void){
    uint32_t *bit_32, test_addr;
    uint16_t *bit_16;
    uint8_t *bit_8;
    uint32_t test_data;
    uint32_t i;

    qspi_gpio_config();
    qspi_init_gb25q32b();

	set_page_read_gb25q32b();


	DbgPrintf("rd data from flash.. \r\n" );
    bit_32 = (uint32_t *)BASEADDR_QSPI_DEV;
  	for (i=0; i< 2; i++)
  	{
    	DbgPrintf("QSPI flash word [%d]  = %x\r\n", i, *bit_32);
		bit_32++;
	}

	DbgPrintf("test end!\r\n");
    while(1);
}


void test_flash_GD25Q32B(void){
    uint32_t *bit_32, test_addr;
    uint16_t *bit_16;
    uint8_t *bit_8;
    uint32_t test_data;
    uint32_t i;

    //qspi_gpio_config();
    qspi_init_gb25q32b();

	set_page_write_gb25q32b();

	set_page_read_gb25q32b();

	test_addr = BASEADDR_QSPI_DEV + 0x0;
	io_rw_mem_32b_gd25q32b(test_addr);

	test_addr = BASEADDR_QSPI_DEV;
	rw_mem_32b_gd25q32b(test_addr);


	DbgPrintf("Flash  R/W PASS !\r\n");


}


















//============================================================================================



