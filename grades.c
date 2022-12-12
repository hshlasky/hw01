#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"
#include "grades.h"


typedef struct st_grades{
	int id;
	char* name;
	struct list* st_courses;
}st_grades_t;

typedef struct course{
	char* cs_name;
	int cs_grade;
}course_t;

typedef struct grades{
	struct list* grades_list;
}grades_t;



int course_clone (void* element, void** output){
	course_t* cs_temp = (course_t*)element;
	
	course_t* cs_out = (course_t*)malloc(sizeof(course_t));
	if (!cs_out) { //check if malloc didn't work.
		return 1;
	}
	
	//start cloning feilds and check that they are valid.
	//return 1 if not and 0 if successful.
	
	//copy course_name
	cs_out->cs_name = 
		(char*)malloc(sizeof(char)*(strlen(cs_temp->cs_name)+1));
	if (!(cs_out->cs_name)){ //check if malloc didn't work.
		free (cs_out);
		return 1;
	}
	
	strcpy(cs_out->cs_name, cs_temp->cs_name);
		
	//copy course_grade
	cs_out->cs_grade = cs_temp->cs_grade;

	*output = cs_out;
	return 0;
}


void course_destroy (void* element) {
	course_t *cs_ptr = (course_t*)element;
	free (cs_ptr->cs_name);
	free (cs_ptr);
}





/**
 * @brief cloning student func.
 * @param element st_grades struct to copy
 * @param output address  of cloned st_grades struct
 * @returns 0 on success, 1 on failed
*/
int student_clone (void* element, void** output){
	st_grades_t* st_temp = (st_grades_t*)element;
	
	st_grades_t* st_out = (st_grades_t*)malloc(sizeof(st_grades_t));
	if (!st_out) { //check if malloc didn't work.
		return 1;
	}
	
	//start cloning feilds and check that they are valid.
	//return 1 if not and 0 if successful.
	//copy student_id
	st_out->id = st_temp->id;

	//copy student_name
	st_out->name = 
		(char*)malloc(sizeof(char)*(strlen(st_temp->name)+1));
	if (!(st_out->name)){ //check if malloc didn't work.
		free (st_out);
		return 1;
	}
	strcpy(st_out->name, st_temp->name);
	
	//copy the courses to the list
	//tmp and out list ptr
	struct list* st_temp_cs = st_temp->st_courses;
	
	//initiate student_courses list
	st_out->st_courses=list_init(course_clone, course_destroy);
	if (!(st_out->st_courses)) { 
		free (st_out->name);
		free (st_out);
		return 1;
	}
	//tmp first iterator ptr
	struct iterator* st_temp_cs_it=list_begin(st_temp_cs);
	
	while (st_temp_cs_it) {
		course_t cs_node_copy;
		course_clone(st_temp_cs_it,(void**)&cs_node_copy); //???
		list_push_back(st_out->st_courses, &cs_node_copy);
		st_temp_cs_it=list_next(st_temp_cs_it);
	}
	
	*output = st_out;
	return 0;
}

void student_destroy (void* element) {
	st_grades_t* st_ptr = (st_grades_t*)element;
	list_destroy(st_ptr->st_courses);
	free (st_ptr->name);	
	free (st_ptr);
}




/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init() {
	grades_t* grades_main=(grades_t*)malloc(sizeof(grades_t*));
	if(!(grades_main)) {
		return NULL;
	}
	
	grades_main->grades_list=list_init(student_clone,student_destroy);
	if(!(grades_main->grades_list)) {
		free(grades_main);
		return NULL;
	}
	
	return grades_main;	
}

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
	list_destroy(grades->grades_list);
	free (grades);
}

/**???
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
 st_grades_t* find_student(struct grades *grades, int id) { 
/*	struct iterator* st_itr = list_begin(grades->grades_list);
	while(st_itr) {
		if(id == ((st_grades_t*)list_get(st_itr))->id) {
			return (st_grades_t*)list_get(st_itr);
		}
		st_itr=list_next(st_itr);
	}

	return NULL;
*/
	 if (grades == NULL){
		return NULL;
	}

	struct iterator* it_st = list_begin(grades->grades_list);
	if(it_st == NULL){
		return NULL;
	}

	while(it_st != NULL){
		if(((st_grades_t*)list_get(it_st))->id == id)
		{
			return (st_grades_t*)list_get(it_st);
		}
		it_st = list_next(it_st);
	}
	return NULL;
}



/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
	
	//check if "grades" is valid
	if(!(grades->grades_list)||!(grades)){
		return 1;
	}
	
	
	//check if "id" already exists in "grades"
	if(find_student(grades,id)) {
		return 1;
	}
	
	
	//add new student to "grades" list
	st_grades_t* st_new = (st_grades_t*)malloc(sizeof(st_grades_t*));
	if(!(st_new)) {
		return 1;
	}
	
	st_new->id=id;
	
	st_new->name = 
		(char*)malloc(sizeof(char)*(strlen(name)+1));
	if (!(st_new->name)){ //check if malloc didn't work.
		free (st_new);
		return 1;
	}
	strcpy(st_new->name, name);
	
	st_new->st_courses=list_init (course_clone, course_destroy);
	if (!(st_new->st_courses)) { 
		free (st_new->name);
		free (st_new);
		return 1;
	}
	return list_push_back(grades->grades_list, (void*)st_new);

}

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
						 
	//check if "grades" is valid

	if(!(grades->grades_list)||!(grades)){
		return 1;
	}
	
	//find student with "id" in grade
	st_grades_t* student = find_student(grades,id);
	//check if "id" doesn't exist in "grades" (ptr=null)
	if(!(student)) {
		return 1;
	}
	
	//check if "grade" is between 0 to 100.
	if((grade>100)||(grade<0)) {
		return 1;
	}
	
	//check if "name" already exists in current student
	struct iterator* student_cs = list_begin(student->st_courses);
	while(student_cs) {
		if(!(strcmp(name,((course_t*)list_get(student_cs))->cs_name))) {
			return 1;
		}
		student_cs=list_next(student_cs);
	}
	
	
	//create new course
	course_t* cs_new = (course_t*)malloc(sizeof(course_t*));
	if (!(cs_new)) { //check if malloc didn't work.
		return 1;
	}	
	
	//update course_name
	cs_new->cs_name = 
		(char*)malloc(sizeof(char)*(strlen(name)+1));
	if (!(cs_new->cs_name)){ //check if malloc didn't work.
		free (cs_new);
		return 1;
	}
	
	strcpy(cs_new->cs_name, name);
		
	//update course_grade
	cs_new->cs_grade = grade;
	//???
	return list_push_back(student->st_courses, (void*)cs_new);
					
 }

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "*out" to NULL.
 * @note "out" is a pointer to char*. Meaning, your function should
 * allocate memory on the heap and set "*out" to point on that memory.
 * This methodology (of returning values via pointers) is very common in C.
 * An example of C method that returns a value via pointer:
 * void foo(int *out) {
 *   *out = 1;  
 * }
 */
float grades_calc_avg(struct grades *grades, int id, char **out){
	
	//check if "grades" is valid
	if(!(grades->grades_list)||!(grades)){
		return -1;
	}
	
	//find student with "id" in grade
	st_grades_t* student = find_student(grades,id);
	//check if "id" doesn't exist in "grades" (ptr=null)
	if(!(student)) {
		return -1;
	}
	
	//calculate the sum of the student's grades
	float sum=0.0;
	int counter=0;
	
	struct iterator* grade_itr = list_begin(student->st_courses);
	while(grade_itr!=NULL) {
		sum+=((course_t*)list_get(grade_itr))->cs_grade;
		counter++;
		grade_itr=list_next(grade_itr);
	}
		
	//define *out to be the student's name
	*out = (char*)malloc(sizeof(char)*(strlen(student->name)+1));
	if(!(*out)) { //check if malloc didn't work.
		return -1;
	}	
	strcpy(*out,student->name);

	//check if the student doesnt have any grades
	if(counter==0){
		return 0.00;
	}
	else {
	//calculate the sum of the student's grades
	return sum/counter;	
	}
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
	
	//check if "grades" is valid
	if(!(grades->grades_list)||!(grades)){
		return 1;
	}
	
	//find student with "id" in grade
	st_grades_t* student = find_student(grades,id);
	//check if "id" doesn't exist in "grades" (ptr=null)
	if(!(student)) {
		return 1;
	}
	
	//print student details
	printf("%s %d:", student->name,student->id);
	
	//print student grades
	struct iterator* grade_itr = list_begin(student->st_courses);

	while(grade_itr) {
		if(list_next(grade_itr)){
		printf(" %s %d,", ((course_t*)list_get(grade_itr))->cs_name,
		((course_t*)list_get(grade_itr))->cs_grade);
		grade_itr=list_next(grade_itr);
		}
		else {
		printf(" %s %d", ((course_t*)list_get(grade_itr))->cs_name,
		((course_t*)list_get(grade_itr))->cs_grade);
		grade_itr=list_next(grade_itr);
		}
	}
	
	
	return 0;
}

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){
	
	//check if "grades" is valid
	if(!(grades->grades_list)||!(grades)){
		return 1;
	}
	
	//print all the student in the list
	struct iterator* student_itr = list_begin(grades->grades_list);
	while(student_itr) {
		if(grades_print_student(grades,((st_grades_t*)list_get(student_itr))->id)) {
			return 1;
		}
		printf("\n");
		student_itr=list_next(student_itr);
	}
	
	return 0;
}
