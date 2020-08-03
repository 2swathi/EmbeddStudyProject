/* -------------------������ͷ�ļ�-----------------------------------------------*/
#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "sdcard.h"
#include "ff.h"
uint8_t tx_buf[512];
uint8_t rx_buf[512];
#define Debug printf
void OutPutFile(void);
/* Private functions ---------------------------------------------------------*/
FATFS fs;            // Work area (file system object) for logical drive
FIL fsrc, fdst;      // file objects
BYTE buffer[512]; // file copy buffer
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count

uint8_t textFileBuffer[100] = "Thank you for using Waveshare Development Board!\r\n";
#if _USE_LFN
char Fs_LongFileName[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
#endif
/*************************************************************************************
  * �������ƣ�main()
  * ����    ��void
  * ����ֵ  ��void
  * ����    �����������main����
  *************************************************************************************/
int main(void)
{ 
	SD_Error state;
	FATFS fs;           
	FRESULT res;                 
	DIR dirs;
  	FILINFO finfo;
  SystemInit();			                      //��ʼ��ϵͳʱ�ӣ�����ʱ��Ϊ168Mhz

  SysTick_Init();
  USART1_Conf();

	state=SD_Init();
  delay_nms(100);
	printf("����һ��SD����дʵ�飡\r\n");
   delay_nms(50);
   if(state==SD_OK)
		 {
			  printf("SD����ʼ���ɹ���\r\n");
			}
			else
			{
				   printf("SD����ʼ��ʧ�ܣ�\r\n");
			}
			
		 printf("SD����Ϊ��%dM\r\n",SDCardInfo.CardCapacity>>20);
			//disk_initialize();
		res=f_mount(0, &fs);
  	res=f_opendir(&dirs, "0:/");//�򿪸�Ŀ¼
  	res=f_readdir(&dirs, &finfo);
			
				OutPutFile();

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

void OutPutFile(void)
{ 
	unsigned int a;
	FRESULT res;
	FILINFO finfo;
	DIR dirs;
	char path[16]={""};  
#if _USE_LFN
    finfo.lfname = Fs_LongFileName;
    finfo.lfsize = sizeof(Fs_LongFileName);
#endif

	Debug(" ���̳�ʼ��:%d\r\n",disk_initialize(0));
	Debug("���ش���:%d\r\n",f_mount(0, &fs));

	if (f_opendir(&dirs, path) == FR_OK) 
	{
    	while (f_readdir(&dirs, &finfo) == FR_OK)  
    	{
      		if (finfo.fattrib & AM_ARC) 
      		{
        		if(!finfo.fname[0]) break;        
        		Debug("���ļ���:%s\r\n",finfo.fname);
#if _USE_LFN
        		Debug("���ļ���:%s\r\n",finfo.lfname);
#endif
        		res = f_open(&fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ);
        		br=1;
				a=0;
				Debug("�ļ�ͷ255�ֽ�����:");
				//for (;;) 
				{					
					for(a=0; a<512; a++) buffer[a]=0; 
		    	    res = f_read(&fsrc, buffer, sizeof(buffer), &br);
					Debug("%s\r\n",buffer);	
		    	    if (res || br == 0) break;   // error or eof
        		}
				f_close(&fsrc);                 
			}
		} 
	}
  	res = f_unlink("0:/test.txt");
	if(res==FR_OK)
		printf("test.txt file has been Deleted!,%d\r\n",res);
	else
		printf("test.txt file has not been Deleted!,%d\r\n",res);
	res = f_open(&fsrc,"0:/test.txt", FA_CREATE_ALWAYS | FA_WRITE);
	if(res==FR_OK)
	{
		printf("test.txt file has been create!,%d\r\n",res);

		res = f_write(&fsrc,textFileBuffer,sizeof(textFileBuffer),(void *)&bw);
		if(res==FR_OK)
			printf("test.txt file has been writed!,%d\r\n",res);
		else
			printf("test.txt file has not been writed!,%d\r\n",res);	
	}
	else
		printf("test.txt file has not been create!,%d\r\n",res);	
  	f_close(&fsrc);

	res = f_open(&fsrc,"0:/test.txt", FA_OPEN_EXISTING | FA_READ);
	if(res==FR_OK)
	{
		res = f_read(&fsrc, buffer, sizeof(buffer), &br);
		Debug("%s\r\n",buffer);	
	}
	else
		printf("test.txt file has not been create!,%d\r\n",res);	
  	f_close(&fsrc);

	while(1);
}

