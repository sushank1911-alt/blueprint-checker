#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "models.h"

// Module 3: Data Organization and Analysis
void organize_and_analyze_data(const Blueprint *bp, const QuestionPaper *qp, AuditReport *report);
void display_unit_wise_analysis(const AuditReport *report);
void display_co_wise_analysis(const AuditReport *report);
void display_cognitive_wise_analysis(const AuditReport *report);
void display_topic_coverage_analysis(const Blueprint *bp, const QuestionPaper *qp);

#endif // ANALYSIS_H
