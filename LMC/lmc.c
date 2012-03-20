#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int prog_mem[99];
int acc;
int acc_negative;
int prog_c;
int strict_output = 1;
clock_t current_time;
void delay(int i)
{
	while(difftime(clock(), current_time)<i)
	{
		//do nothing...
	}
	current_time = clock();
}
int main (int argc, char** argv)
{
	//read the contents of a program file into the program memory
	FILE * s_program;
	FILE * io_file;
	s_program = fopen(argv[1],"r");
	io_file = fopen("io.txt","w");
	
	if(s_program != NULL && io_file != NULL)
	{
		//read in the file
		int c = 0;
		int t = 0;
		while(fscanf(s_program,"%i",&t)!=EOF && c<99)
		{
			prog_mem[c]=t%1000;
			//printf("m: %i = %i\n", c, i);
			c++;
		}		
		int halt = 1;
		prog_c = 0;
		while(halt == 1)
		{
			delay(500);
			int c_inst = prog_mem[prog_c];
			int operator = (int)(c_inst/100);
			int operand = c_inst-(operator*100);
			printf("\n\n-> PROGRAM COUNTER = %i\n", prog_c);
			printf("-> INSTRUCTION =     %i\n", c_inst);
			/*printf("-> OPERATOR =        %i\n", operator);
			printf("-> OPERAND =         %i\n", operand);
			printf("-> ACCUMULATOR =     %i\n", acc);*/
			delay(500);
			switch(operator)
			{
				case 0:
					printf("--> HALT\n");
					printf("--------------PROGRAM FINISHED--------------\n");
					halt = 0;
				break;
				case 1:
					//ADD
					printf("--> ADD data in %i to accumulator\n",operand);
					printf("--> DAT in %i = %i\n", operand, prog_mem[operand]);
					acc += prog_mem[operand];
					acc_negative = acc<0;
					acc = acc%999;
				break;
				case 2:
					//SUBTRACT
					printf("--> SUB data in %i from accumulator\n", operand);
					printf("--> DAT in %i = %i\n", operand, prog_mem[operand]);
					acc -= prog_mem[operand];
					acc_negative = acc<0;
					acc = acc%999;
				break;
				case 3:
					//STORE
					printf("--> STO acc in mem %i\n", operand);
					printf("--> ACC = %i", acc);
					prog_mem[operand] = acc;
				break;
				case 5:
					//LOAD
					printf("--> LDA mem %i into acc\n", operand);
					printf("--> DAT in %i = %i\n", operand, prog_mem[operand]);
					acc = prog_mem[operand];
				break;
				case 6:
					//BRANCH
					printf("--> BRA to mem %i\n", operand);
					prog_c = operand-1;
				break;
				case 7:
					//BRANCH IF ZeRO
					printf("-->BRZ to mem %i\n", operand);
					if(acc == 0)
					{
						printf("---> ACC = 0, brancing.\n");
						prog_c = operand-1;
					}else{
						printf("---> ACC <> 0, not branching.\n");
					}
				break;
				case 8:
					//BRANCH IF POSITIVE
					printf("-->BRP to mem %i\n", operand);
					if(acc >= 0)
					{
						printf("---> ACC >= 0, brancing.\n");
						prog_c = operand-1;
					}else{
						printf("---> ACC < 0, not branching.\n");
					}
				break;
				case 9:
					//IO
					printf("-->IO");
					if(operand == 1)
					{
						printf(" IN\n");
						printf("-->INP into acc: ");
						scanf("%i", &acc);
						fprintf(io_file,"INPUT: %i\n", acc);
					}else if(operand == 2){
						printf(" OUT\n");
						fprintf(io_file,"OUTPUT: %i\n", acc);
					}
				break;
			}
			prog_c++;
		}
	}else{
		printf("opening failed\n");
	}
	fclose(s_program);
	fclose(io_file);
	scanf("%i", &prog_c);
	return 0;
}