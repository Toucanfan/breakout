#ifndef STD_FIXPT_H
#define STD_FIXPT_H

struct std_fixpt_point {
	long x;
	long y;
};

/* macro functions */
#define std_fixpt_cos(dgr512) std_fixpt_sin(dgr512 + 128)
#define std_fixpt_mul(a, b) ((a >> 14) * b)
#define std_fixpt_div(a, b) ((a << 14) / b)

/* function prototypes */
extern long std_fixpt_sin(int dgr512);
extern void rotate(struct std_fixpt_point *point, int dgr512);


#endif /* std/fixpt.h */
