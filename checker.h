#ifndef CHECKER_H
#define CHECKER_H

#include "models.h"

// Module 4: Blueprint Checking and Comparison Engine
int run_blueprint_compliance_check(const Blueprint *bp, const QuestionPaper *qp, AuditReport *report);
void print_compliance_summary(const AuditReport *report);

#endif // CHECKER_H
