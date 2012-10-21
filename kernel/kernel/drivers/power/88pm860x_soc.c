#include <linux/kernel.h>

#ifndef __PM860X_SOC_H
#define __PM860X_SOC_H

#define OCV_NUM 101


#if  (defined CONFIG_PXA_U802) ||(defined CONFIG_PXA_U810)
#if 0
u32 array_soc[OCV_NUM][2] =
{ {4151, 99}, {4140, 98}, {4125, 97}, {4115, 96},
{4106, 95}, {4097, 94}, {4088, 93}, {4078, 92}, {4068, 91},
{4062, 90}, {4056, 89}, {4052, 88}, {4049, 87}, {4040, 86},
{4026, 85}, {4010, 84}, {3991, 83}, {3976, 82}, {3965, 81},
{3956, 80}, {3948, 79}, {3942, 78}, {3935, 77}, {3931, 76},
{3928, 75}, {3924, 74}, {3919, 73}, {3914, 72}, {3906, 71},
{3899, 70}, {3893, 69}, {3885, 68}, {3878, 67}, {3871, 66},
{3863, 65}, {3858, 64}, {3850, 63}, {3844, 62}, {3839, 61},
{3833, 60}, {3828, 59}, {3823, 58}, {3817, 57}, {3813, 56},
{3809, 55}, {3805, 54}, {3801, 53}, {3797, 52}, {3794, 51},
{3790, 50}, {3786, 49}, {3783, 48}, {3780, 47}, {3777, 46},
{3774, 45}, {3771, 44}, {3769, 43}, {3765, 42}, {3763, 41},
{3761, 40}, {3758, 39}, {3756, 38}, {3753, 37}, {3751, 36},
{3749, 35}, {3747, 34}, {3745, 33}, {3744, 32}, {3742, 31},
{3741, 30}, {3739, 29}, {3737, 28}, {3735, 27}, {3733, 26},
{3731, 25}, {3728, 24}, {3726, 23}, {3723, 22}, {3720, 21},
{3718, 20}, {3712, 19}, {3707, 18}, {3703, 17}, {3698, 16},
{3692, 15}, {3687, 14}, {3680, 13}, {3673, 12}, {3670, 11},
{3668, 10}, {3667, 9}, {3665, 8}, {3663, 7}, {3658, 6},{3653, 5},
{3638, 4}, {3605, 3}, {3549, 2},{3500, 1}, {3390, 0}
};
#endif
#if 0
u32 array_soc[OCV_NUM][2] =                     
    { {4156, 99}, {4134, 98}, {4126, 97}, {4118, 96},
{4110, 95}, {4102, 94}, {4094, 93}, {4086, 92}, {4078, 91},
{4070, 90}, {4062, 89}, {4054, 88}, {4046, 87}, {4038, 86},
{4030, 85}, {4022, 84}, {4014, 83}, {4006, 82}, {3998, 81},
{3990, 80}, {3982, 79}, {3974, 78}, {3966, 77}, {3958, 76},
{3950, 75}, {3942, 74}, {3934, 73}, {3926, 72}, {3918, 71},
{3910, 70}, {3902, 69}, {3894, 68}, {3886, 67}, {3878, 66},
{3870, 65}, {3862, 64}, {3854, 63}, {3846, 62}, {3838, 61},
{3830, 60}, {3822, 59}, {3814, 58}, {3806, 57}, {3798, 56},
{3790, 55}, {3782, 54}, {3774, 53}, {3766, 52}, {3758, 51},
{3750, 50}, {3742, 49}, {3734, 48}, {3726, 47}, {3718, 46},
{3710, 45}, {3702, 44}, {3694, 43}, {3686, 42}, {3678, 41},
{3670, 40}, {3662, 39}, {3654, 38}, {3646, 37}, {3638, 36},
{3630, 35}, {3622, 34}, {3614, 33}, {3606, 32}, {3598, 31},
{3590, 30}, {3582, 29}, {3574, 28}, {3566, 27}, {3558, 26},
{3550, 25}, {3542, 24}, {3534, 23}, {3526, 22}, {3518, 21},
{3510, 20}, {3502, 19}, {3494, 18}, {3486, 17}, {3478, 16},
{3470, 15}, {3462, 14}, {3454, 13}, {3446, 12}, {3438, 11},
{3430, 10}, {3422, 9}, {3414, 8}, {3406, 7}, {3398, 6},{3395, 5},
{3392, 4}, {3389, 3}, {3386, 2},{3383, 1}, {3380, 0}

};
#endif
u32 array_soc[OCV_NUM][2] =                     
    {{4140, 100},{4120, 99}, {4100, 98}, {4090, 97}, {4080, 96},
	{4070, 95}, {4060, 94}, {4050, 93}, {4045, 92}, {4040, 91},
	{4035, 90}, {4030, 89}, {4025, 88}, {4020, 87}, {4015, 86},
	{4010, 85}, {4005, 84}, {4000, 83}, {3995, 82}, {3990, 81},
	{3985, 80}, {3980, 79}, {3975, 78}, {3970, 77}, {3965, 76},
	{3960, 75}, {3955, 74}, {3950, 73}, {3945, 72}, {3940, 71},
	{3935, 70}, {3930, 69}, {3925, 68}, {3920, 67}, {3915, 66},
	{3910, 65}, {3905, 64}, {3900, 63}, {3895, 62}, {3890, 61},
	{3885, 60}, {3880, 59}, {3875, 58}, {3870, 57}, {3865, 56},
	{3860, 55}, {3855, 54}, {3850, 53}, {3845, 52}, {3840, 51},
	{3835, 50}, {3830, 49}, {3825, 48}, {3820, 47}, {3815, 46},
	{3810, 45}, {3805, 44}, {3796, 43}, {3789, 42}, {3782, 41},
	{3775, 40}, {3768, 39}, {3761, 38}, {3754, 37}, {3747, 36},
	{3740, 35}, {3733, 34}, {3726, 33}, {3719, 32}, {3712, 31},
	{3705, 30}, {3698, 29}, {3691, 28}, {3684, 27}, {3677, 26},
	{3670, 25}, {3663, 24}, {3656, 23}, {3649, 22}, {3642, 21},
	{3635, 20}, {3628, 19}, {3621, 18}, {3614, 17}, {3607, 16},
	{3600, 15}, {3595, 14}, {3590, 13}, {3585, 12}, {3580, 11},
	{3575, 10}, {3570, 9}, {3565, 8}, {3560, 7}, {3555, 6},{3550, 5},
	{3545, 4}, {3540, 3}, {3460, 2},{3400, 1}, {3380, 0}

};

#elif defined  CONFIG_PXA_U880

u32 array_soc[OCV_NUM][2] =                     
    { {4140, 100}, {4120, 99}, {4100, 98}, {4090, 97}, {4080, 96},
	{4070, 95}, {4060, 94}, {4050, 93}, {4045, 92}, {4040, 91},
	{4035, 90}, {4030, 89}, {4025, 88}, {4020, 87}, {4015, 86},
	{4010, 85}, {4005, 84}, {4000, 83}, {3995, 82}, {3990, 81},
	{3985, 80}, {3980, 79}, {3975, 78}, {3970, 77}, {3965, 76},
	{3960, 75}, {3955, 74}, {3950, 73}, {3945, 72}, {3940, 71},
	{3935, 70}, {3930, 69}, {3925, 68}, {3920, 67}, {3915, 66},
	{3910, 65}, {3905, 64}, {3900, 63}, {3895, 62}, {3890, 61},
	{3885, 60}, {3880, 59}, {3875, 58}, {3870, 57}, {3865, 56},
	{3860, 55}, {3855, 54}, {3850, 53}, {3845, 52}, {3840, 51},
	{3835, 50}, {3830, 49}, {3825, 48}, {3820, 47}, {3815, 46},
	{3810, 45}, {3805, 44}, {3796, 43}, {3789, 42}, {3782, 41},
	{3775, 40}, {3768, 39}, {3761, 38}, {3754, 37}, {3747, 36},
	{3740, 35}, {3733, 34}, {3726, 33}, {3719, 32}, {3712, 31},
	{3705, 30}, {3698, 29}, {3691, 28}, {3684, 27}, {3677, 26},
	{3670, 25}, {3663, 24}, {3656, 23}, {3649, 22}, {3644, 21},
	{3640, 20}, {3636, 19}, {3632, 18}, {3628, 17}, {3624, 16},
	{3620, 15}, {3616, 14}, {3611, 13}, {3606, 12}, {3603, 11},
	{3600, 10}, {3590, 9}, {3580, 8}, {3575, 7}, {3570, 6},{3560, 5},
	{3550, 4}, {3540, 3}, {3460, 2},{3400, 1}, {3380, 0}

};
#elif (defined  CONFIG_PXA_U812 || defined  CONFIG_PXA_U830)

u32 array_soc[OCV_NUM][2] =                     
    { {4140, 100}, {4120, 99}, {4100, 98}, {4090, 97}, {4080, 96},
	{4070, 95}, {4060, 94}, {4050, 93}, {4045, 92}, {4040, 91},
	{4035, 90}, {4030, 89}, {4025, 88}, {4020, 87}, {4015, 86},
	{4010, 85}, {4005, 84}, {4000, 83}, {3995, 82}, {3990, 81},
	{3985, 80}, {3980, 79}, {3975, 78}, {3970, 77}, {3965, 76},
	{3960, 75}, {3955, 74}, {3950, 73}, {3945, 72}, {3940, 71},
	{3935, 70}, {3930, 69}, {3925, 68}, {3920, 67}, {3915, 66},
	{3910, 65}, {3905, 64}, {3900, 63}, {3895, 62}, {3890, 61},
	{3885, 60}, {3880, 59}, {3875, 58}, {3870, 57}, {3865, 56},
	{3860, 55}, {3855, 54}, {3850, 53}, {3845, 52}, {3840, 51},
	{3835, 50}, {3830, 49}, {3825, 48}, {3820, 47}, {3815, 46},
	{3810, 45}, {3805, 44}, {3796, 43}, {3789, 42}, {3782, 41},
	{3775, 40}, {3768, 39}, {3761, 38}, {3754, 37}, {3747, 36},
	{3740, 35}, {3733, 34}, {3726, 33}, {3719, 32}, {3712, 31},
	{3705, 30}, {3698, 29}, {3691, 28}, {3684, 27}, {3677, 26},
	{3670, 25}, {3663, 24}, {3656, 23}, {3649, 22}, {3644, 21},
	{3640, 20}, {3636, 19}, {3632, 18}, {3628, 17}, {3624, 16},
	{3620, 15}, {3616, 14}, {3611, 13}, {3606, 12}, {3603, 11},
	{3600, 10}, {3590, 9}, {3580, 8}, {3575, 7}, {3570, 6},{3560, 5},
	{3550, 4}, {3540, 3}, {3460, 2},{3400, 1}, {3380, 0}

};
#endif

#ifdef CONFIG_PXA_U880
int para_on=2985,para_off=3019;
int version_880 = 1;
int vchg_normal_high= 7000;
#else
int para_on=3000,para_off=3029;
int version_880 = 0;
int vchg_normal_high= 7000;

#endif

#endif
