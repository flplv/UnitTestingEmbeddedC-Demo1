all: tests

msp430:
	make -f MakeMsp430.mk V=${V} all

msp430_clean:
	make -f MakeMsp430.mk V=${V} clean	

msp430_deploy:
	make -f MakeMsp430.mk V=${V} deploy

tests:
	make -f MakeTests.mk V=${V} all
	
clean:	
	make -f MakeMsp430.mk V=${V} clean
	make -f MakeTests.mk V=${V} clean
	@rm -rf lib objs
	

# To open msp430 serial:
# miniterm.py --eol 'LF'  /dev/ttyACM0 9600