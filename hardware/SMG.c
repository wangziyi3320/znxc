#include "SMG.h"


 unsigned char  Seg_test[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};	//�˶��������ʾ��ÿһ��
 unsigned char  Dign[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};		//��λ����������
 unsigned char  Number_arr[10]=   {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};			 //���������������0-9��������
 unsigned char  Character_arr[53]={0x88/*A*/,0xff,0xc6 /*C*/,0xff,0x86/*E*/,0x8e/*F*/,0xff,0x89/*H*/,
									  0xff,0xff,0xff,0xc7/*L*/,0xff,0xff,0xff,				 				 //����ܿ���ʾ�ַ������
									  0x8c/*P*/,0x98/*Q*/,0xff,0xff,0xff,0xc1/*U*/,
									  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
									  0xf7/*_*/,0xff,0xff,0x83/*b*/,			 							 //����_,A,C,E,F,H,L,P,Q,U,-,b,c,d,h,l,n,o,u
									  0xa7/*c*/,0xa1/*d*/,0xff,0xff,0xff,0x8b/*h*/,0xff,0xff,0xff,0xcf/*l*/,0xff,
									  0xab/*n*/,0xa3/*o*/,0xff,0xff,0xaf/*r*/,0xff,0xff,0xe3/*u*/};

//unsigned char  Seg_test[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

//*��  �ܣ���ʼ����ʾ�ӿ�
void DisplayInterfaceInit(void)
{
	HC595_GPIO_Config();
}
/*************************************************************************************
*��������void DisplayInterfaceInit(void)
*��  �ܣ���dignλ��ʾDat,���Ҳ��ǵ�1λ
*˵  ����dign�ķ�Χ��1-8��dat��������
**************************************************************************************/
void DisplayDatOnDign(unsigned char dign,unsigned char dat)
{
	dign-=1;								   //�Ƚ�dign��1��Ӧ��0-7
	dign&=0x07;								   //���dign���Ϸ�����dign�ĸ�λĨȥ
	ShiftInTwoByteAndLatch(dat,Dign[dign]);	   //��dign���벢��ʾ
}
/*************************************************************************************
*��������void DisplayNumOnDign(unsigned char dign,unsigned char num,unsigned char dot)
*��  �ܣ���dignλ��ʾ����Num�����������Ƿ���ʾС����
*˵  ����dign�ķ�Χ��1-8��Num����0-9,dot==1��ʾС����
**************************************************************************************/
void DisplayNumOnDign(unsigned char dign,unsigned char num,unsigned char dot)
{
	unsigned char tmp;

	dign-=1;								   //�Ƚ�dign��1��Ӧ��0-7
	dign&=0x07;								   //���dign���Ϸ�����dign�ĸ�λĨȥ
	
	if(num>9)								   //�ж�num�Ƿ񳬷�Χ
	{
		num=9;
	}

	tmp=Number_arr[num];					   //�ж��Ƿ���ʾС����

	if((dot&0x01)==0x01)
	{
		tmp&=0x7f;
	}

	ShiftInTwoByteAndLatch(tmp,Dign[dign]);	   //��dign���벢��ʾ
}
/*************************************************************************************
*��������void DisplayCharOnDign(unsigned char dign,unsigned char c,unsigned char dot)
*��  �ܣ���dignλ��ʾ�ַ�c�����������Ƿ���ʾС����
*˵  ����dign�ķ�Χ��1-8��c���ݷ�ΧΪ0-9�����ֺ͡�_,A,C,E,F,H,L,P,Q,U,-,b,c,d,h,l,n,o,u��
		 dot==1��ʾС����
**************************************************************************************/
void DisplayCharOnDign(unsigned char dign,unsigned char c,unsigned char dot)
{
	if(c>0&&c<=9)										//�ж��Ƿ�Ϊ����
	{
		DisplayNumOnDign(dign,c,dot);
	}
	else if(c>=65&&c<=117)								//�ж��Ƿ�Ϊ�ַ��ӡ�A'����u��
	{
		DisplayDatOnDign(dign,Character_arr[(c-65)]);
	}
	else if(c==45)										//�ж��Ƿ�Ϊ��-����
	{
		DisplayDatOnDign(dign,0xbf);
	}
	else if(c==32)										//��ʾ�հ�
	{
		DisplayDatOnDign(dign,0xff);
	} 
	else if(c==61)									    //�ж��Ƿ�Ϊ��=����
	{
		DisplayDatOnDign(dign,0xb7);
	}
	else if(c==46)									    //�ж��Ƿ�Ϊ��.����
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
