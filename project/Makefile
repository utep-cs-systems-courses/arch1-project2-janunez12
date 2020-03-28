# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS         = -L/opt/ti/msp430_gcc/include

#switch the compuler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all:
	(cd /home/student/arch1-project2-janunez12/project/timerLib; make install)

	(cd /home/student/arch1-project2-janunez12/project; make button.elf)

#additional rules for files
button.elf: ${COMMON_OBJECTS} buzzer.o p2_interrupt_handle.o led.o switches.o main.o ../project/lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load:	button.elf
	msp430loader.sh button.elf

clean:
	rm -f *.o *.elf

