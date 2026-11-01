#ifndef QUESTION_PAPER_H
#define QUESTION_PAPER_H

#include "models.h"

// Module 2: Question Paper Management Functions
void init_question_paper(QuestionPaper *qp);
int add_question(QuestionPaper *qp, const char *q_no, const char *content, int unit, int co_number, const char *topic, int cog_level, int marks);
void view_question_paper(const QuestionPaper *qp);
int modify_question(QuestionPaper *qp, int index);
int delete_question(QuestionPaper *qp, int index);
int calculate_question_paper_total_marks(QuestionPaper *qp);
int save_question_paper_to_file(const QuestionPaper *qp, const char *filename);
int load_question_paper_from_file(QuestionPaper *qp, const char *filename);
void load_default_rgm_question_paper(QuestionPaper *qp, int flawed_scenario);

#endif // QUESTION_PAPER_H
