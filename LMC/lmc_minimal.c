#include <stdio.h>
#include <stdlib.h>
int prog_mem[99];
int acc,acc_negative, prog_c=0, halt=1;
int main (int argc, char** argv)
{
	FILE * s_program = fopen(argv[1],"r");
	FILE * io_file= fopen("io.txt","w");
	if(s_program != NULL && io_file != NULL)
	{
		int c = 0,t = 0;
		while(fscanf(s_program,"%i",&t)!=EOF && c<99)
		{
			prog_mem[c++]=t%1000;
		}		
		int halt = 1;
		while(halt == 1)
		{
			int c_inst = prog_mem[prog_c];
			int operator = (int)(c_inst/100);
			int operand = c_inst-(operator*100);
			switch(operator)
			{
				case 0:
					halt = 0;
				break;
				case 1:
					acc += prog_mem[operand];
					acc_negative = acc<0;
					acc = acc%999;
				break;
				case 2:
					acc -= prog_mem[operand];
					acc_negative = acc<0;
					acc = acc%999;
				break;
				case 3:
					prog_mem[operand] = acc;
				break;
				case 5:
					acc = prog_mem[operand];
				break;
				case 6:
					prog_c = operand-1;
				break;
				case 7:
					if(acc == 0)
						prog_c = operand-1;
				break;
				case 8:
					if(acc >= 0)
						prog_c = operand-1;
				break;
				case 9:
					if(operand == 1)
					{
						printf("INPUT: ");
						scanf("%i", &acc);
						fprintf(io_file,"INPUT: %i\n", acc);
					}else if(operand == 2){
						fprintf(io_file,"OUTPUT: %i\n", acc);
					}
				break;
			}
			prog_c++;
		}
	}
	fclose(s_program);
	fclose(io_file);
	getchar();
	return 0;
}
