#ifndef REPORT_H
#define REPORT_H

#include "models.h"

// Module 5: Report Generation and File Management
void display_full_compliance_report(const Blueprint *bp, const QuestionPaper *qp, const AuditReport *report);
int export_audit_report_to_file(const Blueprint *bp, const QuestionPaper *qp, const AuditReport *report, const char *filename);
int export_audit_report_to_csv(const Blueprint *bp, const QuestionPaper *qp, const AuditReport *report, const char *filename);

#endif // REPORT_H
