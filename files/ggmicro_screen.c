
typedef char  bool;



#define DEFAULTFBDEV  "/dev/fb0"
#define DEFAULTFBMODE "/etc/fb.modes"
#define displayno 0
#define DISP_DEV "/dev/disp"

//#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
//#include <linux/input.h>

#include <linux/fb.h>
#include <drv_display.h>


const char *fbdev = DEFAULTFBDEV;
int FB_fd;
disp_layer_info layerinfo;
struct fb_var_screeninfo var;



void FB_init()
{
	int fh;
	fh = open(DEFAULTFBDEV, O_RDONLY);
	
	if ( fh < 0 )
  {
    puts("open fb0 failed");
  }
  else
  {
	  
	  ioctl(fh, 0x4600u, &var);
	
	
	
		  printf("Current screen xres_virtual = %d\n", var.xres_virtual);
		 
		  printf("Current screen yres_virtual = %d\n", var.yres_virtual);
		 
		  printf("Current screen xres = %d\n", var.xres);
		
		  printf("Current screen yres = %d\n", var.yres);
		
		  printf("Current screen yoffset = %d\n", var.yoffset);
		  
		  
		  printf("Current screen bits_per_pixel = %d\n", var.bits_per_pixel);
	
	
	var.yres=200;
	var.xres=320;
	
	
	var.yres_virtual=200;
	var.xres_virtual=320;
	

	var.bits_per_pixel=32;
	printf("setting bits per pixel to %d\n",var.bits_per_pixel);
	
	ioctl(fh, 0x4601, &var);//FBIOPUT_VSCREENINFO
	
	
	
	int args[4] = {displayno, 3, (unsigned long)(&layerinfo), 0};
	
	int dispfile;
	int ret;
	
	dispfile = open(DISP_DEV, O_RDWR, 0);
	if (dispfile < 0) {
		perror("open");
	}
	

	if (ioctl(dispfile, DISP_CMD_LAYER_GET_INFO, &args) < 0)
		perror("ioctl: 0x43 - DISP_CMD_LAYER_GET_INFO");
	
	
	
	layerinfo.fb.size.width=320;
	layerinfo.fb.size.height=200;
	
	layerinfo.fb.src_win.width=320;
	layerinfo.fb.src_win.height=200;
	
	layerinfo.screen_win.width=240;
	layerinfo.screen_win.height=180;
	layerinfo.screen_win.y=38;
	
	//layerinfo.mode=DISP_LAYER_WORK_MODE_NORMAL;
	layerinfo.mode=DISP_LAYER_WORK_MODE_SCALER;
	
	layerinfo.alpha_mode=0;
	
	//printf("setting pixel format to: DISP_FORMAT_RGB_565");
	layerinfo.fb.format = DISP_FORMAT_ARGB_8888; //DISP_FORMAT_RGB_565;
	//layerinfo.fb.format = DISP_FORMAT_RGB_565;
	//layerinfo.fb.format = DISP_FORMAT_YUV444_P;
	//layerinfo.fb.format = DISP_FORMAT_BGRA_4444;
	
	//printf("setting layer mode to 2\n");
	//layerinfo.mode=4;
	
	if (ioctl(dispfile, DISP_CMD_LAYER_SET_INFO, &args) < 0)//DISP_CMD_LAYER_SET_INFO
			perror("ioctl: 0x42 - DISP_CMD_LAYER_SET_INFO");
		puts("set layer 3 info...");
		
		


	//v10x=1;		
	if (ioctl(dispfile, DISP_CMD_LAYER_ENABLE, &args) < 0)//DISP_CMD_LAYER_ENABLE 
			perror("ioctl: 0x41 - DISP_CMD_LAYER_ENABLE");	
			puts("enabled layer 3");
			
			
	args[1]=0;
	if (ioctl(dispfile, DISP_CMD_LAYER_DISABLE, &args) < 0)//DISP_CMD_LAYER_DISABLE 
			perror("ioctl: 0x41 - DISP_CMD_LAYER_DISABLE");	
			puts("disabled layer 0");
	args[1]=1;		
	if (ioctl(dispfile, DISP_CMD_LAYER_DISABLE, &args) < 0)//DISP_CMD_LAYER_DISABLE 
			perror("ioctl: 0x41 - DISP_CMD_LAYER_DISABLE");	
			puts("disabled layer 1");
	args[1]=2;
	if (ioctl(dispfile, DISP_CMD_LAYER_DISABLE, &args) < 0)//DISP_CMD_LAYER_DISABLE 
			perror("ioctl: 0x41 - DISP_CMD_LAYER_DISABLE");	
			puts("disabled layer 2");

	puts("released layer...");
	
	close(fh);
	close(dispfile);




	
	
  }
}