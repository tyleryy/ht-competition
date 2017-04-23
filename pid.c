#include "pid.h"


void pid_cal(pid_s *pid, float target, float measure, u32 dert_t)
{
	float dt=dert_t;

	pid->error = target - measure;
	pid->deriv = (pid->error - pid->pre_error) / dt;

	pid->output = pid->p * pid->error + pid->d * pid->deriv;
}
