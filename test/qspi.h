#ifndef _ARMSTAT_M33_QSPI_H_
#define _ARMSTAT_M33_QSPI_H_

//************************************************************//
//QSPI#endif
//************************************************************//// eof
#define BASEADDR_QSPI                                           0x40001800
//addJPEG_Reg0x0
#define addQSPI_Reg0x0                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x0  *4))
#define addQSPI_Reg0x1                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x1  *4))
#define addQSPI_Reg0x2                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x2  *4))
#define addQSPI_Reg0x3                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x3  *4))

#define addQSPI_Reg0x4                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x4  *4))
#define addQSPI_Reg0x5                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x5  *4))
#define addQSPI_Reg0x6                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x6  *4))
#define addQSPI_Reg0x7                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x7  *4))

#define addQSPI_Reg0x8                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x8  *4))
#define addQSPI_Reg0x9                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0x9  *4))
#define addQSPI_Reg0xa                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0xa  *4))
#define addQSPI_Reg0xb                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0xb  *4))

#define addQSPI_Reg0xc                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0xc  *4))
#define addQSPI_Reg0xd                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0xd  *4))
#define addQSPI_Reg0xe                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0xe  *4))
#define addQSPI_Reg0xf                                          *((volatile unsigned long *) (BASEADDR_QSPI + 0xf  *4))

#define addQSPI_Reg0x10                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x10 *4))
#define addQSPI_Reg0x11                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x11 *4))
#define addQSPI_Reg0x12                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x12 *4))
#define addQSPI_Reg0x13                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x13 *4))

#define addQSPI_Reg0x14                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x14 *4))
#define addQSPI_Reg0x15                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x15 *4))
#define addQSPI_Reg0x16                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x16 *4))
#define addQSPI_Reg0x17                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x17 *4))

#define addQSPI_Reg0x18                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x18 *4))
#define addQSPI_Reg0x19                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x19 *4))
#define addQSPI_Reg0x1a                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x1a *4))
#define addQSPI_Reg0x1b                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x1b *4))

#define addQSPI_Reg0x1c                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x1c *4))
#define addQSPI_Reg0x1d                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x1d *4))
#define addQSPI_Reg0x1e                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x1e *4))
#define addQSPI_Reg0x1f                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x1f *4))

#define addQSPI_Reg0x20                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x20 *4))
#define addQSPI_Reg0x21                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x21 *4))
#define addQSPI_Reg0x22                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x22 *4))

// IO MEM
#define addQSPI_Reg0x40                                         *((volatile unsigned long *) (BASEADDR_QSPI + 0x40 *4))

//#define   BASEADDR_PSRAM                                        0x80000000
#define   BASEADDR_QSPI_DEV                                     0x80000000
#endif // _ARMSTAT_M33_QSPI_H_
// eof
