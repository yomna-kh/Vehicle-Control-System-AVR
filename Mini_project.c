/*
 * Mini_project.c
 *
 */

#include<stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1
#define ON 1
#define OFF 0
char input1;
char input2;
int engine_data = 0;
struct Data {
	float ac_temperature ;
	float eng_temperature ;
	int v_speed ;
	int controller;
	float temp_ac;
	float temp_eng;
	int AC;
	char colour;
}vehicle;
struct Data *ptr = &vehicle;/*pointer to structure - easier to access */


void sensor(char*);/*declaring el functions so compiler will know definition are there */
void traffic_data(struct Data* );
int room_temp(struct Data* ) ;
int engine_temp(struct Data* );
void display();
/*1st menu will loop by do while if the input is b */
void menu(char *input_menu)

{
	do {
		printf("Choose from the following: \n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n");
		scanf(" %c", input_menu);
		/*C is case senstive so a & A must have the same answer*/
		switch (*input_menu) {
		case 'a':
		case 'A':
			engine_data = ON ;
			printf("\nEngine is turned on \n\n");
			sensor(&input2);
			break;
		case 'b':/*NO break as I want it to have the same result as 'B' */
		case 'B':
			printf("\nTurn off the engine\n\n");
			engine_data = OFF ;
			break;
		case 'c':
		case 'C':
			printf("\nQUIT\n\n");
			break;
		default:/*what if user entered another input? */
			printf("\n ERROR, Please re-enter \n\n");
			menu(&input1);

		}
	} while (*input_menu == 'b' ||*input_menu == 'B' );
}


void sensor(char *input2)

{

	/*2nd menu  */
	printf("\nChoose from the following: \n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
	scanf(" %c", input2);

	switch (*input2) {
	case 'a':
	case 'A':
		printf("\nTurn off the engine\n\n");
		menu(&input1);
		break;
	case 'b':
	case 'B':
		printf("\n Insert a color\n\n ");
		scanf(" %c", &(*ptr).colour);
		traffic_data(ptr);
		display();
		break;
	case 'c':
	case 'C':
		printf("\n Insert room temperature\n\n ");
		scanf(" %f", &(*ptr).temp_ac);
		(*ptr).AC = room_temp(ptr);/*just ptr not *ptr.temp */
		display();
		break;
#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
	case 'd':
	case 'D':
			printf("\nInsert engine temperature\n\n ");
			scanf(" %f", &(*ptr).temp_eng);
			(*ptr).controller = engine_temp(ptr);
			display();
			break;
	default:/*what if user entered another input? */
			printf("\n ERROR \n\n");


#endif
	}

}
void traffic_data(struct Data* ptr) {

	switch (ptr -> colour) {
	case 'G':
	case 'g':
		(*ptr).v_speed = 100;
		break;
	case 'O':
	case 'o':
		(*ptr).v_speed = 30;
		break;
	case 'R':
	case 'r':
		(*ptr).v_speed = 0;
		break;
	}

}

int room_temp(struct Data* ptr) {
	(*ptr).ac_temperature = ptr -> temp_ac;
	if (ptr -> temp_ac < 10 || ptr -> temp_ac > 30) {

		(*ptr).ac_temperature = 20;
		return ON;
	}

	return OFF;

}
/* This is the bonus requirments */
#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
int engine_temp(struct Data* ptr) {
		(*ptr).eng_temperature = (*ptr).temp_eng;
		if (ptr -> temp_eng < 100 || ptr -> temp_eng > 150) {
			(*ptr).eng_temperature = 125;
			return ON;
		}
		return OFF;
}
#endif

void display() {
/* In case the speed is 30 , there are certain controls */
	if ((*ptr).v_speed == 30) {
		(*ptr).ac_temperature = ((*ptr).ac_temperature * (5 / 4)) + 1;
		(*ptr).AC = ON;
#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
			(*ptr).eng_temperature = ((*ptr).eng_temperature * (5 / 4)) + 1;
			(*ptr).controller = ON;

#endif
	}
/* Print the following */
	if (engine_data == 1)
			printf("Engine is  : ON\n");
		else
			printf("Engine is : OFF\n");
	if ((*ptr).AC == ON)
		printf("AC : ON\n");
	else
		printf("AC : OFF\n");
	printf("Vehicle speed : %d Km/hr \n", (*ptr).v_speed);
	printf("Room Temperature : %.2f C\n", (*ptr).ac_temperature);
#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
		printf("Engine Temperature : %.2f C\n", (*ptr).eng_temperature);
		if ((*ptr).controller == ON)
			printf("Engine controller : ON \n");
		else
			printf("Engine controller state : OFF\n");

#endif
	sensor(&input2);

}

int main(void) {


	ptr-> colour = 'G';
	ptr-> ac_temperature = 25 ;
	ptr -> eng_temperature = 120;
	ptr -> v_speed = 40 ;


	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	menu(&input1);
}

