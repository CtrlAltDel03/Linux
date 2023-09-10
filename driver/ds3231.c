#include<stdio.h>
#include<unistd.h>/*gives access to POSIX : which allows multiple process to overlap*/
#include<stdint.h>/*extended data type of int to limit width*/
#include</sys/ioctl.h>
#include</dev/i2c-3>
#include<fcntl.h>/*file operations*/
#include<sys.stat.h>/*contains dev_t : ID of device file*/

uint8_t slave_add=0b110100
uint8_t reg_sec=0x00
uint8_t reg_min=0x01
uint8_t reg_hr=0x02
uint8_t reg_day=0x03
uint8_t reg_date=0x04
uint8_t reg_month=0x05
uint8_t reg_yr=0x06 	

#define dev "/dev/i2c-19"
int fd=open(dev,O_RDWR);
static ssize_t my_read(int fd,void* buf,size_t count){
size_t bytt=read(fd,buf,count)
if(bytt=count)
{
	return bytt;
}
else
{
	printk("File read failed");
}
}

static ssize_t my_write(int fd,void *buf,size_t count){
	size_t bytt=write(fd,buf,count)
	if(bytt==count)
	{
		return bytt;
	}
	else
	{
		printk("File write failed");
	}
}


int date()

{
	uint8_t dater;
	if(ioctl(fd,I2C_SLAVE,slave_add)<0)
	{
		printk("Connection to slave failed");
		close(fd);
		return 1;
	}
	my_write(fd,&date,1);
	my_read(fd,&dater,1);
	close(fd);
	int out=dateb_date(dater);
	printk(out);
	return 0;
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

int dateb_date(uint8_t d)
{
	int j=0;
	int i;
	int fid=0;
	while(j<4)
	{
		i=d>>j;
		fid=fid+powe(i,j);
		j+=1;
		
	}
	int w=0;
	while(w<2){
		i=d>>(4+w);
		fid+=(10*powe(i,w));
		w+=1
	}
	return fid;
}

int sec_min()

{
	uint8_t secr,minr;
	if(ioctl(fd,I2C_SLAVE,slave_add)<0)
	{
		printk("Connection to slave failed");
		close(fd);
		return 1;
	}
	my_write(fd,&reg_sec,1);
	my_read(fd,&secr,1);
	my_write(fd,&reg_min,1);
	my_read(fd,&minr,1);
	int out1=min_sec_convert(secr);
	printk("Seconds %d",out1);
	int out2=min_sec_convert(minr);
	printk("minutes %d",out2);
	close(fd);
	return 0;
}

int min_sec_convert(uint8_t d)
{
	int j=0;
	int i;
	int fid=0;
	while(j<4)
	{
		i=d>>j;
		fid=fid+powe(i,j);
		j+=1;
	}
	int w=0;
	while(w<3){
		i=d>>(4+w);
		fid+=(10*powe(i,w));
		w+=1;
	}
	return fid;
}
int hour_convert(uint8_t d)
{
	int j=0;
	int i;
	int fid=0;
	while(j<4)
	{
		i=d>>j;
		fid=fid+powe(i,j);
		j+=1;
	}
	fid+=10*powe(d>>4,0);
	if(d>>6)
	{
		if(d>>5){
			printk("%d AM",fid);
		}
		else
			printk("%d PM",fid);
	}
	else
	{
		fid+=10*powe(d>>5,1);
		printk("%d",fid);
	}

}
int hr()
{
	uint8_t hrr;
	if(ioctl(fd,I2C_SLAVE,slave_add)<0)
	{
		printk("Connection to slave failed");
		close(fd);
		return 1;
	}
	my_write(fd,&reg_hr,1);
	my_read(fd,&hrr,1);
	hour_convert(hrr);
	close(fd);
	return 0;
}

int main(){
	date();
	sec_min();
	hr();

}