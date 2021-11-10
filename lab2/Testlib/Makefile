calculator_mk : calculator.o ./lib/cal_operation.o
	gcc -o calculator_mk calculator.o ./lib/cal_operation.o
calculator.o : calculator.c
	gcc -c calculator.c
cal_operation.o : ./lib/cal_operation.c
	gcc -c ./lib/cal_operation.c
clean : 
	rm -f calculator_mk calculator.o ./lib/cal_operation.o
