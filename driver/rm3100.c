#include<stdio.h>
#include<unistd.h>/*gives access to POSIX : which allows multiple process to overlap*/
#include<stdint.h>/*extended data type of int to limit width*/
#include</sys/ioctl.h>
#include</dev/i2c-3>
#include<fcntl.h>/*file operations*/
#include<sys.stat.h>/*contains dev_t : ID of device file*/
#include<sys/types.h>
#include<errno.h>
#define dev "i2c-8"
#define slave_add 0

uint8_t cycle_x_lsb=0x05;
uint8_t cycle_x_msb=0x04;
uint8_t cycle_y_lsb=0x07;
uint8_t cycle_y_msb=0x06;
uint8_t cycle_z_lsb=0x09;
uint8_t cycle_z_msb=0x08;

int cycle_x_lsb_val=;
int cycle_x_msb_val=;
int cycle_y_lsb_val=;
int cycle_y_msb_val=;
int cycle_z_lsb_val=;
int cycle_z_msb_val=;

int fd=open(dev,O_RDWR);
int cmm_active()
{
	if(ioctl(fd,I2C_SLAVE,slave_add)<0)
	{
		printk("Connection to slave failed");
		close(fd);
		return 1;
	}
	else
	{
		char buf[2];
		buf[0]=0x01;
		buf[1]=0x81;
		if(write(fd,buf,2)==2)
		{
			return errno;
		}
		else
		{
			return errno;
		}
	}
}

int cycle()
{
	read(fd,cycle_x_lsb,1);
	write(fd,cycle_x_lsb_val,1);
	read(fd,cycle_y_lsb,1);
	write(fd,cycle_y_lsb_val,1);
	read(fd,cycle_z_lsb,1);
	write(fd,cycle_z_lsb_val,1);

	read(fd,cycle_x_msb,1);
	write(fd,cycle_x_msb_val,1);
	read(fd,cycle_y_msb,1);
	write(fd,cycle_y_msb_val,1);
	read(fd,cycle_z_msb,1);
	write(fd,cycle_z_msb_val,1);


	
int status()
	{
		char st=0xB4;
		char r;
		write(fd,&st,1);
		if(read(fd,&r,1)>0)
		{
			return 1;
		}
		else return 0;
}
int powe(int d,int k)
{
	int s=1;
	while(k>0)
	{
		s=s*2;
		k-=1;
	}
	s=s*d;
	return s;
}
int read_meas()
{
	char bufx[3];
	bufx[0]=0x24;
	bufx[1]=0x25;
	bufx[2]=0x26;

	char bufz[3];
	bufz[0]=0x2A;
	bufz[1]=0x2B;
	bufz[2]=0x2C;

	char bufy[3];
	bufy[0]=0x27;
	bufy[1]=0x28;
	bufy[2]=0x29;

	char bufxr[3];
	bufxr[0]=0xA4;
	bufxr[1]=0xA5;
	bufxr[2]=0xA6;

	char bufzr[3];
	bufzr[0]=0xAA;
	bufzr[1]=0xAB;
	bufzr[2]=0xAC;

	write(fd,bufx,3);
	char x_ax[3]=read(fd,bufxr,3);
	write(fd,bufy,3);
	char y_ay[3]=read(fd,bufyr,3);
	write(fd,bufz,3);
	char z_ax[3]= read(fd,bufzr,3);
	int x_axis=(x_ax[2]<<16)+(x_ax[1]<<8)+x_ax[0];
	int y_axis=(y_ax[2]<<16)+(y_ax[1]<<8)+y_ax[0];
	int z_axis=(z_ax[2]<<16)+(z_ax[1]<<8)+z_ax[0];
	int reading[3]=[bcd(x_axis),bcd(y_axis),bcd(z_axis)];
	return reading;
}


int bcd(int v)
{
	int sum=0;
	for(i=0;i<15,i++)
	{
		d=v<<i;
		sum=sum+(pow(d,i));
	}
	return sum;

}


int main()
{cmm_active();
cycle();
status();
read_meas();	

}










































































































































































































































































































































































































































































































































































	C;

	char bufyr[3];
	bufyr[0]=0x27;
	bufyr[1]=0x28;
	bufyr[2]=0x29;
}