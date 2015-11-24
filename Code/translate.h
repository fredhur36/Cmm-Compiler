#ifndef __TRAN__
#define __TRAN__

#include"common.h"
typedef struct Operand_* Operand;

struct Operand_
{
	enum {VARIABLE , CONSTANT , TEMP , ADDRESS , LABEL_SIGN , FUNC} kind;
	union
	{
		int var_no;
		int value;
		int temp_no;
		int label_no;
		char* func_name;
	}u;
};

struct InterCode
{
	enum {LABEL , FUNCTION , ASSIGN , ADD , SUB , MUL , DIV , ADD_ASSIGN , REF_ASSIGN , ASSIGN_REF , GOTO , RELOP_GOTO  , RETURN ,DEC , ARG , CALLFUNC , PARAM , READ , WRITE } kind;
	union
	{
		struct {Operand x;} label;
		struct {Operand f;} function;
		struct {Operand x, y, z;} alop;
		struct {Operand x , y;} assignop;
		struct {Operand x;} gotolabel;
		struct {Operand x, y, z , relop;} relopgoto;
		struct {Operand x;} ret;
		struct {Operand x ,  size;} dec;
		struct {Operand x;} arg;
		struct {Operand x , f;} callfunc;
		struct {Operand x;} param;
		struct {Operand x;} read;
		struct {Operand x;} write;
	}u;
};

struct InterCodes
{
	struct InterCode code;
	struct InterCodes* prev;
	struct InterCodes* next;
};

struct InterCodes* code_head;
struct InterCodes* current_code;
int variable_num;
int temp_num;
int label_num;

void insertcode(struct InterCodes* );

void outputoperand(Operand , FILE* );

void outputlabel(struct InterCodes* , FILE*);

void outputfunction(struct InterCodes* , FILE*);

void outputalop(struct InterCodes* , FILE*);

void outputassign(struct InterCodes* , FILE*);

void outputgoto(struct InterCodes* , FILE*);

void outputrelopgoto(struct InterCodes* , FILE*);

void outputreturn(struct InterCodes* , FILE*);

void outputdec(struct InterCodes* , FILE*);

void outputarg(struct InterCodes* , FILE*);

void outputcallfunc(struct InterCodes* , FILE*);

void outputparam(struct InterCodes* , FILE*);

void outputread(struct InterCodes* , FILE*);

void outputwrite(struct InterCodes* , FILE*);

void translate_function(struct tree_node* );

void translate_exp(struct tree_node* , Operand);

void translate_cond(struct tree_node* , Operand , Operand);

void translate_stmt(struct tree_node*);

void optimize();
#endif
