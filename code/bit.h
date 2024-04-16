#ifndef BIT_H
#define BIT_H

#define	SETBIT(NUM,BIT) (NUM |= (1<<BIT))
#define	CLEARBIT(NUM,BIT) (NUM &= ~(1<<BIT))
#define	TOGGLEBIT(NUM,BIT) (NUM ^= (1<<BIT))
#define	GETBIT(NUM,BIT) (NUM = ((NUM >> BIT) & 1))

#define SET_BIT(reg, bit)    ((reg) |= (1 << (bit)))
#define GET_BIT(reg, bit)    (((reg) >> (bit)) & 1)
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1 << (bit)))

#endif
