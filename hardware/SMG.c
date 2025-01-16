#include "SMG.h"


 unsigned char  Seg_test[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};	//八段数码管显示的每一段
 unsigned char  Dign[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};		//对位的译码数组
 unsigned char  Number_arr[10]=   {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};			 //共阳极数码管数字0-9编码数组
 unsigned char  Character_arr[53]={0x88/*A*/,0xff,0xc6 /*C*/,0xff,0x86/*E*/,0x8e/*F*/,0xff,0x89/*H*/,
									  0xff,0xff,0xff,0xc7/*L*/,0xff,0xff,0xff,				 				 //数码管可显示字符编码表
									  0x8c/*P*/,0x98/*Q*/,0xff,0xff,0xff,0xc1/*U*/,
									  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
									  0xf7/*_*/,0xff,0xff,0x83/*b*/,			 							 //包括_,A,C,E,F,H,L,P,Q,U,-,b,c,d,h,l,n,o,u
									  0xa7/*c*/,0xa1/*d*/,0xff,0xff,0xff,0x8b/*h*/,0xff,0xff,0xff,0xcf/*l*/,0xff,
									  0xab/*n*/,0xa3/*o*/,0xff,0xff,0xaf/*r*/,0xff,0xff,0xe3/*u*/};

//unsigned char  Seg_test[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

//*功  能：初始化显示接口
void DisplayInterfaceInit(void)
{
	HC595_GPIO_Config();
}
/*************************************************************************************
*函数名：void DisplayInterfaceInit(void)
*功  能：在dign位显示Dat,最右侧是第1位
*说  明：dign的范围是1-8，dat数据任意
**************************************************************************************/
void DisplayDatOnDign(unsigned char dign,unsigned char dat)
{
	dign-=1;								   //先将dign减1对应到0-7
	dign&=0x07;								   //如果dign不合法，将dign的高位抹去
	ShiftInTwoByteAndLatch(dat,Dign[dign]);	   //将dign译码并显示
}
/*************************************************************************************
*函数名：void DisplayNumOnDign(unsigned char dign,unsigned char num,unsigned char dot)
*功  能：在dign位显示数字Num，并可设置是否显示小数点
*说  明：dign的范围是1-8，Num数据0-9,dot==1显示小数点
**************************************************************************************/
void DisplayNumOnDign(unsigned char dign,unsigned char num,unsigned char dot)
{
	unsigned char tmp;

	dign-=1;								   //先将dign减1对应到0-7
	dign&=0x07;								   //如果dign不合法，将dign的高位抹去
	
	if(num>9)								   //判断num是否超范围
	{
		num=9;
	}

	tmp=Number_arr[num];					   //判断是否显示小数点

	if((dot&0x01)==0x01)
	{
		tmp&=0x7f;
	}

	ShiftInTwoByteAndLatch(tmp,Dign[dign]);	   //将dign译码并显示
}
/*************************************************************************************
*函数名：void DisplayCharOnDign(unsigned char dign,unsigned char c,unsigned char dot)
*功  能：在dign位显示字符c，并可设置是否显示小数点
*说  明：dign的范围是1-8，c数据范围为0-9的数字和“_,A,C,E,F,H,L,P,Q,U,-,b,c,d,h,l,n,o,u”
		 dot==1显示小数点
**************************************************************************************/
void DisplayCharOnDign(unsigned char dign,unsigned char c,unsigned char dot)
{
	if(c>0&&c<=9)										//判断是否为数字
	{
		DisplayNumOnDign(dign,c,dot);
	}
	else if(c>=65&&c<=117)								//判断是否为字符从’A'到‘u’
	{
		DisplayDatOnDign(dign,Character_arr[(c-65)]);
	}
	else if(c==45)										//判断是否为’-‘号
	{
		DisplayDatOnDign(dign,0xbf);
	}
	else if(c==32)										//显示空白
	{
		DisplayDatOnDign(dign,0xff);
	} 
	else if(c==61)									    //判断是否为‘=’号
	{
		DisplayDatOnDign(dign,0xb7);
	}
	else if(c==46)									    //判断是否为‘.’号
	{
		DisplayDatOnDign(dign,0x7f);
	}
}

void Menu(unsigned char x, unsigned char y, unsigned char z,unsigned char weishu)
{ 
	if(weishu==0)
	  {DisplayNumOnDign(1,x%10,1);}		
	else
	if(weishu==1)
	  {DisplayNumOnDign(2,y%100/10,0);}
	else
	if(weishu==2)
	  {DisplayNumOnDign(3,y%10,1);}
	else
	if(weishu==3)
	  {DisplayNumOnDign(4,z%10,0);}
}
