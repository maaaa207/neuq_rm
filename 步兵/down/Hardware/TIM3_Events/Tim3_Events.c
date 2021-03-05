/**
  ******************************************************************************
  * @file    Project/USER/Tim3_Events.c 
  * @author  Siyuan Qiao&Junyu Luo
  * @version V1.0.0
  * @date    1.2021
  * @brief   ��ʱ��3��غ���
  ******************************************************************************
  * @attention
  ******************************************************************************
*/
#include "Tim3_Events.h"


/**
  * @breif �˶����ƺ���
	* @param  ��pid����
	*/
void Robo_Move()
{
	if(stop_flag_1 && ap_pid_flag == ang_pid)			//�����ʱ�ٶ�Ϊ0��ֹͣ�������Զ�����ʱû��������λ�ñջ�   ��ô�Ƕȱջ�
	{	
		break_jugement();
		if(stop_flag_3 && 1)
		{
			stop_chassis_motor();
		}
		apid_chassic_realize(0.2,0.05,0);			
	
	}
  if(1) //(Control_Mode) == 0x03 Control_Mode & auto_control) == auto_control)
	{
		chassic_speed_control(Liner_X, Liner_Y, Angular_Z);		 
		gimbal_speed_control(Angular_Yaw, Angular_Pitch);      //ʹ����̨�ٶȻ�����
	  //gimbal_angle_control(Angle_Yaw,Angle_Pitch);  //ʹ����̨λ�û�����
		//auto_fire();//��λ�����ͱ�־λ  ����
	 }
 
	
   	vpid_chassic_realize(v_chassic_p,v_chassic_i,v_chassic_d);			//�ٶȱջ�2  0.05
	  vpid_trigger_realize(v_trigger_p,v_trigger_i,v_trigger_d);      //�������ٶȱջ�  ����δȷ��   2.5  0.05
    //apid_gimbal_realize(a_yaw_p,a_yaw_i,a_yaw_d,a_pitch_p,a_pitch_i,a_pitch_d);	        //��̨λ�û�����
	  vpid_gimbal_realize(v_yaw_p,v_yaw_i,v_yaw_d,v_pitch_p,v_pitch_i,v_pitch_d);     //  ��̨�ٶȻ��趨
		set_chassis_current();		//�趨�������
	  set_trigger_current();
	  set_gimbal_current();

	  TIM_SetCompare1(TIM1,pwm_pulse_p);
		TIM_SetCompare2(TIM1,pwm_pulse_y);

	  
}



/**
  * @breif �����õİ���������Ƭ���ϵİ�ɫ����
	* @param key_flag
	*/
void Debug_Key()
{
	static int key_flag = unpressed;		//���ڿ��������ж��ڰ��µĹ�����ֻ����һ��
	if( key_press() && key_flag == unpressed)		//�������������
	{
		LED4=!LED4;												//LED4��ת������״ָ̬ʾ
		key_flag = pressed;			          //����������
		// your codes below
		
		//NRF24L01_TxPacket(send_data);			//nrf�����ַ���
	}
	else if(!key_press())
		key_flag=unpressed;		//����δ������
}

