#ifndef __UltrasonicWave_H
#define	__UltrasonicWave_H

void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave_StartMeasure(void);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��

extern float UltrasonicWave_Distance;      //������ľ���  

extern char DisNum[5];

#endif /* __UltrasonicWave_H */

